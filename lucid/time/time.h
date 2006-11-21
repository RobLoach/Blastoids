#ifndef _TIME_H_INCLUDED_
#define _TIME_H_INCLUDED_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

namespace System {
namespace Time {

//Usage:
/*
System::Time::Timer FooTimer = 100; // Set up timer
if(FooTimer.Check()){ // Check if interval has been met
	// Do something
	FooTimer.StartTimer(); // Reset the timer
}
*/

	
//TODO - Function Pointer callback



	class Timer{
	public:
		Timer(){ /* nothing */}
		Timer(int delay){ SetDelay(delay); }
		bool Check();
		void SetDelay(int delay);
		void StartTimer();
	private:
		Uint32 m_NextIntervalTime;
		Uint32 m_Delay;
	};
	
}
} // end namespace

#endif // _TIME_H_INCLUDED_


