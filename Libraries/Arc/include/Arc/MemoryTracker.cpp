#include "MemoryTracker.h"

#include "ManagedObject.h"
#include "StringFunctions.h"

Arc::MemoryTracker* Arc::gp_MemoryTracker = nullptr;

bool Arc::Arc_InitMemoryTracker( void )
{
	if (gp_MemoryTracker == nullptr)
	{
		gp_MemoryTracker = new Arc::MemoryTracker();
		return true;
	}

	return false;
}

void Arc::Arc_CleanupMemoryTracker( void )
{
	delete gp_MemoryTracker;
}

void Arc::MemoryTracker::addAllocation( ManagedObject *ptr, size_t size, int lineNumber, string filename )
{
	if (m_Allocations.containsKey(ptr))
	{
		//ERROR(toString(), "Element already in map");
		return;
	}

	AllocationRecord rec(m_AllocationIndex, size, lineNumber, filename);
	m_Allocations.add(ptr, rec);

	++m_AllocationIndex;
}

bool Arc::MemoryTracker::removeAllocation( ManagedObject *ptr )
{
	if (m_Allocations.isEmpty() || ! m_Allocations.containsKey(ptr))
		return false;

	m_Allocations.removeKey(ptr);
	return true;
}

void Arc::MemoryTracker::printAllocations( std::ostream& stream )
{
	stream << "Allocations: \n";

	for (auto it = m_Allocations.itBegin(); it != m_Allocations.itEnd(); ++it)
	{
		stream << "#" << it->second.Num
			   << ": (address: #" << it->first << ") "
			   << it->first->getClassName() << "\n"
			   << "\t In " << Arc_Basename(it->second.Filename)
			   << " On Line " << it->second.LineNum << "\n";
	}
}
