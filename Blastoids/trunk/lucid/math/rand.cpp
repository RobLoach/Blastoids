#include "rand.h"


 
#include <ctime>
#include <cstdlib>

namespace System{
namespace Math{ 
      

int RandomNumber(int lowest, int highest){
	if(lowest > highest){
		int temp = highest;
		highest = lowest;
		lowest = temp;
    }
    return lowest + int((highest - lowest + 1) * (double)rand()/((double)RAND_MAX + 1.0));
}

int RandomNumber(int highest){
	return (rand() % (highest + 1));
}

int RandomNumber(){
	return rand();
}
          
void InitRandomNumber(){
	srand(static_cast<unsigned>(time(NULL)));
	int randnumber = RandomNumber(0,100);
	for(int x = 0; x < randnumber; x++) // Enter the sequence a random amount
		RandomNumber();
}


double RandomNumberDouble(double lowest, double highest){
	if(lowest > highest){
		double temp = highest;
		highest = lowest;
		lowest = temp;
    }
    return lowest + double((highest - lowest + 1) * (double)rand()/((double)RAND_MAX + 1.0));
}

}
}
