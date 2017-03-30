#include "Particle.h"
#include <random>

//constructor setting random values
Particle::Particle(int* _deltaTime)
{
	m_col.r = 100 + rand() % 154;
	m_col.g = 100 + rand() % 154;
	m_col.b = 100 + rand() % 154;
	m_position.x = 5 + rand() % 1270;
	m_position.y = 5 + rand() % 710;
	m_velocity.x = ((rand() % 3)-1)*25;
	m_velocity.y = ((rand() % 3)-1)*25;
	m_deltaTime = _deltaTime;
}

//run every frame to move the particle
void Particle::Update()
{
	m_position.x += (m_velocity.x * *m_deltaTime/1000);
	m_position.y += (m_velocity.y * *m_deltaTime/1000);
}

//set both components of the velocity
void Particle::SetVelocity(float _x, float _y)
{
	m_velocity.x = _x;
	m_velocity.y = _y;
}

//set one of the components of the velocity
void Particle::SetVelocity(int _componentFlag, float _value)
{
	if (_componentFlag == X)
	{
		m_velocity.x = _value;
	}
	else
	{
		m_velocity.y = _value;
	}
}