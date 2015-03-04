#include "ExtensionTypeMap.h"

#include <sstream>

Map<string, string> gExtensionTypeMap;

void LoadExtensionTypeMap( const string& mappings )
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

        gExtensionTypeMap.add(ext, type);
    }
}

string getTypeByExtension( const string& ext )
{
    if (gExtensionTypeMap.containsKey(ext) == 0)
        return "";

    return gExtensionTypeMap[ext];
}
