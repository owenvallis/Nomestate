# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode" -I "../../Libraries/**"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"/usr/X11R6/lib/" -L"../../../../../sdks/juce/modules/bin" -lfreetype -lpthread -lrt -lX11 -lGL -lGLU -lXinerama -lasound -lXext 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode" -I "../../Libraries/**"
  TARGET := chronomeState
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode" -I "../../Libraries/**"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"/usr/X11R6/lib/" -L"../../../../../sdks/juce/modules/bin" -lfreetype -lpthread -lrt -lX11 -lGL -lGLU -lXinerama -lasound -lXext 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode" -I "../../Libraries/**"
  TARGET := chronomeState
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/IpEndpointName_3e2b2d0e.o \
  $(OBJDIR)/NetworkingUtils_1825df34.o \
  $(OBJDIR)/UdpSocket_ad3365ab.o \
  $(OBJDIR)/OscOutboundPacketStream_87ae81a6.o \
  $(OBJDIR)/OscPrintReceivedElements_773a3861.o \
  $(OBJDIR)/OscReceivedElements_990f2ae6.o \
  $(OBJDIR)/OscTypes_5116aa15.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/DeviceTabComponent_b12cf8e7.o \
  $(OBJDIR)/MIDIMsgTypeIOComponent_451c4b26.o \
  $(OBJDIR)/MidiIOManagerComponent_e965e200.o \
  $(OBJDIR)/PreferencesComponent_df4d6ee.o \
  $(OBJDIR)/NomeButton_bfba13b4.o \
  $(OBJDIR)/CustomLookAndFeel_ab3d772e.o \
  $(OBJDIR)/MainWindow_499ac812.o \
  $(OBJDIR)/MainComponent_a6ffb4a5.o \
  $(OBJDIR)/ColourSelectorPropertyComponent_945bf9fe.o \
  $(OBJDIR)/ZeroConfResolve_a5bbfec1.o \
  $(OBJDIR)/ZeroConfReceiver_ce82e104.o \
  $(OBJDIR)/SignalCore_18610870.o \
  $(OBJDIR)/SignalModifier_9cd9d1a8.o \
  $(OBJDIR)/MIDIReceiver_18ed0c99.o \
  $(OBJDIR)/MIDISender_1809031f.o \
  $(OBJDIR)/NetworkReceiver_ef9c181e.o \
  $(OBJDIR)/NetworkSender_7b9f2be4.o \
  $(OBJDIR)/MessageCenter_7646b89d.o \
  $(OBJDIR)/Commands_fe28c111.o \
  $(OBJDIR)/Signal_e892fa31.o \
  $(OBJDIR)/Message_d04bf4e8.o \
  $(OBJDIR)/OSCBroadcaster_66f75cb8.o \
  $(OBJDIR)/OSCBundle_341fc942.o \
  $(OBJDIR)/OSCListener_6ac05db4.o \
  $(OBJDIR)/OSCMessage_2d11b191.o \
  $(OBJDIR)/MidiIODeviceManager_3cab7e11.o \
  $(OBJDIR)/PropertiesManager_f871875b.o \
  $(OBJDIR)/PropertyGroup_716a000b.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_devices_a4c8a728.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking Nomestate
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning Nomestate
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

$(OBJDIR)/IpEndpointName_3e2b2d0e.o: ../../Libraries/ip/IpEndpointName.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IpEndpointName.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NetworkingUtils_1825df34.o: ../../Libraries/ip/posix/NetworkingUtils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NetworkingUtils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/UdpSocket_ad3365ab.o: ../../Libraries/ip/posix/UdpSocket.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling UdpSocket.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OscOutboundPacketStream_87ae81a6.o: ../../Libraries/osc/OscOutboundPacketStream.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OscOutboundPacketStream.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OscPrintReceivedElements_773a3861.o: ../../Libraries/osc/OscPrintReceivedElements.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OscPrintReceivedElements.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OscReceivedElements_990f2ae6.o: ../../Libraries/osc/OscReceivedElements.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OscReceivedElements.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OscTypes_5116aa15.o: ../../Libraries/osc/OscTypes.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OscTypes.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DeviceTabComponent_b12cf8e7.o: ../../Source/DeviceTabComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DeviceTabComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MIDIMsgTypeIOComponent_451c4b26.o: ../../Source/MIDIMsgTypeIOComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MIDIMsgTypeIOComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiIOManagerComponent_e965e200.o: ../../Source/MidiIOManagerComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiIOManagerComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PreferencesComponent_df4d6ee.o: ../../Source/PreferencesComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PreferencesComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NomeButton_bfba13b4.o: ../../Source/NomeButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NomeButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CustomLookAndFeel_ab3d772e.o: ../../Source/CustomLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CustomLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_499ac812.o: ../../Source/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_a6ffb4a5.o: ../../Source/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ColourSelectorPropertyComponent_945bf9fe.o: ../../Source/ColourSelectorPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ColourSelectorPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ZeroConfResolve_a5bbfec1.o: ../../Source/ZeroConfResolve.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ZeroConfResolve.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ZeroConfReceiver_ce82e104.o: ../../Source/ZeroConfReceiver.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ZeroConfReceiver.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SignalCore_18610870.o: ../../Source/SignalCore.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SignalCore.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SignalModifier_9cd9d1a8.o: ../../Source/SignalModifier.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SignalModifier.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MIDIReceiver_18ed0c99.o: ../../Source/MIDIReceiver.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MIDIReceiver.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MIDISender_1809031f.o: ../../Source/MIDISender.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MIDISender.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NetworkReceiver_ef9c181e.o: ../../Source/NetworkReceiver.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NetworkReceiver.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NetworkSender_7b9f2be4.o: ../../Source/NetworkSender.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NetworkSender.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MessageCenter_7646b89d.o: ../../Source/MessageCenter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MessageCenter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Commands_fe28c111.o: ../../Source/Commands.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Commands.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Signal_e892fa31.o: ../../Source/Signal.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Signal.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Message_d04bf4e8.o: ../../Source/Message.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Message.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OSCBroadcaster_66f75cb8.o: ../../Source/OSCBroadcaster.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OSCBroadcaster.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OSCBundle_341fc942.o: ../../Source/OSCBundle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OSCBundle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OSCListener_6ac05db4.o: ../../Source/OSCListener.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OSCListener.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OSCMessage_2d11b191.o: ../../Source/OSCMessage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OSCMessage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiIODeviceManager_3cab7e11.o: ../../Source/MidiIODeviceManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiIODeviceManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PropertiesManager_f871875b.o: ../../Source/PropertiesManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PropertiesManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PropertyGroup_716a000b.o: ../../Source/PropertyGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PropertyGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: ../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
