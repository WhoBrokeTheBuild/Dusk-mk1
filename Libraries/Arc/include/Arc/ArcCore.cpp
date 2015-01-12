#include "ArcCore.h"

#include "RandomFunctions.h"

bool Arc::Arc_InitCore( void )
{
	bool success = false;

	Arc::Arc_InitRandom();
	success = Arc::Arc_InitMemoryTracker();

	if ( ! success)
		goto error;

	return true;

error:

	return false;

}