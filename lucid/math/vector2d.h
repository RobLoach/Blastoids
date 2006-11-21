#if !defined(_VECTOR2D_H_INCLUDED_)
#define _VECTOR2D_H_INCLUDED_


namespace System{
namespace Math{
	

//class Vector2D;


/// 2d vector class
class Vector2D {
protected:
	double m_x, m_y, m_length, m_direction; // USES RADIANS
public:
	Vector2D(const Vector2D& other) :
			m_x(other.m_x),
			m_y(other.m_y),
			m_length(other.m_length),
			m_direction(other.m_direction){ /* nothing */ }			
	Vector2D(double x = 0, double y = 0){ SetPoints(x,y); }
	double x(double x);
	double y(double y);
	double Direction(double d);	
	double Length(double m);
	void SetPoints(double x, double y);
	void Reset();

	void ReflectAngle(int NormalAngle);
	double x(){ return m_x; }
	double y(){ return m_y; }
	double Direction(){ return m_direction; }
	double Length(){ return m_length; }

	// Vector arithmetic operators
	Vector2D& operator+= (Vector2D& v);
	Vector2D& operator-= (Vector2D& v);
	Vector2D& operator*= (Vector2D& v);	
	Vector2D& operator/= (Vector2D& v);
	
	// scalar operators for speed and resolving ambiguity problems
	// with implicit constructor calls
	Vector2D& operator+= (double f);
	Vector2D& operator-= (double f);
	Vector2D& operator*= (double f);
	Vector2D& operator/= (double f);
};

} 
}
#endif

