#include "ScriptingSystem.h"

#include <Logging/Log.h>

using namespace Dusk::Logging;

bool Dusk::Scripting::ScriptingSystem::init(void)
{
	mp_LuaState = luaL_newstate();

	if (!mp_LuaState)
	{
		LogError(getClassName(), "Failed to create Lua State");
		return false;
	}

	luaL_openlibs(mp_LuaState);

	return true;
}

bool Dusk::Scripting::ScriptingSystem::registerFunction(const string& func, LuaCallback callback)
{
	if (func.empty())
	{
		LogError(getClassName(), "Cannot register function with no name");
		return false;
	}

	if (callback == nullptr)
	{
		LogError(getClassName(), "Cannot register function with null callback");
		return false;
	}

	lua_register(mp_LuaState, func.c_str(), callback);
	return true;
}

bool Dusk::Scripting::ScriptingSystem::runScript(const string& script)
{
	int status = luaL_loadfile(mp_LuaState, script.c_str());

	if (status == 0)
	{
		status = lua_pcall(mp_LuaState, 0, LUA_MULTRET, 0);
	}
	else
	{
		LogErrorFmt("Script", "%s", lua_tostring(mp_LuaState, -1));
		lua_pop(mp_LuaState, 1); // remove error message
        return false;
	}

	return true;
}
