#include "vector2d.h"

#include <cmath>
#include "math.h"
 
namespace System{
namespace Math{

	void Vector2D::Reset(){
		m_x = 0;
		y(0);
	}
	
	double Vector2D::x(double x)
	{
		m_x = x;
		m_direction = atan2(m_y, m_x);
		m_length = sqrt((m_x * m_x) + (m_y * m_y));
	}
	double Vector2D::y(double y)
	{
		m_y = y;
		m_direction = atan2(m_y, m_x);
		m_length = sqrt((m_x * m_x) + (m_y * m_y));
	}
	double Vector2D::Direction(double a){
		m_direction = a;
		m_x = cos(m_direction) * m_length;
		m_y = sin(m_direction) * m_length;
	}
	double Vector2D::Length(double m){
		m_length = m;
		m_x = cos(m_direction) * m_length;
		m_y = sin(m_direction) * m_length;
	}
	void Vector2D::SetPoints(double x, double y){
		m_x = x;
		m_y = y;
		m_length = sqrt((m_x * m_x) + (m_y * m_y));
		m_direction = atan2(m_y,m_x);
	}
	
	 
	void Vector2D::ReflectAngle(int NormalAngle)
	{
	   int NormDiffAngle; //difference between the inverted angle & the BoundaryNormal angle
	   int angle = (int)RAD2DEG(m_direction);	// new angle
	   int OppAngle = (angle + 180) % 360; // Inverted angle
	   if( NormalAngle >= OppAngle ){
	      NormDiffAngle = NormalAngle - OppAngle;
	      angle = (NormalAngle + NormDiffAngle) % 360;
	   } else {
	      NormDiffAngle = OppAngle - NormalAngle;
	      angle = NormalAngle - NormDiffAngle;
	      if( angle < 0 ) angle += 360;
	   }
	
	   this->Direction(DEG2RAD(angle));
	}


	// scalar operators for speed and resolving ambiguity problems
	// with implicit constructor calls
	
	/// Componentwise addition 
	Vector2D& Vector2D::operator+= (double f) {
		SetPoints(m_x + f, m_y + f);
		return *this;
	}
	
	/// Componentwise subtraction
	Vector2D& Vector2D::operator-= (double f) {
		SetPoints(m_x - f, m_y - f);
		return *this;
	}
	
	/// Componentwise multiplication
	Vector2D& Vector2D::operator*= (double f) {
		SetPoints(m_x * f, m_y * f);
		return *this;
	}
	
	/// Componentwise division
	Vector2D& Vector2D::operator/= (double f) {
		SetPoints(m_x / f, m_y / f);
		return *this;
	}


	// Vector arithmetic operators
	
	Vector2D& Vector2D::operator+= (Vector2D& v) {
		SetPoints(m_x + v.x(), m_y + v.y());
		return *this;
	}
	
	Vector2D& Vector2D::operator-= (Vector2D& v) {
		SetPoints(m_x - v.x(), m_y - v.y());
		return *this;
	}
	
	Vector2D& Vector2D::operator*= (Vector2D& v) {
		SetPoints(m_x * v.x(), m_y * v.y());
		return *this;
	}
	
	Vector2D& Vector2D::operator/= (Vector2D& v) {
		SetPoints(m_x / v.x(), m_y / v.y());
		return *this;
	}


}
}


