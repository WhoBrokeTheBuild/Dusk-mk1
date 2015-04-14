
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
XCFLAGS = $(CFLAGS) -g -DDEBUG -D_CRT_SECURE_NO_WARNINGS
XLDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = ../obj/Dusk
OUT = ../dusktest

SOURCES = \
Events/Event.cpp \
Events/IEventDispatcher.cpp \
Graphics/GraphicsContext.cpp \
Graphics/GraphicsSystem.cpp \
Graphics/Material.cpp \
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
World/Camera.cpp \
World/Entity.cpp \
World/Skybox.cpp \
Program.cpp \
Main.cpp \
lodepng/lodepng.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CXX) $(XCFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	$(LD) $(LIBDIR) -o $(OUT) $(OBJECTS) $(XLDFLAGS) $(LIB)
