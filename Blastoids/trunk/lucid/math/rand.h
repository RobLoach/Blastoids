#if !defined(_RAND_H_INCLUDED_)
#define _RAND_H_INCLUDED_


namespace System{
namespace Math{

    

int RandomNumber(int lowest, int highest);
int RandomNumber(int highest);
int RandomNumber();
void InitRandomNumber();

double RandomNumberDouble(double lowest, double highest);



}
}

#endif // _RAND_H_INCLUDED_

