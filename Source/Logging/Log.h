#ifndef DUSK_LOG_H
#define DUSK_LOG_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <Arc/ArrayList.h>
#include <Arc/Map.h>

#include <Scripting/Scripting.h>

using Arc::ArrayList;
using Arc::Map;

namespace Dusk
{

namespace Logging
{

class Log
{
public:

	static bool AddInfoOutput( const string& filename, bool append = true );
	static bool RemoveInfoOutput( const string& filename );

	static bool AddErrorOutput( const string& filename, bool append = true );
	static bool RemoveErrorOutput( const string& filename );

	static void Info( const string& src, const string& msg, const string& file, const int& line );
	static void Error( const string& src, const string& msg, const string& file, const int& line );

	static void InfoFmt( const string& src, const string& fmt, const string& file, const int line, ... );
	static void ErrorFmt( const string& src, const string& fmt, const string& file, const int line, ... );

	static void CloseOutputs( void );

	static void InitScripting( void );
	static int Script_LogInfo( lua_State* pState );
	static int Script_LogError( lua_State* pState );

private:

	Log( void );
	Log( const Log& rhs );

	static string Format( const string& fmt, va_list args );

	static void Output( std::ostream& stream, const string& type, const string& src, const string& msg, const string& file, const int& line );

	static ArrayList<std::ostream*> s_Streams;

	static Map<string, int> s_InfoOutputs;
	static Map<string, int> s_ErrorOutputs;

};

#define LogInfo(SRC, MSG) Log::Info(SRC, MSG, string(__FILE__), __LINE__);
#define LogError(SRC, MSG) Log::Error(SRC, MSG, string(__FILE__), __LINE__);

#define LogInfoFmt(SRC, FMT, ...) Log::InfoFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);
#define LogErrorFmt(SRC, FMT, ...) Log::ErrorFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);

} // Logging

} // Dusk

#endif // DUSK_LOG_H
