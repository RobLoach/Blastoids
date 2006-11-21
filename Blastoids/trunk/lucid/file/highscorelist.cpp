#include "highscorelist.h"

#include "tinyxml/tinyxml.h"
#include "file.h"
#include "../text/encoding.h"

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace System{
namespace File{



	bool HighScoreItem_comp(HighScoreItem* i1, HighScoreItem* i2){
		return (i1->Score > i2->Score);
	}

	bool HighScoreItem_comp2(HighScoreItem* i1, HighScoreItem* i2){
		return (i1->Score < i2->Score);
	}

	void HighScoreList::Sort(){
		if(m_descending)
			std::sort(list.begin(), list.end(), HighScoreItem_comp);
		else
			std::sort(list.begin(), list.end(), HighScoreItem_comp2);
	}

	bool HighScoreList::Load(std::string Filename){
		std::string filecontents;
		if(System::File::DecryptFromFile(Filename,filecontents,m_key)){
			if(filecontents == "") return true;

			TiXmlDocument doc;
			try{
				doc.Parse(filecontents.c_str());
				if(doc.Error())
					return System::File::WriteContents(Filename,"");
			} catch(std::exception a){
				return System::File::WriteContents(Filename,"");
			}

			TiXmlHandle docHandle( &doc );
			TiXmlElement* child = docHandle.FirstChild("record").Element();
			for( child; child; child=child->NextSiblingElement() )
				AddRecord(child->Attribute("name"), System::Text::ToInteger(child->Attribute("score")));
			
			return true;
		}
		return System::File::WriteContents(Filename,"");

	}

	bool HighScoreList::Save(std::string Filename, int NumberOfRecords){
		if(NumberOfRecords == 0) return true;
		std::stringstream output;

		if(NumberOfRecords < 0){
			for(std::vector<HighScoreItem*>::iterator pos = list.begin(); pos != list.end(); pos++){
				output << "<record name=\"" << (*pos)->Name << "\" score=\"" << (*pos)->Score << "\"/>";
			}
		} else {
			for(std::vector<HighScoreItem*>::iterator pos = list.begin(); pos != list.end(); pos++){
				if(NumberOfRecords-- > 0)
					output << "<record name=\"" << (*pos)->Name << "\" score=\"" << (*pos)->Score << "\"/>";
				else
					break;
			}
		}
		std::string s = output.str();
		return System::File::EncryptToFile(Filename, s, m_key);
	}

	std::string HighScoreList::Name(int Position){
		try{	
			HighScoreItem* item = list.at(Position);
			return item->Name;
		}catch(std::exception a){
			return "Nobody";
		}
	}
	int HighScoreList::Score(int Position){
		try{	
			HighScoreItem* item = list.at(Position);
			return item->Score;
		}catch(std::exception a){
			return 0;
		}
	}

	int HighScoreList::AddRecord(std::string Name, int Score){
		list.push_back(new HighScoreItem(Name, Score));
		Sort();
	}

	void HighScoreList::ClearList(){
		while(!list.empty()){
			delete list.back();
			list.pop_back();
		}
		list.clear();
	}

}
}

