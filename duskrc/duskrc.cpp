#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

#include "func.h"
#include "main_args.h"
#include "ext_types_map.h"

#include "inter_model.h"

#include "imp_obj.h"
#include "exp_obj.h"

using std::string;
using std::map;

map<string, string> g_ext_types_map;

void load_ext_type_map( const string& mappings )
{
    std::istringstream ss(mappings);

    string line, ext, type;
    std::stringstream liness;
    while (std::getline(ss, line))
    {
        if (line.empty())
            break;

        liness.clear();
        liness.str(line);

        liness >> ext;
        liness >> type;

        g_ext_types_map.insert(std::pair<string, string>(ext, type));
    }
}

string get_rc_type( const string& ext )
{
    if (g_ext_types_map.count(ext) == 0)
        return "";

    return g_ext_types_map[ext];
}

int main( int argc, char* argv[] )
{
    DuskMainArgs args;
    parse_main_args(argc, argv, &args);

    load_ext_type_map(STR_EXT_TYPES_MAP);

    if (args.InputType == "AUTO")
    {
        const string& in_ext = parse_ext(args.InputFilename);
        args.InputType = get_rc_type(in_ext);
    }

    if (args.OutputType == "AUTO")
    {
        const string& out_ext = parse_ext(args.OutputFilename);
        args.OutputType = get_rc_type(out_ext);
    }

    printf("Input: %s\nOutput: %s\n", args.InputType.c_str(), args.OutputType.c_str());

    const string& in_type_cat = args.InputType.substr(0, args.InputType.find('/'));
    const string& out_type_cat = args.OutputType.substr(0, args.OutputType.find('/'));

    if (in_type_cat != out_type_cat)
    {
        error("Type Category Mismatch");
    }

    if (args.InputType == "model/wavefront-obj")
    {
        DuskInterModel model;
        import_obj(args.InputFilename, &model);
    }

    return 0;
}
