CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g

# Use the SDK verified to work with the currently installed Apple linker.
# Remove this override after updating to a toolchain compatible with SDK 27.
SDKROOT = /Library/Developer/CommandLineTools/SDKs/MacOSX26.5.sdk
CXXFLAGS += -isysroot $(SDKROOT)

CPPFLAGS += $(shell pkg-config --cflags spdlog)
LDLIBS += $(shell pkg-config --libs spdlog)

TARGET = parser_demo
SOURCE = src/protocol.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE) Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCE) $(LDFLAGS) $(LDLIBS) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
