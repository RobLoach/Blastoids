#include "script.h"


#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <vector>
#include "variable.h"

namespace System{


	ScriptEngine::ScriptEngine(){
	    state = lua_open();
	    lua_baselibopen(state);
		lua_iolibopen(state);
	    lua_strlibopen(state);
	    lua_mathlibopen(state);
		
		luaopen_table(state);
		
		Arguments.state = state;
	}
	
	ScriptEngine::~ScriptEngine(){
		lua_setgcthreshold(state, 0);
	    lua_close(state);
	}

	bool ScriptEngine::LoadString(std::string data){
		luaL_loadbuffer(state, data.c_str(), data.size(), "line");
		lua_pcall(state, 0, 0, 0);
	}
	
	bool ScriptEngine::LoadFile(std::string filename)
	{
	    if(luaL_loadfile(state, filename.c_str()) != 0){
	        if(lua_isstring(state,-1))
	            error = lua_tostring(state, -1 );
	        else
	        	error = "Unknown loading error";
			return false;
	    }
	    if(lua_pcall(state, 0, LUA_MULTRET, 0) != 0){
	        if(lua_isstring(state,-1))
	            error = lua_tostring(state, -1 );
	        else
	            error = "Unknown call message";
			return false;
	    }
		return true;
	}

	bool ScriptEngine::VariableExists(std::string name){
		lua_getglobal(state, name.c_str());
		return !((bool)lua_isnil(state, -1) || (bool)lua_isfunction(state, -1) || (bool)lua_iscfunction(state,-1));
	}


	bool ScriptEngine::CallFunctionFinal(std::string name, std::string arguments, std::string* output){
		lua_getglobal(state, name.c_str());
		if(lua_isfunction(state, -1)){

			// Put in arguments
			int numArguments = 0;
			if(arguments != ""){
				arguments += "|";
				int pos;
				while((pos = arguments.find("|", 0)) != std::string::npos){
					lua_pushstring(state, arguments.substr(0,pos).c_str());
					arguments.erase(0,pos+1);
					numArguments++;
				}
			}

			// Call
			if (lua_pcall(state, numArguments, (output == NULL)?0:1, 0) != 0){
				error = "Error calling function `" + name + "': " + lua_tostring(state, -1);
				return false;
			}

			// Return value
			if (!lua_isstring(state, -1)){
				error = "function `" + name + "' must return a string";
				return false;
			}
			if(output != NULL)
				*output = lua_tostring(state, -1);
			lua_pop(state, 1);
			return true;
		} else {
			error = "Function `" + name + "' not found";
			return false;
		}
	}


	ScriptVariable& ScriptEngine::Variable(std::string name){
		ScriptVariable* newVar = new ScriptVariable(state, name);
		return *newVar;
	}

	ScriptVariable& ScriptEngine::operator[](std::string name){
		ScriptVariable* newVar = new ScriptVariable(state, name);
		return *newVar;
	}

	bool ScriptEngine::BindFunction(int (*function)(lua_State*), std::string name){
		lua_pushcfunction(state, function);
	    lua_setglobal(state, name.c_str());
		lua_settable(state, LUA_REGISTRYINDEX);
	}

	int ScriptEngine::Return(std::string returnvalue){
		lua_pushstring(state, returnvalue.c_str());
		Arguments.argumentindex = 0;
		return 1;
	}

	int ScriptEngine::Return(int returnvalue){
		lua_pushnumber(state, returnvalue);
		Arguments.argumentindex = 0;
		return 1;
	}

	int ScriptEngine::Return(long returnvalue){
		lua_pushnumber(state, returnvalue);
		Arguments.argumentindex = 0;
		return 1;
	}

	int ScriptEngine::Return(float returnvalue){
		lua_pushnumber(state, returnvalue);
		Arguments.argumentindex = 0;
		return 1;
	}

	int ScriptEngine::Return(double returnvalue){
		lua_pushnumber(state, returnvalue);
		Arguments.argumentindex = 0;
		return 1;
	}

	int ScriptEngine::Return(bool returnvalue){
		lua_pushboolean(state, (returnvalue == false)?0:1);
		Arguments.argumentindex = 0;
		return 1;
	}

	int ScriptEngine::Return(){
		Arguments.argumentindex = 0;
		return 0;
	}
	ScriptEngine Script;
}
