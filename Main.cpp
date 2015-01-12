#include <Arc/MemoryTracker.h>

#include "Program.h"
#include "Log.h"
#include "ShaderManager.h"

int main(int argc, char* argv[])
{
    Log::AddInfoOutput("stdout");
    Log::AddErrorOutput("stderr");

    Log::AddInfoOutput("info.log", false);
    Log::AddErrorOutput("error.log", false);

    Log::AddInfoOutput("combined.log", false);
    Log::AddErrorOutput("combined.log", false);

    Arc::Arc_InitMemoryTracker();

    Program::getInstance().start();

    if (Arc::Arc_GetMemoryAllocationCount() > 0)
        Arc::Arc_PrintMemoryAllocations();

    Arc::Arc_CleanupMemoryTracker();

    return 0;
}
