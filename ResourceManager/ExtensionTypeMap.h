#ifndef DUSK_EXTENSION_TYPE_MAP
#define DUSK_EXTENSION_TYPE_MAP

#include <string>

#include "Map.h"

using std::string;

#define STR_EXT_TYPES_MAP \
"dskm model/dusk-engine-binary\n" \
"dskt texture/dusk-engine-binary\n" \
"dskc config/dusk-engine-binary\n" \
"obj model/wavefront-obj\n" \
"fbx model/maya-binary\n" \
"png texture/png\n" \
"tga texture/targa\n"

extern Map<string, string> gExtensionTypeMap;

void LoadExtensionTypeMap( const string& mappings );
string getTypeByExtension( const string& ext );

#endif // DUSK_EXTENSION_TYPE_MAP