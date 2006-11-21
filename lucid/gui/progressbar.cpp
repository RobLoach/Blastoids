#include "progressbar.h"





namespace System{
namespace GUI{


void ProgressBar::Draw(){
	if(Visible()){
		System::Graphics::DrawRectangle(this->x()+System::CameraX,this->y()+System::CameraY,x()+Width()+System::CameraX,y()+Height()+System::CameraY,borderR,borderG,borderB,borderA);
		System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY,x()+Width()-1+System::CameraX,y()+Height()-1+System::CameraY,backR,backG,backB,backA);
		if(m_Value > 0)
			System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY, x()+int(Width()*Percent())-1+System::CameraX, y()+Height()-1+System::CameraY,barR,barG,barB,barA);
		else
			System::Graphics::DrawLine(x()+1+System::CameraY,y()+1+System::CameraY, x()+1+System::CameraX, y()+Height()-1+System::CameraY,barR,barG,barB,barA);
	}
}

double ProgressBar::Percent(){
	return (double)(m_Value) / (double)(m_MaxValue);
}

void ProgressBar::BorderColour(int r, int g, int b, int a){
	borderR = r;  borderG = g; borderB = b; borderA = a;
}
void ProgressBar::BackColour(int r, int g, int b, int a){
	backR = r; backG = g; backB = b; backA = a;
}
void ProgressBar::BarColour(int r, int g, int b, int a){
	barR = r; barG = g; barB = b; barA = a;
}



}
}









