#include "_Team167Lib.h"

#ifndef PI_2
#define PI_2 3.14159265
#endif

Vector3::Vector3( float x, float y, float z )
{
   v[0] = x;
   v[1] = y;
   v[2] = z;
}

Vector3::Vector3( float d[3] )
{
   v[0] = d[0];
   v[1] = d[1];
   v[2] = d[2];
}

Vector3::Vector3(const Vector3 &orig )
{
   v[0] = orig[0];
   v[1] = orig[1];
   v[2] = orig[2];
}

Vector3 Vector3::operator+( Vector3 other ) const
{
   return Vector3( v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2] );
}

Vector3 Vector3::operator+=( Vector3 other )
{
   v[0] += other.v[0];
   v[1] += other.v[1];
   v[2] += other.v[2];
   return *this;
}


Vector3 Vector3::operator-( Vector3 other ) const
{
   return Vector3( v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2] );
}

Vector3 Vector3::operator-=( Vector3 other )
{
   v[0] -= other.v[0];
   v[1] -= other.v[1];
   v[2] -= other.v[2];
   return *this;
}

Vector3 Vector3::operator*( float d ) const
{
   return Vector3( v[0] * d, v[1] * d, v[2] * d );
}

Vector3 Vector3::operator*=( float d )
{
   v[0] *= d;
   v[1] *= d;
   v[2] *= d;
   return *this;
}

Vector3 Vector3::operator/( float d) const
{
   return Vector3( v[0]/d, v[1]/d, v[2]/d );
}

Vector3 Vector3::operator/=( float d )
{
   v[0] /= d;
   v[1] /= d;
   v[2] /= d;
   return *this;
}


//performs cross product of 2 vectors and returns the result
Vector3 Vector3::cross( const Vector3 v2 ) const
{
   //Cx = AyBz - AzBy
   //Cy = AzBx - AxBz
   //Cz = AxBy - AyBx 
   
   return Vector3(
      v[1]*v2[2] - v[2]*v2[1],
      v[2]*v2[0] - v[0]*v2[2],
      v[0]*v2[1] - v[1]*v2[0]);
}


//performs dot product of 2 vectors and returns the result     
float Vector3::dot( const Vector3 v2 ) const
{
   //DotProduct = (x1*x2 + y1*y2 + z1*z2)
   return ( v[0]*v2[0] + v[1]*v2[1] + v[2]*v2[2] );
}





//computes the length of a vector
float Vector3::length() const
{
   return sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] ); 
}

Vector3::operator const float* () const 
{
   return v;
}


Vector3::operator float* ()
{
   return v;
}


float Vector3::GetMagnitude(float X, float Y)
{
	return sqrt((X*X)+(Y*Y));
}

float Vector3::GetRotation(float X, float Y)
{
	float ret = 0.0f;
	
	if(Y == 0.0f && X == 0.0f)
		return -1.0f;
	
	ret = atan2(Y,X);
	
	ret *= 180/PI_2;
	
	while(ret < 0)
		ret += 360.0f;
	
	return ret;
}


