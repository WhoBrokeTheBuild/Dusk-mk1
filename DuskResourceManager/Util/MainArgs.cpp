#include "MainArgs.h"

bool ParseMainArgs( int argc, char* argv[], MainArgs* args )
{
    if (argc < 3)
        usage();

    if (string(argv[1]) == "--help")
        usage();

    args->InputFilename = argv[1];
    args->OutputFilename = argv[2];

    for (int i = 3; i < argc; ++i)
    {
        const string& arg = argv[i];

        if (arg == "-i" || arg == "--input-type")
        {
            if (i + 1 >= argc)
                break;

            ++i;
            args->InputType = argv[i];
        }
        else if (arg == "-o" || arg == "--output-type")
        {
            if (i + 1 >= argc)
                break;

            ++i;
            args->OutputType = argv[i];
        }
    }

    return true;
}
