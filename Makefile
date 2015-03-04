
WORKDIR = `pwd`

CXX = g++
AR = ar
LD = g++

INC = -ILibraries/glm/include -ILibraries/Arc/include -ILibraries/lodepng/include -ISource -I/usr/include/lua5.2/
CFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
LIBDIR = -LLibraries/Arc/lib -L/usr/lib64
LIB = -lm -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXi -lXxf86vm -lXrandr -lpthread -lArcCore -llua5.2
LDFLAGS =

# Debug
CFLAGS = $(CFLAGS) -g -DDEBUG
LDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = obj
OUT = dusk

SOURCES = \
 Source/Events/Event.cpp \
 Source/Events/IEventDispatcher.cpp \
 Source/Graphics/GraphicsContext.cpp \
 Source/Graphics/GraphicsSystem.cpp \
 Source/Graphics/Mesh.cpp \
 Source/Graphics/Model.cpp \
 Source/Graphics/ShaderManager.cpp \
 Source/Graphics/Texture.cpp \
 Source/Graphics/Window.cpp \
 Source/Input/InputSystem.cpp \
 Source/Logging/Log.cpp \
 Source/Scripting/ScriptingSystem.cpp \
 Source/Timing/TimeInfo.cpp \
 Source/Timing/Timer.cpp \
 Source/World/Skybox.cpp \
 Source/World/Camera.cpp \
 Source/Program.cpp \
 Source/Main.cpp \
 Libraries/lodepng/include/lodepng/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

.cpp.o:
	$(CXX) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	$(LD) $(LIBDIR) -o $(OUT) $(OBJECTS) $(LDFLAGS_DEBUG) $(LIB)
