#ifndef DUSK_MAIN_ARGS_H
#define DUSK_MAIN_ARGS_H

#include <Util/Functions.h>
#include <Util/Usage.h>

struct MainArgs
{
public:

    string InputFilename;
    string OutputFilename;

    string InputType;
    string OutputType;

    MainArgs( void ) :
        InputFilename(),
        OutputFilename(),
        InputType("AUTO"),
        OutputType("AUTO")
    { }

};

bool ParseMainArgs( int argc, char* argv[], MainArgs* args );

#endif // DUSK_MAIN_ARGS_H
