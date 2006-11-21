#if !defined(_INCLUDED_VARIABLE_H_)
#define _INCLUDED_VARIABLE_H_

#include <lua.h>
#include <string>


#include <sstream>

namespace System{



template<typename TargetType, typename SourceType>
inline TargetType ConvertTo(SourceType from) {
	std::stringstream s;
	TargetType to;
	s << from;
	s >> to;
	return to;
}


class ScriptVariable{
public:
	ScriptVariable(lua_State* L, std::string variablename) : state(L), name(variablename)
	{	}

	operator long() const;
	operator int() const;
	operator float() const;
	operator char*() const;
	operator std::string() const;
	operator double() const;
	operator bool() const;

	int 		ToInteger(){ 	return operator int(); 			}
	float 		ToFloat(){ 		return operator float(); 		}
	double 		ToDouble(){ 	return operator double(); 		}
	long 		ToLong(){ 		return operator long(); 		}
	bool 		ToBool(){ 		return operator bool(); 		}
	bool 		ToBoolean(){ 	return operator bool(); 		}
	std::string ToString(){ 	return operator std::string(); 	}
	char* 		ToCString(){ 	return operator char*();		}

	ScriptVariable& operator =(int value);
	ScriptVariable& operator =(long value);
	ScriptVariable& operator =(float value);
	ScriptVariable& operator =(double value);
	ScriptVariable& operator =(bool value);
	ScriptVariable& operator =(std::string value);
	ScriptVariable& operator =(char* value);

	int Type();
	std::string Typename();

private:
	lua_State* state;
	std::string name;
};


}

#endif
