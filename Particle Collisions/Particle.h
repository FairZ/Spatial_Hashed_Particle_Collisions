#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include <math.h>

#define X 0
#define Y 1

//Vec 2 struct used for positions and velocities
struct Vec2
{
	float x;
	float y;

	//operator overloading
	Vec2 operator-(const Vec2 a) const
	{
		Vec2 retVal;
		retVal.x = x-a.x;
		retVal.y = y-a.y;
		return retVal;
	}

	Vec2 operator/(const float a) const
	{
		Vec2 retVal;
		retVal.x = x/a;
		retVal.y = y/a;
		return retVal;
	}

	Vec2 operator*(const float a) const
	{
		Vec2 retVal;
		retVal.x = x*a;
		retVal.y = y*a;
		return retVal;
	}

	//returns the square magnitude of the vector
	float sqrLength()
	{
		return(pow(x,2)+pow(y,2));
	}
};

struct Colour
{
	int r;
	int g;
	int b;
};

//particle class has a colour, position, velocity and acceleration (not used but there for future expansion) and a reference to the deltaTime
//has functions to update the particle and get and set velocities
class Particle
{
private:
	Colour m_col;
	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;
	int *m_deltaTime;
public:
	Particle(int* _deltaTime);
	void Update();
	Vec2 GetPosition(){return m_position;};
	void SetVelocity(Vec2 _vel){m_velocity = _vel;};
	void SetVelocity(float _x, float _y);
	void SetVelocity(int _componentFlag, float _value);
	Vec2 GetVelocity(){return m_velocity;};
	Colour GetColour(){return m_col;};
};


#endif