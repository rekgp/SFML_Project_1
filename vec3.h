#pragma once
#include <iostream>

//Klasa vektora 3d z dodatkową funkcjonalnością cross product oraz dot product - wymagane do generowania Szumu Perlina
template<typename T>
class Vec3
{
public:
	Vec3();
	Vec3(const T &_x,const T &_y,const T &_z);
	Vec3(const Vec3 &_vec);

	Vec3 operator + (const Vec3 &_vec);
	Vec3 &operator += (const Vec3 &_vec);
	Vec3 operator - (const Vec3 &_vec);
	Vec3 &operator -= (const Vec3 &_vec);
	Vec3 operator * (const Vec3 &_vec);
	Vec3 &operator *= (const Vec3 &_vec);
	Vec3 operator / (const Vec3 &_vec);
	Vec3 &operator /= (const Vec3 &_vec);

	Vec3 operator + (const T &_val);
	Vec3 &operator += (const T &_val);
	Vec3 operator - (const T &_val);
	Vec3 &operator -= (const T &_val);
	Vec3 operator * (const T &_val);
	Vec3 &operator *= (const T &_val);
	Vec3 operator / (const T &_val);
	Vec3 &operator /= (const T &_val);
	
	Vec3 cross(const Vec3 &_vec);
	float dot(const Vec3 &_vec);
	float length() const;
	
	friend std::ostream &operator << (std::ostream &_out, const Vec3<T> &_vec) {
		_out << _vec.x << " " << _vec.y << " " << _vec.z << "; length :" << _vec.length() << std::endl;
		return _out;
	};
	T x, y, z;
};

template<typename T>
inline Vec3<T>::Vec3() : x((T)0),z((T)0),y((T)0)
{
}

template<typename T>
inline Vec3<T>::Vec3(const T &_x,const T &_y,const T &_z) : x(_x),y(_y),z(_z)
{
}

template<typename T>
inline Vec3<T>::Vec3(const Vec3 &_vec) : x(_vec.x), y(_vec.y), z(_vec.z)
{
}

template<typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3 &_vec)
{	
	return Vec3(x + _vec.x, y + _vec.y, z + _vec.z);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator+=(const Vec3 &_vec)
{	
	x += _vec.x;
	y += _vec.y;
	z += _vec.z;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3 &_vec)
{
	return Vec3(x - _vec.x, y - _vec.y, z - _vec.z);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator-=(const Vec3 &_vec)
{	
	x -= _vec.x;
	y -= _vec.y;
	z -= _vec.z;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator*(const Vec3 &_vec)
{
	return Vec3(x * _vec.x, y * _vec.y,z* _vec.z);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator*=(const Vec3 &_vec)
{
	x *= _vec.x;
	y *= _vec.y;
	z *= _vec.z;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator/(const Vec3 &_vec)
{
	return Vec3(x / _vec.x, y / _vec.y, z / _vec.z);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator/=(const Vec3 &_vec)
{
	x /= _vec.x;
	y /= _vec.y;
	z /= _vec.z;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator+(const T &_val)
{
	return Vec3(x + _val, y + _val , z + _val);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator+=(const T &_val)
{	
	x += _val;
	y += _val;
	z += _val;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator-(const T &_val)
{
	return Vec3(x - _val, y - _val, z - _val);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator-=(const T &_val)
{
	x -= _val;
	y -= _val;
	z -= _val;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator*(const T &_val)
{
	return Vec3(x * _val, y * _val, z * _val);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator*=(const T &_val)
{
	x *= _val;
	y *= _val;
	z *= _val;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator/(const T &_val)
{
	return Vec3(x / _val , y / _val , z / _val);
}

template<typename T>
inline Vec3<T> &Vec3<T>::operator/=(const T &_val)
{
	x /= _val;
	y /= _val;
	z /= _val;
	return *this;
}

template<typename T>
inline Vec3<T> Vec3<T>::cross(const Vec3 &_vec)
{
	return Vec3(y * _vec.z - z * _vec.y, z * _vec.x - x * _vec.z, x * _vec.y - y * _vec.x);
}

template<typename T>
inline float Vec3<T>::dot(const Vec3 &_vec)
{
	return x * _vec.x + y * _vec.y + z * _vec.z;
}

template<typename T>
inline float Vec3<T>::length() const
{
	return sqrt(x * x + y * y + z * z);
}

typedef Vec3<float> Vec3f;