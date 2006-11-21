#include "menu.h"

#include <vector>

namespace System{
namespace GUI{



	void Menu::AddItem(std::string item){
		items.push_back(item);
		Height(Items.Height());
	}

	void Menu::Draw(){
		int num = 0;
		for (std::vector<std::string>::iterator pos = items.begin(); pos != items.end(); pos++){
			Items.x(x());
			Items.y(y() + num * Items.Height() + num * itemspacing);
			Items.Text((*pos));
			if(selecteditem == num)
				Items.Draw(1);
			else
				Items.Draw(0);
			num++;
    	}
	}

	int Menu::SelectedItem(std::string name){
		int num = 0;
		for (std::vector<std::string>::iterator pos = items.begin(); pos != items.end(); pos++){
			if(name == (*pos)){
				return selecteditem = num;
			}
			num++;
    	}
	}

	void Menu::MouseMotion(){
		int num = 0;
		for (std::vector<std::string>::iterator pos = items.begin(); pos != items.end(); pos++){
			Items.x(x());
			Items.y(y() + num * Items.Height() + num * itemspacing);
			if(Items.MouseIsOver()){
				selecteditem = num;
				return;
			}
			num++;
    	}
	}

	void Menu::MouseButtonDown(int button){
		int num = 0;
		for (std::vector<std::string>::iterator pos = items.begin(); pos != items.end(); pos++){
			Items.x(x());
			Items.y(y() + num * Items.Height() + num * itemspacing);
			if(Items.MouseIsOver()){
				Select((*pos));
				Select(num);
				return;
			}
			num++;
    	}
	}

	void Menu::KeyDown(int key){
		switch(key){
		case SDLK_DOWN:
			if(++selecteditem >= items.size())
				selecteditem = 0;
		break;
		case SDLK_UP:
			if(--selecteditem < 0)
				selecteditem = items.size() - 1;
		break;
		case SDLK_RETURN:
			Select(items[selecteditem]);
			Select(selecteditem);
		break;
		}
		
	}

	bool Menu::ItemText(std::string oldtext, std::string newtext){
		vector<std::string>::iterator pos = std::find(items.begin(), items.end(), oldtext);
		if(pos != items.end()){
			*pos = newtext;
			return true;
		}
		return false;
	}

	bool Menu::ItemText(int item, std::string newtext){
		if(item >= 0){
			if(item < items.size()){
				items[item] = newtext;
				return true;
			}
		}
		return false;
	}

	bool Menu::RemoveItem(int item){
		if(item >= 0){
			if(item < items.size()){
				items.erase(items.begin() + item, items.begin() + item + 1);
				return true;
			}
		}
		return false;
	}

	bool Menu::RemoveItem(std::string item){
		vector<std::string>::iterator pos = std::find(items.begin(), items.end(), item);
		if(pos != items.end()){
			items.erase(pos,pos+1);
			return true;
		}
		return false;
	}

	int Menu::Height(int height){
		Items.Height(height);
		m_Height = height * items.size() + itemspacing * items.size();
		return Items.Height();
	}


}
}









