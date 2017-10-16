#pragma once
class MyVector
{
public:
	float x;
	float y;
	float z;
public:
	MyVector() { x = y = z = 0; }
	MyVector(float x, float y, float z) : x(x), y(y), z(z) {}
	~MyVector() {}

	void SetVector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	MyVector& operator+(const MyVector& m)
	{
		x += m.x;
		y += m.y;
		z += m.z;
		return *this;
	}
	MyVector& operator-(const MyVector& m)
	{
		x -= m.x;
		y -= m.y;
		z -= m.z;
		return *this;
	}
};