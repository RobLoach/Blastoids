#include "variable.h"



#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string>
#include <sstream>
//#include <cstdlib>

namespace System{


ScriptVariable::operator std::string() const{
	std::string output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output = ConvertTo<std::string>(lua_tonumber(state, -1));
		break;
	case LUA_TBOOLEAN:
		output = (lua_toboolean(state, -1) ? "true" : "false");
		break;
	case LUA_TSTRING:
		output = std::string(lua_tostring(state, -1));
		break;
	default:
		output = "";
	}
	lua_pop(state, 1);
	return output;
}

ScriptVariable::operator char*() const{
	char* output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output =  ConvertTo<char*>((long)lua_tonumber(state, -1));
		break;
	case LUA_TBOOLEAN:
		output = lua_toboolean(state, -1) ? (char*)("true") : (char*)("false");
		break;
	case LUA_TSTRING:
		output =  (char*)(lua_tostring(state, -1));
		break;
	default:
		output =  "";
	}
	lua_pop(state, 1);
	return output;
}

ScriptVariable::operator long() const{
	long output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output = (long)lua_tonumber(state, -1);
		break;
	case LUA_TBOOLEAN:
		output = lua_toboolean(state, -1);
		break;
	case LUA_TSTRING:
		output = ConvertTo<long>(lua_tostring(state, -1));
		break;
	default:
		output =  0;
	}
	lua_pop(state, 1);
	return output;
}



ScriptVariable::operator int() const{
	long output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output = (int)lua_tonumber(state, -1);
		break;
	case LUA_TBOOLEAN:
		output = lua_toboolean(state, -1);
		break;
	case LUA_TSTRING:
		output = ConvertTo<int>(lua_tostring(state, -1));
		break;
	default:
		output = 0;
	}
	lua_pop(state, 1);
	return output;
}

ScriptVariable::operator float() const{
	float output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output = (float)lua_tonumber(state, -1);
		break;
	case LUA_TBOOLEAN:
		output = lua_toboolean(state, -1);
		break;
	case LUA_TSTRING:
		output = ConvertTo<float>(lua_tostring(state, -1));
		break;
	default:
		output = 0;
	}
	lua_pop(state, 1);
	return output;
}

ScriptVariable::operator double() const{
	double output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output = (double)lua_tonumber(state, -1);
		break;
	case LUA_TBOOLEAN:
		output = lua_toboolean(state, -1);
		break;
	case LUA_TSTRING:
		output = ConvertTo<double>(lua_tostring(state, -1));
		break;
	default:
		output = 0;
	}
	lua_pop(state, 1);
	return output;
}


ScriptVariable::operator bool() const{
	bool output;
	lua_getglobal(state, name.c_str());
	switch(lua_type(state, -1)){
	case LUA_TNUMBER:
		output = (((long)lua_tonumber(state, -1)) != 0);
		break;
	case LUA_TBOOLEAN:
		output = lua_toboolean(state, -1);
		break;
	case LUA_TSTRING:
		output = (lua_tostring(state, -1) == "true");
		break;
	default:
		output = false;
	}
	lua_pop(state, 1);
	return output;
}


ScriptVariable& ScriptVariable::operator =(int value) {
	lua_pushnumber(state, value);
	lua_setglobal(state, name.c_str());
	return *this;
}


ScriptVariable& ScriptVariable::operator =(long value) {
	lua_pushnumber(state, value);
	lua_setglobal(state, name.c_str());
	return *this;
}


ScriptVariable& ScriptVariable::operator =(float value) {
	lua_pushnumber(state, value);
	lua_setglobal(state, name.c_str());
	return *this;
}


ScriptVariable& ScriptVariable::operator =(double value) {
	lua_pushnumber(state, value);
	lua_setglobal(state, name.c_str());
	return *this;
}


ScriptVariable& ScriptVariable::operator =(bool value) {
	lua_pushboolean(state, value);
	lua_setglobal(state, name.c_str());
	return *this;
}


ScriptVariable& ScriptVariable::operator =(std::string value) {
	lua_pushstring(state, value.c_str());
	lua_setglobal(state, name.c_str());
	return *this;
}


ScriptVariable& ScriptVariable::operator =(char* value) {
	lua_pushstring(state, value);
	lua_setglobal(state, name.c_str());
	return *this;
}

int ScriptVariable::Type(){
	lua_getglobal(state, name.c_str());
	return lua_type(state, -1);
}

std::string ScriptVariable::Typename(){
	lua_getglobal(state, name.c_str());
	return lua_typename(state, lua_type(state, -1));
}

}
