#ifndef DUSK_MAIN_ARGS_H
#define DUSK_MAIN_ARGS_H

#include "func.h"
#include "usage.h"

struct DuskMainArgs
{
public:

    string InputFilename;
    string OutputFilename;

    string InputType;
    string OutputType;

    DuskMainArgs( void ) :
        InputFilename(),
        OutputFilename(),
        InputType("AUTO"),
        OutputType("AUTO")
    { }

};

bool parse_main_args( int argc, char* argv[], DuskMainArgs* args );

#endif // DUSK_MAIN_ARGS_H
