
WORKDIR = `pwd`

CXX = g++
AR = ar
LD = g++

INC = -I../Libraries/glm/include -I../Libraries/Arc/include -I/usr/include/SDL2 -I./
LIBDIR = -L../Libraries/Arc/lib -L/usr/lib64
LIB = -lSDL2 -lSDL2main -lSDL2_image -lArcCore -lpng
CFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
LDFLAGS =

# Debug
XCFLAGS = $(CFLAGS) -g -DDEBUG
XLDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = ../obj/DuskRC
OUT = ../duskrc

SOURCES = \
Export/ExportDSKM.cpp \
Export/ExportDSKT.cpp \
Export/ExportJPG.cpp \
Export/ExportOBJ.cpp \
Export/ExportPNG.cpp \
Export/ExportTGA.cpp \
Import/ImportDSKM.cpp \
Import/ImportDSKT.cpp \
Import/ImportJPG.cpp \
Import/ImportOBJ.cpp \
Import/ImportPNG.cpp \
Import/ImportTGA.cpp \
Util/ExtensionTypeMap.cpp \
Util/Functions.cpp \
Intermediate/InterMaterial.cpp \
Intermediate/InterMesh.cpp \
Intermediate/InterTexture.cpp \
Util/MainArgs.cpp \
Main.cpp \
savepng/savepng.cpp

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
