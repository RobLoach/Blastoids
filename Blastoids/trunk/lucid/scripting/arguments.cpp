#include "arguments.h"


#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

namespace System{

	CArguments& CArguments::operator>>(std::string& variable){
		variable = luaL_checkstring(state, ++argumentindex);
	    return *this;
	}

	CArguments& CArguments::operator>>(int& variable){
		variable = luaL_checkint(state, ++argumentindex);
	    return *this;
	}

	CArguments& CArguments::operator>>(long& variable){
		variable = luaL_checklong(state, ++argumentindex);
	    return *this;
	}
	CArguments& CArguments::operator>>(float& variable){
		variable = luaL_checknumber(state, ++argumentindex);
	    return *this;
	}

	CArguments& CArguments::operator>>(double& variable){
		variable = luaL_checknumber(state, ++argumentindex);
	    return *this;
	}

	CArguments& CArguments::operator>>(bool& variable){
		variable = lua_toboolean(state,++argumentindex);
	    return *this;
	}

}
