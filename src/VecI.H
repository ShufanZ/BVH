/*!
  @file   VecI.H
  @brief  Implementation of Vec.H
  @author Robert Marskar
  @date   March 2021
*/

#ifndef _VECI_H_
#define _VECI_H_

#include "Vec.H"

#include <math.h>
#include <algorithm>

template <class T>
inline
Vec2T<T>::Vec2T(){
  *this = Vec2T<T>::zero();
}

template <class T>
inline
Vec2T<T>::Vec2T(const Vec2T& u){
  x = u.x;
  y = u.y;
}

template <class T>
inline
Vec2T<T>::Vec2T(const T& a_x, const T& a_y){
  x = a_x;
  y = a_y;
}

template <class T>
inline
Vec2T<T> Vec2T<T>::zero() noexcept {
  return Vec2T<T>(0., 0.);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::one() noexcept {
  return Vec2T<T>(1., 1.);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::min() noexcept {
  return Vec2T<T>(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::max());
}

template <class T>
inline
Vec2T<T> Vec2T<T>::max() noexcept {
  return Vec2T<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template <class T>
inline
Vec2T<T> Vec2T<T>::infinity() noexcept {
  return Vec2T<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
}

template <class T>
inline
Vec2T<T>& Vec2T<T>::operator=(const Vec2T<T>& u) noexcept {
  x = u.x;
  y = u.y;

  return (*this);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::operator+(const Vec2T<T>& u) const noexcept {
  return Vec2T<T>(x+u.x, y+u.y);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::operator-(const Vec2T<T>& u) const noexcept {
  return Vec2T<T>(x-u.x, y-u.y);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::operator-() const noexcept {
  return Vec2T<T>(-x, -y);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::operator*(const T& s) const noexcept {
  return Vec2T<T>(x*s, y*s);
}

template <class T>
inline
Vec2T<T> Vec2T<T>::operator/(const T& s) const noexcept {
  const T is = 1./s;
  return Vec2T<T>(x*is, y*is);
}

template <class T>
inline
Vec2T<T>& Vec2T<T>::operator+=(const Vec2T<T>& u) noexcept {
  x += u.x;
  y += u.y;

  return (*this);
}

template <class T>
inline
Vec2T<T>& Vec2T<T>::operator-=(const Vec2T<T>& u) noexcept {
  x -= u.x;
  y -= u.y;

  return (*this);
}

template <class T>
inline
Vec2T<T>& Vec2T<T>::operator*=(const T& s) noexcept {
  x *= s;
  y *= s;

  return (*this);
}

template <class T>
inline
Vec2T<T>& Vec2T<T>::operator/=(const T& s) noexcept {
  const T is = 1./s;
    
  x *= is;
  y *= is;

  return (*this);
}

template <class T>
inline
T Vec2T<T>::dot(const Vec2T<T>& u) const noexcept {
  return x*u.x + y*u.y;
}

template <class T>
inline
T Vec2T<T>::length() const noexcept {
  return sqrt(x*x + y*y);
}

template <class T>
inline
T Vec2T<T>::length2() const noexcept {
  return x*x + y*y;
}

template <class T>
inline
Vec2T<T> operator*(const T& s, const Vec2T<T>& a_other) noexcept {
  return a_other*s;
}

template <class T>
inline
Vec2T<T> operator/(const T& s, const Vec2T<T>& a_other) noexcept {
  return a_other/s;
}

template <class T>
inline
Vec3T<T>::Vec3T(){
  (*this) = Vec3T<T>::zero();
}

template <class T>
inline
Vec3T<T>::Vec3T(const Vec3T<T>& u) {
  X[0] = u[0];
  X[1] = u[1];
  X[2] = u[2];
}

template <class T>
inline
Vec3T<T>::Vec3T(const T& a_x, const T& a_y, const T& a_z){
  X[0] = a_x;
  X[1] = a_y;
  X[2] = a_z;
}

template <class T>
inline
Vec3T<T> Vec3T<T>::zero() noexcept {
  return Vec3T<T>(0, 0, 0);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::one() noexcept {
  return Vec3T<T>(1, 1, 1);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::min() noexcept {
  return Vec3T<T>(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::max(), -std::numeric_limits<T>::max());
}

template <class T>
inline
Vec3T<T> Vec3T<T>::max() noexcept {
  return Vec3T<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template <class T>
inline
Vec3T<T> Vec3T<T>::infinity() noexcept {
  return Vec3T<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
}

template <class T>
inline
Vec3T<T>& Vec3T<T>::operator=(const Vec3T<T>& u) noexcept {
  X[0] = u[0];
  X[1] = u[1];
  X[2] = u[2];

  return (*this);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::operator+(const Vec3T<T>& u) const noexcept {
  return Vec3T<T>(X[0]+u[0], X[1]+u[1], X[2]+u[2]);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::operator-(const Vec3T<T>& u) const noexcept {
  return Vec3T<T>(X[0]-u[0], X[1]-u[1], X[2]-u[2]);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::operator-() const noexcept {
  return Vec3T<T>(-X[0], -X[1], -X[2]);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::operator*(const T& s) const noexcept {
  return Vec3T<T>(s*X[0], s*X[1], s*X[2]);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::operator/(const T& s) const noexcept {
  const T is = 1./s;
  return Vec3T<T>(is*X[0], is*X[1], is*X[2]);
}
  
template <class T>
inline
Vec3T<T>& Vec3T<T>::operator+=(const Vec3T<T>& u) noexcept {
  X[0] += u[0];
  X[1] += u[1];
  X[2] += u[2];

  return (*this);
}

template <class T>
inline
Vec3T<T>& Vec3T<T>::operator-=(const Vec3T<T>& u) noexcept {
  X[0] -= u[0];
  X[1] -= u[1];
  X[2] -= u[2];

  return (*this);
}

template <class T>
  
inline
Vec3T<T>& Vec3T<T>::operator*=(const T& s) noexcept {
  X[0] *= s;
  X[1] *= s;
  X[2] *= s;

  return (*this);
}

template <class T>
inline
Vec3T<T>& Vec3T<T>::operator/=(const T& s) noexcept {
  const T is = 1./s;
    
  X[0] *= is;
  X[1] *= is;
  X[2] *= is;

  return (*this);
}

template <class T>
inline
Vec3T<T> Vec3T<T>::cross(const Vec3T<T>& u) const noexcept {
  return Vec3T<T>(X[1]*u[2] - X[2]*u[1],
		  X[2]*u[0] - X[0]*u[2],
		  X[0]*u[1] - X[1]*u[0]);
}

template <class T>
inline
T& Vec3T<T>::operator[](int i) noexcept {
  return X[i];
}

template <class T>
inline
const T& Vec3T<T>::operator[](int i) const noexcept {
  return X[i];
}

template <class T>
inline
Vec3T<T> Vec3T<T>::min(const Vec3T<T>& u) noexcept {
  X[0] = std::min(X[0], u[0]);
  X[1] = std::min(X[1], u[1]);
  X[2] = std::min(X[2], u[2]);

  return *this;
}

template <class T>
inline
Vec3T<T> Vec3T<T>::max(const Vec3T<T>& u) noexcept {
  X[0] = std::max(X[0], u[0]);
  X[1] = std::max(X[1], u[1]);
  X[2] = std::max(X[2], u[2]);

  return *this;
}

template <class T>
inline
int Vec3T<T>::maxDir(const bool a_doAbs) const noexcept {
  int mDir = 0;
    
  for (int dir = 0; dir < 3; dir++){
    if (a_doAbs){
      if (std::abs(X[dir]) > std::abs(X[mDir])) {
	mDir = dir;
      }
    }
    else{
      if (X[dir] > X[mDir]){
	mDir = dir;
      }
    }
  }
    
  return mDir;
}

template <class T>
inline
bool Vec3T<T>::operator==(const Vec3T<T>& u) const noexcept {
  return (X[0]==u[0] && X[1]==u[1] && X[2]==u[2]);
}

template <class T>
inline
bool Vec3T<T>::operator<(const Vec3T<T>& u) const noexcept {
  return (X[0]<u[0] && X[1]<u[1] && X[2]<u[2]);
}

template <class T>
inline
bool Vec3T<T>::operator>(const Vec3T<T>& u) const noexcept {
  return (X[0]>u[0] && X[1]>u[1] && X[2]>u[2]);
}

template <class T>
inline
bool Vec3T<T>::operator<=(const Vec3T<T>& u) const noexcept {
  return (X[0]<=u[0] && X[1]<=u[1] && X[2]<=u[2]);
}

template <class T>
  
inline
bool Vec3T<T>::operator>=(const Vec3T<T>& u) const noexcept {
  return (X[0]>=u[0] && X[1]>=u[1] && X[2]>=u[2]);
}

template <class T>
inline
T Vec3T<T>::dot(const Vec3T<T>& u) const noexcept {
  return X[0]*u[0] + X[1]*u[1] + X[2]*u[2];
}

template <class T>
inline
T Vec3T<T>::length() const noexcept {
  return sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]);
}

template <class T>
inline
T Vec3T<T>::length2() const noexcept {
  return X[0]*X[0] + X[1]*X[1] + X[2]*X[2];
}

template <class T>
inline
Vec3T<T> operator*(const T& s, const Vec3T<T>& a_other) noexcept {
  return a_other*s;
}

template <class T>
inline
Vec3T<T> operator/(const T& s, const Vec3T<T>& a_other) noexcept {
  return a_other/s;
}

template <class T>
inline
Vec3T<T> min(const Vec3T<T>& u, const Vec3T<T>& v) noexcept {
  return Vec3T<T>(std::min(u[0], v[0]),
		  std::min(u[1], v[1]),
		  std::min(u[2], v[2]));
}

template <class T>
inline
Vec3T<T> max(const Vec3T<T>& u, const Vec3T<T>& v) noexcept {
  return Vec3T<T>(std::max(u[0], v[0]),
		  std::max(u[1], v[1]),
		  std::max(u[2], v[2]));
}

#endif
