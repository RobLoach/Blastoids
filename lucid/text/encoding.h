#if !defined(_ENCODING_H_INCLUDED_)
#define _ENCODING_H_INCLUDED_

#include <string>
#include <sstream>
#include <cstdlib>

namespace System {
namespace Text {

	template <class T>
	std::string ToString(T data){
		std::stringstream temp;
		temp << data;
		return temp.str();
	}

	int ToInteger(std::string);

	//std::string ToString(bool data);

	bool Encrypt(const std::string &intstr, std::string &outstr, std::string key = "lucid");
	bool Decrypt(const std::string &intstr, std::string &outstr, std::string key = "lucid");

}
}

#endif
