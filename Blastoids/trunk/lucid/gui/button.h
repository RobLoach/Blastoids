#if !defined(_BUTTON_H_)
#define _BUTTON_H_

#include <string>
#include "baseguiobject.h"
#include <SDL/SDL.h>
#include "../text/text.h"
#include "../input/mouse.h"
#include "../graphics/primitives.h"

namespace System{
namespace GUI{


class ButtonSprite : public System::GUI::GUIObjectSprite {
	protected:
		std::string m_text;
		std::string m_font;
		Uint8 textR, textG, textB;
	public:
	ButtonSprite(): m_text(""), m_font("default"),
					textR(0), textG(0), textB(0)
	{ }

	std::string Text(std::string text){ return m_text = text; }
	std::string Text(){ return m_text; }

	std::string Font(std::string font){ return m_font = font; }
	std::string Font(){ return m_font; }

	void TextColour(int r, int g, int b);

	virtual void Click(){ }

	virtual void MouseButtonDown(int button){
		if(Visible() && Enabled()){
			if(button == SDL_BUTTON_LEFT)
				Click();
		}
	}
	virtual void KeyDown(int key){
		if(Visible() && Enabled()){
			if(key == SDLK_RETURN)
				Click();
		}
	}

	void Draw();

};

class Button : public System::GUI::GUIObject {
	protected:
		std::string m_text;
		std::string m_font;
		Uint8 borderR, borderG, borderB, borderA;
		Uint8 backR, backG, backB, backA;
		Uint8 hoverR, hoverG, hoverB, hoverA;
		Uint8 textR, textG, textB;
	public:

	Button() : 	m_text("Button"),
				m_font("default"),
				backR(150), backG(150), backB(150), backA(255),
				borderR(200), borderG(200), borderB(200), borderA(255),
				hoverR(200), hoverG(200), hoverB(200), hoverA(255)
	{
		Height(50);
		Width(150);
	}

	Button(std::string text, std::string font,
		int colBackR, int colBackG, int colBackB, int colBackA,
		int colBorderR, int colBorderG, int colBorderB, int colBorderA,
		int colHoverR, int colHoverG, int colHoverB, int colHoverA) : 
				m_text(text),
				m_font(font),
				backR(colBackR), backG(colBackG), backB(colBackB), backA(colBackA),
				borderR(colBorderR), borderG(colBorderG), borderB(colBorderB), borderA(colBorderA),
				hoverR(colHoverR), hoverG(colHoverG), hoverB(colHoverB), hoverA(colHoverA){

		}

	void BorderColour(int r, int g, int b, int a=255);
	void BackColour(int r, int g, int b, int a=255);
	void HoverColour(int r, int g, int b, int a=255);
	void TextColour(int r, int g, int b);

	void Draw(int hovering){
		if(Visible()){
			System::Graphics::DrawRectangle(this->x()+System::CameraX,this->y()+System::CameraY,x()+Width()+System::CameraX,y()+Height()+System::CameraY,borderR,borderG,borderB,borderA);
	
			bool hover = false;
			if(hovering == -1){
				if(MouseIsOver() && !System::Input::MouseButtonDown(SDL_BUTTON_LEFT)){
					hover = true;
				}
			} else if(hovering == 1){
				hover = true;
			}
			if(hover && Enabled())
				System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY,x()+Width()-1+System::CameraX,y()+Height()-1+System::CameraY,hoverR,hoverG,hoverB,hoverA);
			else
				System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY,x()+Width()-1+System::CameraX,y()+Height()-1+System::CameraY,backR,backG,backB,backA);
			
			System::Text::Print(x()+Width()/2+System::CameraX,y()+Height()/2+System::CameraY,m_text,textR,textG,textB,255,1,1,m_font);
		}
	}
	void Draw(){
		if(Visible()){
			System::Graphics::DrawRectangle(this->x()+System::CameraX,this->y()+System::CameraY,x()+Width()+System::CameraX,y()+Height()+System::CameraY,borderR,borderG,borderB,borderA);
	
			bool hover = false;
			if(MouseIsOver() && !System::Input::MouseButtonDown(SDL_BUTTON_LEFT)){
				hover = true;
			}
			if(hover && Enabled())
				System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY,x()+Width()-1+System::CameraX,y()+Height()-1+System::CameraY,hoverR,hoverG,hoverB,hoverA);
			else
				System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY,x()+Width()-1+System::CameraX,y()+Height()-1+System::CameraY,backR,backG,backB,backA);
			
			System::Text::Print(x()+Width()/2+System::CameraX,y()+Height()/2+System::CameraY,m_text,textR,textG,textB,255,1,1,m_font);
		}
	}

	std::string Text(std::string text){ return m_text = text; }
	std::string Text(){ return m_text; }

	std::string Font(std::string font){ return m_font = font; }
	std::string Font(){ return m_font; }

	virtual void Click(){ }

	virtual void MouseButtonDown(int button){
		if(Visible() && Enabled()){
			if(button == SDL_BUTTON_LEFT)
				Click();
		}
	}
	virtual void KeyDown(int key){
		if(Visible() && Enabled()){
			if(key == SDLK_RETURN)
				Click();
		}
	}
};


}
}

#endif

