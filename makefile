CXX = g++
CC = gcc
TARGET = WaveVisualizer
ifeq ($(OS), Windows_NT)
    TARGET := $(TARGET).exe
    LDFLAGS = -lSDL3 -lm -mwindows
    CLEAN_CMD = del /F /Q
    SLASH = \\
    RUN_CMD = $(TARGET)
else
    LDFLAGS = -lSDL3 -lm
    CLEAN_CMD = rm -f
    SLASH = /
    RUN_CMD = ./$(TARGET)
endif

CXXFLAGS = -std=c++17 -I. -g
CFLAGS = -std=c11 -I. -g

SOURCES_CPP = ui.cpp \
              imgui/imgui.cpp \
              imgui/imgui_draw.cpp \
              imgui/imgui_tables.cpp \
              imgui/imgui_widgets.cpp \
              imgui/imgui_impl_sdl3.cpp \
              imgui/imgui_impl_sdlrenderer3.cpp

SOURCES_C = main.c

OBJECTS = $(SOURCES_CPP:.cpp=.o) $(SOURCES_C:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo Linking executable...
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo Build complete: $(RUN_CMD)

%.o: %.cpp
	@echo Compiling C++: $<
	$(CXX) -c $(CXXFLAGS) $< -o $@

%.o: %.c
	@echo Compiling C: $<
	$(CC) -c $(CFLAGS) $< -o $@

run: all
	$(RUN_CMD)

clean:
	@echo Removing executable...
	$(CLEAN_CMD) $(TARGET)

cleanall:
	@echo Cleaning up all build files...
	$(CLEAN_CMD) $(OBJECTS) $(TARGET)

.PHONY: all run clean cleanall