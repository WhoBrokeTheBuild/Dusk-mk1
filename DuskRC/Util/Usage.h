#ifndef DUSK_USAGE_H
#define DUSK_USAGE_H

#include <cstdio>

#define STR_USAGE \
"Usage: duskrc INPUT OUTPUT [OPTION..] \n\n" \
"    -i, --input-type[=AUTO]     The input type of the file to be converted, or AUTO to autodetect\n" \
"    -o, --output-type[=AUTO]    The output type for the file to be converted to, or AUTO to autodetect\n"

inline void usage( void )
{
    printf("%s\n", STR_USAGE);
    exit(0);
}

#endif // DUSK_USAGE_H
