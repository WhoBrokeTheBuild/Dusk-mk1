#include "FileFunctions.h"

#include "Platform.h"

#if defined(ARC_OS_WINDOWS)

#define NOGDI
#include <Windows.h>

#elif defined(ARC_OS_LINUX)



#endif 

//bool Arc::Arc_FileExists( const string& filename )
//{
//
//}
//
//bool Arc::Arc_DirExists( const string& filename )
//{
//
//}
//
//bool Arc::Arc_IsDir( const string& filename )
//{
//
//}
//
//bool Arc::Arc_CreateDir( const string& filename )
//{
//#if defined(ARC_OS_WINDOWS)
//
//	CreateDirectory(filename.c_str(), NULL);
//
//#elif defined(ARC_OS_LINUX)
//
//
//
//#endif 
//
//	return true;
//}