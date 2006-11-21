#if !defined(_FILE_H_)
#define _FILE_H_


#include <string>
#include "tinyxml/tinyxml.h"
#include "highscorelist.h"


namespace System{
namespace File{

	std::string GetContents(std::string filename);
	bool WriteContents(std::string filename, std::string contents);
	bool Exists(std::string filename);

	bool EncryptToFile(std::string Filename, std::string input, std::string key = "lucid");
	bool DecryptFromFile(std::string Filename, std::string &output, std::string key = "lucid");

}
}

#endif
