
WORKDIR = `pwd`

CXX = g++
AR = ar
LD = g++

INC = -I../Libraries/glm/include -I../Libraries/Arc/include -I./ -I/usr/include/lua5.2/
LIBDIR = -L../Libraries/Arc/lib -L/usr/lib64
LIB = -lm -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXi -lXxf86vm -lXrandr -lpthread -lArcCore -llua5.2
CFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
LDFLAGS =

# Debug
XCFLAGS = $(CFLAGS) -g -DDEBUG
XLDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = ../obj/Dusk
OUT = ../dusk

SOURCES = \
Events/Event.cpp \
Events/IEventDispatcher.cpp \
Graphics/GraphicsContext.cpp \
Graphics/GraphicsSystem.cpp \
Graphics/Mesh.cpp \
Graphics/Model.cpp \
Graphics/ShaderManager.cpp \
Graphics/Texture.cpp \
Graphics/Window.cpp \
Input/InputSystem.cpp \
Logging/Log.cpp \
Scripting/ScriptingSystem.cpp \
Timing/TimeInfo.cpp \
Timing/Timer.cpp \
World/Skybox.cpp \
World/Camera.cpp \
Program.cpp \
Main.cpp \
lodepng/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

.cpp.o:
	mkdir -p `dirname $(OBJDIR)/$@`
	$(CXX) $(XCFLAGS) $(INC) -c $< -o $(OBJDIR)/$@

$(OUT): $(OBJECTS)
	$(LD) $(LIBDIR) -o $(OUT) $(addprefix $(OBJDIR)/, $(OBJECTS)) $(XLDFLAGS) $(LIB)
