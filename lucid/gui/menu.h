#if !defined(_GUI_MENU_H_)
#define _GUI_MENU_H_

#include <string>
#include "baseguiobject.h"
#include "button.h"
#include <SDL/SDL.h>
#include <vector>
#include "../graphics/primitives.h"

namespace System{
namespace GUI{

class Item : public System::GUI::Button
{
	public:
	
};

class Menu : public System::GUI::GUIObject
{
	protected:
		std::vector<std::string> items;
		int selecteditem;
		int itemspacing;
	public:
		Item Items;
	Menu() : selecteditem(0), itemspacing(0) {
		Type(5);
		Height(0);
		Width(100);
	}
	int Width(int width){ m_Width = width; return Items.Width(width); }
	int Width(){ return Items.Width(); }
	int Height(int height);
	int Height(){ return m_Height; }
	int SelectedItem(std::string name);
	int SelectedItem(int num){ 
		return selecteditem = num;
	}

	int ItemSpacing(int spacing){ 
		Height(Items.Height());
		return itemspacing = spacing;
	}
	int ItemSpacing(){ return itemspacing; }
	
	bool ItemText(std::string oldtext, std::string newtext);
	bool ItemText(int item, std::string newtext);

	bool RemoveItem(int item);
	bool RemoveItem(std::string item);

	virtual void Select(std::string Item){ }
	virtual void Select(int Item){ }
	void AddItem(std::string item);
	void ItemEnabled(std::string item, bool enabled);
	void Draw();
	void MouseButtonDown(int button);
	void MouseMotion();
	
	void KeyDown(int key);

};

}
}

#endif

