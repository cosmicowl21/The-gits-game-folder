#ifndef MATH_CORE_H
#define MATH_CORE_H

class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);

private:
	float m_x;
	float m_y;
};

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);

private:
	float m_x;
	float m_y;
	float m_z;
};
#endif