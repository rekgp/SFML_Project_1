#pragma once

template<typename T>
class Vec2
{
public:
	Vec2();
	Vec2(const T &_x, const T &_y);
	Vec2(const Vec2 &_vec);
	
	Vec2 operator + (const Vec2& _vec);
	Vec2 operator += (const Vec2& _vec);
	Vec2 operator - (const Vec2& _vec);
	Vec2 operator -= (const Vec2& _vec);
	Vec2 operator * (const Vec2& _vec);
	Vec2 operator *= (const Vec2& _vec);
	Vec2 operator / (const Vec2& _vec);
	Vec2 operator /= (const Vec2& _vec);

	Vec2 operator + (const T& _val);
	Vec2 operator += (const T& _val);
	Vec2 operator - (const T& _val);
	Vec2 operator -= (const T& _val);
	Vec2 operator * (const T& _val);
	Vec2 operator *= (const T& _val);
	Vec2 operator / (const T& _val);
	Vec2 operator /= (const T& _val);

	Vec2 cross(const Vec2& _vec) const;
	float dot(const Vec2& _vec) const;
	float length() const; 

	T x, y;
};

