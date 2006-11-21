#include "textbox.h"

#include "../text/encoding.h"

namespace System{
namespace GUI{



	void TextBox::KeyDown(SDL_KeyboardEvent *key){
		if(Enabled() && Visible()){
			if(!m_Locked){
				switch(key->keysym.sym){
				case SDLK_BACKSPACE:
					if(m_text.length() > 0)
						m_text = m_text.substr(0, m_text.length()-1);
					return;
				case SDLK_RETURN:
					Enter();
					return;
				}
		
				if(m_MaxCharacters > -1)
					if(m_text.length() >= m_MaxCharacters)
						return;
	
				int ch = key->keysym.unicode;
				if (ch >= 32 && ch <= 126){
					m_text += ch;
				}
			}
		}
	}





void TextBox::BorderColour(int r, int g, int b, int a){
		borderR = r; borderG = g; borderB = b; borderA = a;
	}
void TextBox::BackColour(int r, int g, int b, int a){
	backR = r; backG = g; backB = b; backA = a;
}
void TextBox::TextColour(int r, int g, int b){
		m_textcolourR = r; m_textcolourG = g; m_textcolourB = b;
}



}
}
