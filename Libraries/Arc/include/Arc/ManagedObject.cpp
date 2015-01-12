#include "ManagedObject.h"

#include "MemoryTracker.h"

void *Arc::ManagedObject::operator new( size_t size )
{
	// Allocate memory normally 
	return malloc(size);
}
void *Arc::ManagedObject::operator new[]( size_t size )
{
	// Allocate memory normally 
	return malloc(size);
}

void *Arc::ManagedObject::operator new( size_t size, int lineNumber, const char *filename )
{
	// Call base operator
	void* ptr = ::operator new(size);

	// Record allocation in memory tracker
	if (gp_MemoryTracker)
		gp_MemoryTracker->addAllocation((ManagedObject*)ptr, size, lineNumber, string(filename));

	return ptr;
}

void *Arc::ManagedObject::operator new[]( size_t size, int lineNumber, const char *filename )
{
	// Call base operator
	void* ptr = ::operator new(size);

	// Record allocation in memory tracker
	if (gp_MemoryTracker)
		gp_MemoryTracker->addAllocation((ManagedObject*)ptr, size, lineNumber, string(filename));

	return ptr;
}

void Arc::ManagedObject::operator delete( void *ptr )
{
	// Remove the allocation record if it exists
	if (gp_MemoryTracker)
		gp_MemoryTracker->removeAllocation((ManagedObject*)ptr);

	// Free memory normally 
	free(ptr);
}

void Arc::ManagedObject::operator delete[]( void *ptr )
{
	// Remove the allocation record if it exists
	if (gp_MemoryTracker)
		gp_MemoryTracker->removeAllocation((ManagedObject*)ptr);

	// Free memory normally 
	free(ptr);
}