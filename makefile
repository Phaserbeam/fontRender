# Compiler and flags
CXX = g++
CXXFLAGS = -I./libs/ -I ./src/ 
DEBUG?=0

ifneq (,$(findstring r,$(MAKEFLAGS)))
    CXXFLAGS += -O3
else
    CXXFLAGS += -g -D_DEBUG
endif

TARGET = target
BUILD_DIR ?= ./build
LIBS = -lGL -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi
# All source files
SOURCES = $(shell find . -name "*.cpp")
# ./build/./libs
OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Default rule
all: $(TARGET)
	@ mv $(TARGET) $(BUILD_DIR)
	@ echo "Executing "$(TARGET)
	@ echo "--------------------"
	@ ./$(BUILD_DIR)/$(TARGET)
# Rule to link the executable
$(TARGET): $(OBJECTS)
	@ $(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

# Rule to compile source files
$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ echo $@ 
	@ $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	@ rm -r $(BUILD_DIR)/src
	@ rm $(BUILD_DIR)/$(TARGET)
clean-all:
	@ rm $(BUILD_DIR)/$(TARGET)
	@ rm -r $(BUILD_DIR)
$(BUILD_DIR):
	@ mkdir $(BUILD_DIR)

.PHONY: all clean
