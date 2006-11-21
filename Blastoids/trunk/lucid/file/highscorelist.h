#if !defined(_HIGHSCORELIST_H_)
#define _HIGHSCORELIST_H_

#include <string>
#include <vector>

namespace System{
namespace File{

// TODO Descending order

class HighScoreItem{
	public:
	std::string Name;
	int Score;
	HighScoreItem(std::string name, int score) : Name(name), Score(score) { }
};

class HighScoreList{
public:
	bool Load(std::string Filename);
	bool Save(std::string Filename, int NumberOfRecords = -1);
	int AddRecord(std::string Name, int Score);
	void ClearList();
	std::string Name(int Position);
	int Score(int position);
	~HighScoreList(){
		ClearList();
	}
	HighScoreList() : m_descending(true), m_key("lucid") {
		
	}
	void Sort();

	int NumberOfRecords(){ return list.size(); }
	bool DescendingOrder(bool desc){ m_descending = desc; Sort(); return m_descending; }
	bool DescendingOrder(){ return m_descending; }
	
	std::string Key(){ return m_key; }
	std::string Key(std::string key){ return m_key = key; }
	
private:
	std::vector<HighScoreItem*> list;
	bool m_descending;
	std::string m_key;
};

}
}

#endif
