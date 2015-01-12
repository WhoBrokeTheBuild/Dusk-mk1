#ifndef DUSK_LOG_H
#define DUSK_LOG_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <Arc/ArrayList.h>
#include <Arc/Map.h>

using Arc::ArrayList;
using Arc::Map;

class Log
{
public:

	static bool AddInfoOutput( const string& filename, bool append = true );
	static bool RemoveInfoOutput( const string& filename );

	static bool AddErrorOutput( const string& filename, bool append = true );
	static bool RemoveErrorOutput( const string& filename );

	static void ExtInfo( const string& src, const string& msg, const string& file, const int& line );
	static void ExtError( const string& src, const string& msg, const string& file, const int& line );

	static void ExtInfoFmt( const string& src, const string& fmt, const string& file, const int line, ... );
	static void ExtErrorFmt( const string& src, const string& fmt, const string& file, const int line, ... );

	static void CloseOutputs( void );

private:

	Log( void );
	Log( const Log& rhs );

	static string Format( const string& fmt, va_list args );

	static void Output( std::ostream& stream, const string& type, const string& src, const string& msg, const string& file, const int& line );

	static ArrayList<std::ostream*> s_Streams;

	static Map<string, int> s_InfoOutputs;
	static Map<string, int> s_ErrorOutputs;

};

#define LogInfo(SRC, MSG) Log::ExtInfo(SRC, MSG, string(__FILE__), __LINE__);
#define LogError(SRC, MSG) Log::ExtError(SRC, MSG, string(__FILE__), __LINE__);

#define LogInfoFmt(SRC, FMT, ...) Log::ExtInfoFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);
#define LogErrorFmt(SRC, FMT, ...) Log::ExtErrorFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);

#endif // DUSK_LOG_H
