#include "time.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


namespace System {
namespace Time {
	
	bool Timer::Check(){
		Uint32 now = SDL_GetTicks();
		
		// Check if interval has not been met
		if(now < m_NextIntervalTime)
			return false;
		
		// Interval has been met
		//StartTimer();
		return true;
	}

	void Timer::StartTimer(){
		m_NextIntervalTime = SDL_GetTicks() + m_Delay;
	}

	void Timer::SetDelay(int delay){
		m_Delay = delay;
		m_NextIntervalTime = SDL_GetTicks() + m_Delay;
	}
	
}
}

