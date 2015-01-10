#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	/** 
	Constructor.  Also functions as default constructor 
	*/
	Vector3( float x=0, float y=0, float z=0 );

	/** 
	Constructor.
	*/
	Vector3( float d[3]);

   /** 
	Copy constructor.
	*/
	Vector3(const Vector3 &v);
   
   /** 
	Automatic conversion operator 
	*/
   operator const float* () const;

	/** 
	Automatic conversion operator 
	*/
   operator float* ();


   //!< Add operator
   Vector3 operator+( Vector3 other ) const;

	//!< Add operator
   Vector3 operator+=( Vector3 other );
  
	//!< subtraction operator
   Vector3 operator-( Vector3 other ) const;

	//!< subtraction operator
   Vector3 operator-=( Vector3 other );
   
	//!< multiplication operator
   Vector3 operator*( float d ) const;

	//!< multiplication operator
   Vector3 operator*=( float d );
   
	//!< division operator
   Vector3 operator/( float d ) const;

	//!< division operator
   Vector3 operator/=( float d );
   
   /** 
	\brief Cross product.
	Compute the cross product. \n
   a = b.cross(c); sets a = b cross c 
	*/
   Vector3 cross( const Vector3 v2 ) const;

   /** 
	\brief Dot product.
	Compute the dot product. \n
   a = b.dot(c); sets a = b dot c 
	*/
   float dot( const Vector3 v2 ) const;

   /** 
	\brief gets length.
	Used to normalize the vector.
	\return length of vector sqrt(a*a + b*b + c*c)
	*/
   float length() const;

	
	static float GetMagnitude(float X, float Y);
	static float GetRotation(float X, float Y);

	
private:
	float v[3];
};

#endif
