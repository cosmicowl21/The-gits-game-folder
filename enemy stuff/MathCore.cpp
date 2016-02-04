#include "MathCore.h"

Vector2::Vector2()
{
	m_x = m_y = 0.0f;
}
Vector2::Vector2(float _x, float _y)
{
	m_x = _x;
	m_y = _y;
}

///////////////////////////////////////////////////////
//////////////vector 3/////////////////////////////////
///////////////////////////////////////////////////////
Vector3::Vector3()
{
	m_x = m_y = m_z= 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	m_x = _x;
	m_y = _y;
	m_z = _z;
}