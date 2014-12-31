#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

#include "usage.h"
#include "ext_types_map.h"
#include "func.h"

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
    if (argc < 3)
        usage();

    if (argv[1] == "--help")
        usage();

    load_ext_type_map(STR_EXT_TYPES_MAP);

    string in_type = "";
    string out_type = "";

    for (int i = 3; i < argc; ++i)
    {
        const string& arg = argv[i];

        if (arg == "-i" || arg == "--input-type")
        {
            if (i + 1 >= argc)
                break;

            ++i;
            in_type = argv[i];
        }
        else if (arg == "-o" || arg == "--output-type")
        {
            if (i + 1 >= argc)
                break;

            ++i;
            out_type = argv[i];
        }
    }

    if (in_type.empty())
    {
        const string& in_ext = parse_ext(argv[1]);
        in_type = get_rc_type(in_ext);
    }

    if (out_type.empty())
    {
        const string& out_ext = parse_ext(argv[2]);
        out_type = get_rc_type(out_ext);
    }

    printf("Input: %s\nOutput: %s\n", in_type.c_str(), out_type.c_str());

    const string& in_type_cat = in_type.substr(0, in_type.find('/'));
    const string& out_type_cat = out_type.substr(0, out_type.find('/'));

    if (in_type_cat != out_type_cat)
    {
        error("Type Category Mismatch");
    }

    return 0;
}
