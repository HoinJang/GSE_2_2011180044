#pragma once
class MyVector
{
public:
	float x;
	float y;
public:
	MyVector() { x = y = 0; }
	MyVector(float x, float y) : x(x), y(y) {}
	~MyVector() {}

	void SetVector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	MyVector& operator+(const MyVector& m)
	{
		x += m.x;
		y += m.y;
		return *this;
	}
	MyVector& operator-(const MyVector& m)
	{
		x -= m.x;
		y -= m.y;
		return *this;
	}
	void Nomalize()
	{
		this->x = x / Size();
		this->y = y / Size();
	}
	float Size()
	{
		return sqrt(x*x + y*y);
	}
};