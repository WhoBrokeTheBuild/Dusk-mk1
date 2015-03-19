/** @file Log.h */
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

/// A static class to handle logging
/**
 * The Logging class handles the Logging outputs and has functions for
 * outputting both info and error messages. Outputs need to be set up at the
 * start, and then to actually log information you will use the LogInfo,
 * LogError, LogInfoFmt, and LogErrorFmt macros, as they will include the
 * __FILE__ and __LINE__ defines.
 */
class Log
{
public:

	/// Add a new info output.
	/**
	 * Adds a new info output file or output stream, and whether or not you want
	 * to append to the file or truncate the file and output from the beginning.
	 * @param filename The filename of the log file or "stdout" or "stderr" to
	 * use standard out or standard error.
	 * @param append True if you want to append to the file or false if you want
	 * to truncate it
	 * @returns True if adding the output succeeded, false otherwise
	 */
	static bool AddInfoOutput( const string& filename, bool append = true );
	/// Removes a given info output by its filename or stream name
	static bool RemoveInfoOutput( const string& filename );

	/// Add a new error output.
	/**
	 * Adds a new error output file or output stream, and whether or not you want
	 * to append to the file or truncate the file and output from the beginning.
	 * @param filename The filename of the log file or "stdout" or "stderr" to
	 * use standard out or standard error.
	 * @param append True if you want to append to the file or false if you want
	 * to truncate it
	 * @returns True if adding the output succeeded, false otherwise
	 */
	static bool AddErrorOutput( const string& filename, bool append = true );
	/// Removes a given error output by its filename or stream name
	static bool RemoveErrorOutput( const string& filename );

	///
	static void Info( const string& src, const string& msg,
		 								const string& file, const int& line );
	static void Error( const string& src, const string& msg,
										 const string& file, const int& line );

	static void InfoFmt( const string& src, const string& fmt,
		 									 const string& file, const int line, ... );
	static void ErrorFmt( const string& src, const string& fmt,
		 										const string& file, const int line, ... );

  /// Close all outputs that have been opened.
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

/// Log an info message from the given source.
/**
 * Logs a message to the info logs in the given format:
 * +h.m.s.ms INF <FILE:LINE> SRC: MSG
 * @param SRC The Source of the message, often the class name or getClassName()
 * @param MSG The message to be displayed
 */
#define LogInfo(SRC, MSG) Log::Info(SRC, MSG, string(__FILE__), __LINE__);

/// Log an error message from the given source.
/**
 * Logs a message to the error logs in the given format:
 * +h.m.s.ms ERR <FILE:LINE> SRC: MSG
 * @param SRC The Source of the message, often the class name or getClassName()
 * @param MSG The message to be displayed
 */
#define LogError(SRC, MSG) Log::Error(SRC, MSG, string(__FILE__), __LINE__);

#define LogInfoFmt(SRC, FMT, ...) Log::InfoFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);
#define LogErrorFmt(SRC, FMT, ...) Log::ErrorFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);

} // Logging

} // Dusk

#endif // DUSK_LOG_H
