#pragma once

template<typename T>
class Vec2
{
public:
	Vec2();
	Vec2(const T& _x, const T& _y);
	Vec2(const Vec2& _vec);

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
	void normalize();

	T x, y;
};



typedef Vec2<float> Vec2f;

template<typename T>
inline Vec2<T>::Vec2() : x(0), y(0)
{
}

template<typename T>
inline Vec2<T>::Vec2(const T& _x, const T& _y) : x(_x), y(_y)
{
}

template<typename T>
inline Vec2<T>::Vec2(const Vec2& _vec) : x(_vec.x), y(_vec.y)
{
}

template<typename T>
inline Vec2<T> Vec2<T>::operator+(const Vec2& _vec)
{
	return Vec2(x + _vec.x, y + _vec.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator+=(const Vec2& _vec)
{
	x += _vec.x;
	y += _vec.y;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-(const Vec2& _vec)
{
	return Vec2(x - _vec.x, y - _vec.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-=(const Vec2& _vec)
{
	x -= _vec.x;
	y -= _vec.y;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*(const Vec2& _vec)
{
	return Vec2(x * _vec.x, y * _vec.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*=(const Vec2& _vec)
{
	x *= _vec.x;
	y *= _vec.y;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator/(const Vec2& _vec)
{
	return Vec2(x / _vec.x, y / _vec.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator/=(const Vec2& _vec)
{
	x /= _vec.x;
	y /= _vec.y;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator+(const T& _val)
{
	return Vec2(x + _val,y + _val);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator+=(const T& _val)
{
	x += _val;
	y += _val;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-(const T& _val)
{
	return Vec2(x - _val, y - _val);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-=(const T& _val)
{
	x -= _val;
	y -= _val;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*(const T& _val)
{
	return Vec2(x * _val, y * _val);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*=(const T& _val)
{
	x *= _val;
	y *= _val;
	return *this;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator/(const T& _val)
{
	return Vec2(x / _val, y / _val);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator/=(const T& _val)
{
	x /= _val;
	y /= _val;
	return *this;
}

template<typename T>
inline float Vec2<T>::length() const
{
	return sqrt(x*x+y*y);
}

template<typename T>
inline void Vec2<T>::normalize()
{
	auto m = this->length();
	*this /= m;
}
