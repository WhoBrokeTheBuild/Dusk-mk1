#include "ScriptingSystem.h"

#include <Logging/Log.h>

using namespace Dusk::Logging;

bool Dusk::Scripting::ScriptingSystem::init(void)
{
	mp_LuaState = luaL_newstate();
	
	if (!mp_LuaState)
	{
		LogErrorFmt(getClassName(), "Failed to create Lua State");
		return false;
	}

	luaL_openlibs(mp_LuaState);

	return true;
}

bool Dusk::Scripting::ScriptingSystem::registerFunction(const string& func, LuaCallback callback)
{
	if (func.empty() == 0)
	{
		LogErrorFmt(getClassName(), "Cannot register function with no name");
		return false;
	}

	if (callback == nullptr)
	{
		LogErrorFmt(getClassName(), "Cannot register function with null callback");
		return false;
	}

	lua_register(mp_LuaState, func.c_str(), callback);
	return true;
}
