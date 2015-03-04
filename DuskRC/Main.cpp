#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Arc/Map.h>

#include <Util/MainArgs.h>
#include <Util/Functions.h>
#include <Util/ExtensionTypeMap.h>

#include <Intermediate/InterModel.h>
#include <Intermediate/InterTexture.h>

#include <Import/ImportOBJ.h>
#include <Import/ImportDSKM.h>
#include <Import/ImportPNG.h>
#include <Import/ImportJPG.h>
#include <Import/ImportTGA.h>
#include <Import/ImportDSKT.h>

#include <Export/ExportOBJ.h>
#include <Export/ExportDSKM.h>
#include <Export/ExportPNG.h>
#include <Export/ExportJPG.h>
#include <Export/ExportTGA.h>
#include <Export/ExportDSKT.h>

using std::string;
using Arc::Map;

typedef bool (*InportModelFunc)(const string&, InterModel*);
typedef bool (*ExportModelFunc)(const string&, InterModel*);

typedef bool(*InportTextureFunc)(const string&, InterTexture*);
typedef bool(*ExportTextureFunc)(const string&, InterTexture*);

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

	if (in_type_cat == "model")
	{
		Map<string, InportModelFunc> importFuncs;
		Map<string, ExportModelFunc> exportFuncs;

		importFuncs.add("model/wavefront-obj", ImportOBJ);
		importFuncs.add("model/dusk-engine-binary", ImportDSKM);

		exportFuncs.add("model/wavefront-obj", ExportOBJ);
		exportFuncs.add("model/dusk-engine-binary", ExportDSKM);

		if (!importFuncs.containsKey(args.InputType) || !exportFuncs.containsKey(args.OutputType))
		{
			printf("Unsupported Input/Output Types\n");
			return 1;
		}

		InterModel model;
		importFuncs[args.InputType](args.InputFilename, &model);
		exportFuncs[args.OutputType](args.OutputFilename, &model);
	}
	else if (in_type_cat == "texture")
	{
		Map<string, InportTextureFunc> importFuncs;
		Map<string, ExportTextureFunc> exportFuncs;

		importFuncs.add("texture/png",                  ImportPNG);
		importFuncs.add("texture/jpg",                  ImportJPG);
		importFuncs.add("texture/targa",                ImportTGA);
		importFuncs.add("texture/dusk-engine-binary",   ImportDSKT);

		exportFuncs.add("texture/png",                  ExportPNG);
		exportFuncs.add("texture/jpg",                  ExportJPG);
		exportFuncs.add("texture/targa",                ExportTGA);
		exportFuncs.add("texture/dusk-engine-binary",   ExportDSKT);

		if (!importFuncs.containsKey(args.InputType) || !exportFuncs.containsKey(args.OutputType))
		{
			printf("Unsupported Input/Output Types\n");
			return 1;
		}

		InterTexture texture;
		importFuncs[args.InputType](args.InputFilename, &texture);
		exportFuncs[args.OutputType](args.OutputFilename, &texture);
	}

    return 0;
}
