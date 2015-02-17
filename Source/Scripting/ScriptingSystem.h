#pragma once

#ifndef DUSK_SCRIPTING_SYSTEM_H
#define DUSK_SCRIPTING_SYSTEM_H

#include <Arc/ManagedObject.h>
#include <Scripting/Scripting.h>

namespace Dusk
{

namespace Scripting
{

typedef int (*LuaCallback)( lua_State* pState );

class ScriptingSystem :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName( void ) const { return "Scripting System"; }

	bool init(void);
	bool registerFunction(const string& func, LuaCallback callback);
	bool runScript(const string& script);

	inline lua_State* getLuaState(void) { return mp_LuaState; }

private:

	lua_State*		mp_LuaState;

};

} // namespace Scripting

} // namespace Dusk

#endif // DUSK_SCRIPTING_SYSTEM_H