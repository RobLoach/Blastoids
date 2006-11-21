#if !defined(_PROGRESSBAR_H_)
#define _PROGRESSBAR_H_

#include <string>
#include "baseguiobject.h"
#include <SDL/SDL.h>
#include "../graphics/primitives.h"

namespace System{
namespace GUI{

class ProgressBar : public System::GUI::GUIObject
{

	protected:
		Uint8 backR, backG, backB, backA;
		Uint8 borderR, borderG, borderB, borderA;
		Uint8 barR, barG, barB, barA;
		int m_Value;
		int m_MaxValue;
	public:
	ProgressBar() : m_MaxValue(100),
				m_Value(0),
				backR(190), backG(190), backB(190), backA(255),
				borderR(150), borderG(150), borderB(150), borderA(255),
				barR(180), barG(0), barB(0), barA(255)
	{
		Type(3);
		Height(30);
	}

	double Percent();

	void Draw();

	int MaxValue(int maxvalue){
		if(maxvalue <= 0) maxvalue = 1;
		return m_MaxValue = maxvalue;
	}
	int MaxValue(){ return m_MaxValue; }
	int Value(){ return m_Value; }
	int Value(int value){
		if(value>m_MaxValue) 	value = m_MaxValue;
		else if(value<0) 		value = 0;
		return m_Value = value;
	}


	void BorderColour(int r, int g, int b, int a=255);
	void BackColour(int r, int g, int b, int a=255);
	void BarColour(int r, int g, int b, int a=255);
};

}
}

#endif

