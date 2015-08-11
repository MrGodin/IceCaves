#pragma once


class TDirection
{
private:
	enum BiDir
	{
		bdLeft,
		bdRight,
		bdUp,
		bdDown,
		Invalid
	}dir;
public:
	TDirection()
	{
		dir = Invalid;
	}
	TDirection(const TDirection& d)
	{
		dir = d.dir;
	}
	void SetLeft()
	{
		dir = bdLeft;
	}
	void SetRight()
	{
		dir = bdRight;
	}
	void SetInvalid()
	{
		dir = Invalid;
	}

	void SetUp()
	{
		dir = bdUp;
	}
	void SetDown()
	{
		dir = bdDown;
	}

	static TDirection Right()
	{
		TDirection d;
		d.SetRight();
		return d;
	}
	static TDirection Left()
	{
		TDirection d;
		d.SetLeft();
		return d;
	}
	static TDirection Up()
	{
		TDirection d;
		d.SetUp();
		return d;
	}
	static TDirection Down()
	{
		TDirection d;
		d.SetDown();
		return d;
	}
	bool IsLeft(){ return dir == bdLeft; }
	bool IsRight(){ return dir == bdRight; }
	bool IsUp(){ return dir == bdUp; }
	bool IsDown(){ return dir == bdDown; }
	bool IsValid(){ return dir != Invalid; }
	TDirection GetOpposite() const
	{
		TDirection o;

		if (dir == bdLeft)
		{
			o.SetLeft();
		}
		else if (dir == bdRight)
		{
			o.SetRight();
		}
		return o;
	}
	void Reverse()
	{


		if (dir == bdLeft)
		{
			SetRight();
		}
		else if (dir == bdRight)
		{
			SetLeft();
		}

	}
	float Translate(float inc)
	{
		float result = 0.0f;
		if (dir == bdLeft || dir == bdUp)
			result = -inc;
		else if (dir == bdRight || dir == bdDown)
			result = inc;

		return result;
	}
	bool operator == (const TDirection& rhs)
	{
		return dir == rhs.dir;
	}
	bool operator != (const TDirection& rhs)
	{
		return dir != rhs.dir;
	}
	TDirection& operator = (const TDirection& rhs)
	{
		dir = rhs.dir;
		return *this;
	}
};