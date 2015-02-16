#include "Log.h"

#include <Arc/StringFunctions.h>
#include <Scripting/ScriptingSystem.h>
#include <Program.h>

#include <string>
#include <fstream>
#include <cstdarg>
#include <ctime>

using std::string;
using Arc::Map;
using Arc::ArrayList;

using namespace Dusk::Scripting;

Map<string, int> Dusk::Logging::Log::s_InfoOutputs = Map<string, int>();
Map<string, int> Dusk::Logging::Log::s_ErrorOutputs = Map<string, int>();

ArrayList<std::ostream*> Dusk::Logging::Log::s_Streams = ArrayList<std::ostream*>();

void Dusk::Logging::Log::CloseOutputs( void )
{
	for (int i = 0; i < (int)s_Streams.getSize(); ++i)
	{
		const string& infoName = s_InfoOutputs.getIndexOf(i);
		const string& errorName = s_ErrorOutputs.getIndexOf(i);

		if (infoName == "stdout" || infoName == "stderr")
			continue;

		if (errorName == "stdout" || errorName == "stderr")
			continue;

		std::ofstream* pFile = (std::ofstream*)s_Streams[i];
		pFile->close();
		delete pFile;
	}

	s_InfoOutputs.clear();
	s_ErrorOutputs.clear();
	s_Streams.clear();
}

bool Dusk::Logging::Log::AddInfoOutput(const string& filename, bool append /*= true */)
{
	if (s_InfoOutputs.containsKey(filename))
		return false;

	if (filename == "stdout")
	{
		s_Streams.add(&std::cout);
	}
	else if (filename == "stderr")
	{
		s_Streams.add(&std::cerr);
	}
	else
	{
		std::ofstream* pFile = new std::ofstream();

		if (append)
			pFile->open(filename, std::ios_base::out | std::ios_base::app);
		else
			pFile->open(filename, std::ios_base::out | std::ios_base::trunc);

		if ( ! (*pFile))
			return false;

		s_Streams.add(pFile);
	}

	s_InfoOutputs.add(filename, s_Streams.getSize() - 1);

	return true;
}

bool Dusk::Logging::Log::RemoveInfoOutput( const string& filename )
{
	int streamInd = s_InfoOutputs[filename];

	if (streamInd == -1)
		return false;

	s_InfoOutputs.removeKey(filename);

	if ( ! s_ErrorOutputs.containsValue(streamInd))
		s_Streams.removeAt(streamInd);

	return true;
}

bool Dusk::Logging::Log::AddErrorOutput( const string& filename, bool append /*= true */ )
{
	if (s_ErrorOutputs.containsKey(filename))
		return false;

	if (filename == "stdout")
	{
		s_Streams.add(&std::cout);
	}
	else if (filename == "stderr")
	{
		s_Streams.add(&std::cerr);
	}
	else
	{
		std::ofstream* pFile = new std::ofstream();

		if (append)
			pFile->open(filename, std::ios_base::out | std::ios_base::app);
		else
			pFile->open(filename, std::ios_base::out | std::ios_base::trunc);

		if ( ! (*pFile))
			return false;

		s_Streams.add(pFile);
	}

	s_ErrorOutputs.add(filename, s_Streams.getSize() - 1);

	return true;
}

bool Dusk::Logging::Log::RemoveErrorOutput( const string& filename )
{
	int streamInd = s_ErrorOutputs[filename];

	if (streamInd == -1)
		return false;

	s_ErrorOutputs.removeKey(filename);

	if ( ! s_InfoOutputs.containsValue(streamInd))
		s_Streams.removeAt(streamInd);

	return true;
}

void Dusk::Logging::Log::Info( const string& src, const string& msg, const string& file, const int& line )
{
	auto end = s_InfoOutputs.itEnd();
	for (auto it = s_InfoOutputs.itBegin(); it != end; ++it)
	{
		Output(*s_Streams[it->second], "INF", src, msg, file, line);
	}
}

void Dusk::Logging::Log::Error( const string& src, const string& msg, const string& file, const int& line )
{
	auto end = s_ErrorOutputs.itEnd();
	for (auto it = s_ErrorOutputs.itBegin(); it != end; ++it)
	{
		Output(*s_Streams[it->second], "ERR", src, msg, file, line);
	}
}

void Dusk::Logging::Log::InfoFmt( const string& src, const string& fmt, const string& file, const int line, ... )
{
	va_list args;

	va_start(args, line);
	string msg = Format(fmt, args);
	va_end(args);

	auto end = s_InfoOutputs.itEnd();
	for (auto it = s_InfoOutputs.itBegin(); it != end; ++it)
	{
		Output(*s_Streams[it->second], "INF", src, msg, file, line);
	}
}

void Dusk::Logging::Log::ErrorFmt( const string& src, const string& fmt, const string& file, const int line, ... )
{
	va_list args;

	va_start(args, line);
	string msg = Format(fmt, args);
	va_end(args);

	auto end = s_ErrorOutputs.itEnd();
	for (auto it = s_ErrorOutputs.itBegin(); it != end; ++it)
	{
		Output(*s_Streams[it->second], "ERR", src, msg, file, line);
	}
}

void Dusk::Logging::Log::Output( std::ostream& stream, const string& type, const string& src, const string& msg, const string& file, const int& line )
{
	clock_t now = clock();
	float seconds = now / (float)CLOCKS_PER_SEC;

	int hours = (int)(seconds / 3600.0f);
	seconds -= hours * 3600.0f;

	int mins = (int)(seconds / 60.0f);
	seconds -= mins * 60.0f;

	int secs = (int)seconds;
	seconds -= secs;

	int ms = (int)(seconds * 1000.0f);

	stream << "+" << hours << "." << mins << "." << secs << "." << ms << " " << type << " <" << Arc::Arc_Basename(file) << ":" << line << "> " << src << ": " << msg << std::endl;
}

string Dusk::Logging::Log::Format( const string& fmt, va_list args )
{
	const int BUFFER_MAX = 4096;
	char buffer[BUFFER_MAX];

	vsnprintf(buffer, BUFFER_MAX, fmt.c_str(), args);

	return string(buffer);
}

void Dusk::Logging::Log::InitScripting(void)
{
	ScriptingSystem* pScriptingSystem = Program::Inst().getScriptingSystem();
}

int Dusk::Logging::Log::Script_LogInfo(lua_State* pState)
{
	int argc = lua_gettop(pState);

	LogInfo("Script", lua_tostring(pState, 1));

	return 0;
}

int Dusk::Logging::Log::Script_LogError(lua_State* pState)
{
	int argc = lua_gettop(pState);

	LogError("Script", lua_tostring(pState, 1));

	return 0;
}
