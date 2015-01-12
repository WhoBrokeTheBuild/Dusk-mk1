#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "MainArgs.h"
#include "Functions.h"
#include "Map.h"
#include "ExtensionTypeMap.h"

#include "InterModel.h"

#include "ImportOBJ.h"
#include "ExportOBJ.h"
#include "ImportDSKM.h"
#include "ExportDSKM.h"

#include "ImportPNG.h"
#include "ExportPNG.h"

using std::string;
using std::map;

int main( int argc, char* argv[] )
{
    MainArgs args;
    ParseMainArgs(argc, argv, &args);

	SDL_Init(SDL_INIT_EVERYTHING);

    LoadExtensionTypeMap(STR_EXT_TYPES_MAP);

    if (args.InputType == "AUTO")
    {
        const string& in_ext = parse_ext(args.InputFilename);
        args.InputType = getTypeByExtension(in_ext);
    }

    if (args.OutputType == "AUTO")
    {
        const string& out_ext = parse_ext(args.OutputFilename);
        args.OutputType = getTypeByExtension(out_ext);
    }

    printf("Input: %s\nOutput: %s\n", args.InputType.c_str(), args.OutputType.c_str());

    const string& in_type_cat = args.InputType.substr(0, args.InputType.find('/'));
    const string& out_type_cat = args.OutputType.substr(0, args.OutputType.find('/'));

    if (in_type_cat != out_type_cat)
    {
        error("Type Category Mismatch");
    }

	InterModel model;
	InterTexture texture;
    if (args.InputType == "model/wavefront-obj")
    {
        ImportOBJ(args.InputFilename, &model);
	}
	else if (args.InputType == "model/dusk-engine-binary")
	{
		ImportDSKM(args.InputFilename, &model);
	}
	else if (args.InputType == "texture/png")
	{
		ImportPNG(args.InputFilename, &texture);
	}

    if (args.OutputType == "model/wavefront-obj")
    {
        ExportOBJ(args.OutputFilename, &model);
    }
    else if (args.OutputType == "model/dusk-engine-binary")
    {
        ExportDSKM(args.OutputFilename, &model);
	}
	else if (args.OutputType == "texture/png")
	{
		ExportPNG(args.InputFilename, &texture);
	}

    return 0;
}
