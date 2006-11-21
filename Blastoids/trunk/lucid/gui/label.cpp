#include "label.h"

#include "../text/encoding.h"

namespace System{
namespace GUI{

	void Label::Draw(){
		if(Visible()){
			switch(m_hAlignment){
			case 0:
				switch(m_vAlignment){
				case 0: System::Text::Print(x()+System::CameraX,y()+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,0,0,m_font); break;
				case 1: System::Text::Print(x()+System::CameraX,y()+Height()/2+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,0,1,m_font); break;
				case 2: System::Text::Print(x()+System::CameraX,y()+Height()+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,0,2,m_font); break;
				}
			break;
	
	
			case 1:
				switch(m_vAlignment){
				case 0: System::Text::Print(x()+Width()/2+System::CameraX,y()+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,1,0,m_font); break;
				case 1: System::Text::Print(x()+Width()/2+System::CameraX,y()+Height()/2+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,1,1,m_font); break;
				case 2: System::Text::Print(x()+Width()/2+System::CameraX,y()+Height()+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,1,2,m_font); break;
				}
			break;
			case 2:
				switch(m_vAlignment){
				case 0: System::Text::Print(x()+Width()+System::CameraX,y()+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,2,0,m_font); break;
				case 1: System::Text::Print(x()+Width()+System::CameraX,y()+Height()/2+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,2,1,m_font); break;
				case 2: System::Text::Print(x()+Width()+System::CameraX,y()+Height()+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,2,2,m_font); break;
				}
			break;
			}
		}
	}

	int Label::HorizontalAlignment(int halign){ return m_hAlignment = halign; }
	int Label::HorizontalAlignment(){ return m_hAlignment; }

	int Label::VerticalAlignment(int valign){ return m_vAlignment = valign; }
	int Label::VerticalAlignment(){ return m_vAlignment; }

}
}

