/******************************************************************************\

	Title:
		Lua C API Wrapper

	Author:
		Rob Loach (http://www.robloach.net)
	
	Date:
		April 7, 2005

	Description:
		A Lua C API class wrapper.
	
	Usage:
		ScriptEngine script;
		script.LoadFile("script.lua");
		
		script["VariableName"] = 5;
		cout << script["VariableName"].ToString();
		
		script.CallFunction("FunctionName", "Argument1", 2, 4.32);
		
		// To bind a C function, you must make the function first:
		int CFunctionSum(lua_State* state){
			int arg1;
			float arg2;
			script.Arguments >> arg1 >> arg2; // get argument 1 and 2
			return script.Return(arg1 + arg2);
		}
		// Then bind it to lua:
		script.BindFunction(CFunctionSum, "CSum");

\******************************************************************************/


#if !defined(_INCLUDED_SCRIPTENGINE_H_)
#define _INCLUDED_SCRIPTENGINE_H_


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <string>
#include <sstream>

#include "variable.h"
#include "arguments.h"

namespace System{



class ScriptEngine {
public:

	CArguments Arguments;

	ScriptEngine();
    ~ScriptEngine();

	bool LoadFile(std::string filename);

	lua_State* GetState(){ return state; }
	std::string GetLastError(){ return error; }

	ScriptVariable& Variable(std::string name);
	ScriptVariable& operator[](std::string name);
	bool VariableExists(std::string name);

	// Calls a function and pass in arguments delimitered by |
	bool CallFunctionFinal(std::string name, std::string arguments, std::string* output = NULL);

	// Calls a function and return becomes output... Arguments delimitered by |
	//bool CallFunction(std::string name, std::string& output, CArguments ArgumentList);

	bool BindFunction(int (*function)(lua_State*), std::string name);
	
	template<class T>
	T GetVariable(std::string variablename, T defaultvalue){
		if(VariableExists(variablename))
			return Variable(variablename);
		else
			return defaultvalue;
	}




	template<class T>
	bool BindVariable(T* p, std::string name){
		lua_newuserdata(state, sizeof(T));
		lua_pushlightuserdata(state, (void*)p);
	    lua_setglobal(state, name.c_str());
	}

	bool LoadString(std::string data);

	int Return();
	int Return(int returnvalue);
	int Return(long returnvalue);
	int Return(float returnvalue);
	int Return(double returnvalue);
	int Return(bool returnvalue);
	int Return(std::string returnvalue);

	std::string CallFunction(std::string name){
		std::string out;
		CallFunctionFinal(name, "", &out);
		return out;
	}
	
	template <class A>
	std::string CallFunction(std::string name, A arg1){
		std::string arg = ConvertTo<std::string>(arg1);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B>
	std::string CallFunction(std::string name, A arg1, B arg2){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B, class C>
	std::string CallFunction(std::string name, A arg1, B arg2, C arg3){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2) + "|" + ConvertTo<std::string>(arg3);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B, class C, class D>
	std::string CallFunction(std::string name, A arg1, B arg2, C arg3, D arg4){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2) + "|" + ConvertTo<std::string>(arg3) + "|" + ConvertTo<std::string>(arg4);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B, class C, class D, class E>
	std::string CallFunction(std::string name, A arg1, B arg2, C arg3, D arg4, E arg5){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2) + "|" + ConvertTo<std::string>(arg3) + "|" + ConvertTo<std::string>(arg4) + "|" + ConvertTo<std::string>(arg5);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B, class C, class D, class E, class F>
	std::string CallFunction(std::string name, A arg1, B arg2, C arg3, D arg4, E arg5, F arg6){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2) + "|" + ConvertTo<std::string>(arg3) + "|" + ConvertTo<std::string>(arg4) + "|" + ConvertTo<std::string>(arg5) + "|" + ConvertTo<std::string>(arg6);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B, class C, class D, class E, class F, class G>
	std::string CallFunction(std::string name, A arg1, B arg2, C arg3, D arg4, E arg5, F arg6, G arg7){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2) + "|" + ConvertTo<std::string>(arg3) + "|" + ConvertTo<std::string>(arg4) + "|" + ConvertTo<std::string>(arg5) + "|" + ConvertTo<std::string>(arg6) + "|" + ConvertTo<std::string>(arg7);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}
	
	template <class A, class B, class C, class D, class E, class F, class G, class H>
	std::string CallFunction(std::string name, A arg1, B arg2, C arg3, D arg4, E arg5, F arg6, G arg7, H arg8){
		std::string arg = ConvertTo<std::string>(arg1) + "|" + ConvertTo<std::string>(arg2) + "|" + ConvertTo<std::string>(arg3) + "|" + ConvertTo<std::string>(arg4) + "|" + ConvertTo<std::string>(arg5) + "|" + ConvertTo<std::string>(arg6) + "|" + ConvertTo<std::string>(arg7) + "|" + ConvertTo<std::string>(arg8);
		CallFunctionFinal(name, arg, &arg);
		return arg;
	}


private:
    lua_State* state;
	std::string error;
};

extern ScriptEngine Script;

}




#endif
