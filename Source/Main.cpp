#include <Arc/MemoryTracker.h>

#include <Program.h>
#include <Logging/Log.h>

#include <limits>

using namespace Dusk;
using namespace Dusk::Logging;

int main(int argc, char* argv[])
{
    Log::AddInfoOutput("stdout");
    Log::AddErrorOutput("stderr");

    Log::AddInfoOutput("info.log", false);
    Log::AddErrorOutput("error.log", false);

    Arc::Arc_InitMemoryTracker();

    Program::Inst().start();

    if (Arc::Arc_GetMemoryAllocationCount() > 0)
    {
        Arc::Arc_PrintMemoryAllocations();

        std::cout << "Press Enter to continue...";
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }

    Arc::Arc_CleanupMemoryTracker();

    return 0;
}
