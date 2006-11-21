#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "../text/encoding.h"
using namespace std;

namespace System{
namespace File{

	std::string GetContents(std::string filename){
		ifstream is;
		std::string s;
		std::stringstream output;
		is.open (filename.c_str(), ios::in );
		if(is.is_open()){
			while(is >> s){
				output << s;
			}
		}
		return output.str();
	}

	bool WriteContents(std::string filename, std::string contents){
		ofstream myFile(filename.c_str(), ios::out);
		if (!myFile)
			return false;		
		myFile << contents;
		myFile.close();
	}


	bool Exists(std::string filename){
		bool exists;
		fstream fin; 
		fin.open(filename.c_str(),ios::in);
		exists = fin.is_open();
		fin.close();
		return exists;
	}







	bool EncryptToFile(std::string Filename, std::string input, std::string key){
		std::string crypted;
		if(System::Text::Encrypt(input, crypted, key)){
			return System::File::WriteContents(Filename, crypted);
		} else {
			return false;
		}
	}
	
	bool DecryptFromFile(std::string Filename, std::string &output, std::string key){
		std::string content = System::File::GetContents(Filename);
		std::string decrypted;
		if(System::Text::Decrypt(content, decrypted, key)){
			output = decrypted;
			return true;
		} else {
			return false;
		}
	}

}
}
