#if !defined(_INCLUDE_ARGUMENTS_H_)
#define _INCLUDE_ARGUMENTS_H_


#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <string>

#include "variable.h"

namespace System{

class CArguments{
	public:
	int argumentindex;
	lua_State* state;
	CArguments() : argumentindex(0) {}
	~CArguments(){ }
	CArguments& operator>>(std::string& variable);
	CArguments& operator>>(int& variable);
	CArguments& operator>>(float& variable);
	CArguments& operator>>(double& variable);
	CArguments& operator>>(bool& variable);
	CArguments& operator>>(long& variable);
};

}


#endif
