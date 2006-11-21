#include "button.h"





namespace System{
namespace GUI{




void ButtonSprite::Draw(){
	if(Visible()){
		Graphic.Draw();
		System::Text::Print(x()+Width()/2+System::CameraX,y()+Height()/2+System::CameraY,m_text,textR,textG,textB,255,1,1,m_font);
	}
}
void ButtonSprite::TextColour(int r, int g, int b){
	textR = r; textG = g; textB = b;
}


void Button::BorderColour(int r, int g, int b, int a){
	borderR = r;  borderG = g; borderB = b; borderA = a;
}
void Button::BackColour(int r, int g, int b, int a){
	backR = r; backG = g; backB = b; backA = a;
}
void Button::HoverColour(int r, int g, int b, int a){
	hoverR = r; hoverG = g; hoverB = b; hoverA = a;
}
void Button::TextColour(int r, int g, int b){
	textR = r; textG = g; textB = b;
}






}
}









