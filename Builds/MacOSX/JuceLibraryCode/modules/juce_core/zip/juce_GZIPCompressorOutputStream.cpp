/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

namespace zlibNamespace
{
 #if JUCE_INCLUDE_ZLIB_CODE
  #undef OS_CODE
  #undef fdopen
  #include "zlib/zlib.h"
  #undef OS_CODE
 #else
  #include JUCE_ZLIB_INCLUDE_PATH
 #endif
}

BEGIN_JUCE_NAMESPACE

//==============================================================================
class GZIPCompressorOutputStream::GZIPCompressorHelper
{
public:
    GZIPCompressorHelper (const int compressionLevel, const int windowBits)
        : buffer ((size_t) gzipCompBufferSize),
          compLevel (compressionLevel),
          strategy (0),
          isFirstDeflate (true),
          streamIsValid (false),
          finished (false)
    {
        using namespace zlibNamespace;
        zerostruct (stream);

        streamIsValid = (deflateInit2 (&stream, compLevel, Z_DEFLATED,
                                       windowBits != 0 ? windowBits : MAX_WBITS,
                                       8, strategy) == Z_OK);
    }

    ~GZIPCompressorHelper()
    {
        if (streamIsValid)
            zlibNamespace::deflateEnd (&stream);
    }

    bool write (const uint8* data, int dataSize, OutputStream& destStream)
    {
        // When you call flush() on a gzip stream, the stream is closed, and you can
        // no longer continue to write data to it!
        jassert (! finished);

        while (dataSize > 0)
            if (! doNextBlock (data, dataSize, destStream, Z_NO_FLUSH))
                return false;

        return true;
    }

    void finish (OutputStream& destStream)
    {
        const uint8* data = nullptr;
        int dataSize = 0;

        while (! finished)
            doNextBlock (data, dataSize, destStream, Z_FINISH);
    }

private:
    enum { gzipCompBufferSize = 32768 };

    HeapBlock <zlibNamespace::Bytef> buffer;
    zlibNamespace::z_stream stream;
    int compLevel, strategy;
    bool isFirstDeflate, streamIsValid, finished;

    bool doNextBlock (const uint8*& data, int& dataSize, OutputStream& destStream, const int flushMode)
    {
        using namespace zlibNamespace;
        if (streamIsValid)
        {
            stream.next_in   = const_cast <uint8*> (data);
            stream.next_out  = buffer;
            stream.avail_in  = (z_uInt) dataSize;
            stream.avail_out = (z_uInt) gzipCompBufferSize;

            const int result = isFirstDeflate ? deflateParams (&stream, compLevel, strategy)
                                              : deflate (&stream, flushMode);
            isFirstDeflate = false;

            switch (result)
            {
                case Z_STREAM_END:
                    finished = true;
                    // Deliberate fall-through..
                case Z_OK:
                {
                    data += dataSize - stream.avail_in;
                    dataSize = (int) stream.avail_in;
                    const int bytesDone = (int) (gzipCompBufferSize - stream.avail_out);
                    return bytesDone <= 0 || destStream.write (buffer, bytesDone);
                }

                default:
                    break;
            }
        }

        return false;
    }
};

//==============================================================================
GZIPCompressorOutputStream::GZIPCompressorOutputStream (OutputStream* const destStream_,
                                                        int compressionLevel,
                                                        const bool deleteDestStream,
                                                        const int windowBits)
    : destStream (destStream_, deleteDestStream)
{
    jassert (destStream_ != nullptr);

    if (compressionLevel < 1 || compressionLevel > 9)
        compressionLevel = -1;

    helper = new GZIPCompressorHelper (compressionLevel, windowBits);
}

GZIPCompressorOutputStream::~GZIPCompressorOutputStream()
{
    flush();
}

void GZIPCompressorOutputStream::flush()
{
    helper->finish (*destStream);
    destStream->flush();
}

bool GZIPCompressorOutputStream::write (const void* destBuffer, int howMany)
{
    jassert (destBuffer != nullptr && howMany >= 0);

    return helper->write (static_cast <const uint8*> (destBuffer), howMany, *destStream);
}

int64 GZIPCompressorOutputStream::getPosition()
{
    return destStream->getPosition();
}

bool GZIPCompressorOutputStream::setPosition (int64 /*newPosition*/)
{
    jassertfalse; // can't do it!
    return false;
}

//==============================================================================
#if JUCE_UNIT_TESTS

class GZIPTests  : public UnitTest
{
public:
    GZIPTests()   : UnitTest ("GZIP") {}

    void runTest()
    {
        beginTest ("GZIP");
        Random rng;

        for (int i = 100; --i >= 0;)
        {
            MemoryOutputStream original, compressed, uncompressed;

            {
                GZIPCompressorOutputStream zipper (&compressed, rng.nextInt (10), false);

                for (int j = rng.nextInt (100); --j >= 0;)
                {
                    MemoryBlock data (rng.nextInt (2000) + 1);

                    for (int k = data.getSize(); --k >= 0;)
                        data[k] = (char) rng.nextInt (255);

                    original.write (data.getData(), data.getSize());
                    zipper  .write (data.getData(), data.getSize());
                }
            }

            {
                MemoryInputStream compressedInput (compressed.getData(), compressed.getDataSize(), false);
                GZIPDecompressorInputStream unzipper (compressedInput);

                uncompressed << unzipper;
            }

            expectEquals ((int) uncompressed.getDataSize(),
                          (int) original.getDataSize());

            if (original.getDataSize() == uncompressed.getDataSize())
                expect (memcmp (uncompressed.getData(),
                                original.getData(),
                                original.getDataSize()) == 0);
        }
    }
};

static GZIPTests gzipTests;

#endif

END_JUCE_NAMESPACE
