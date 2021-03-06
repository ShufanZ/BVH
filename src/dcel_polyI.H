/*!
  @file   dcel_polyI.H
  @brief  Implementation of dcel_poly.H
  @author Robert Marskar
  @date   March 2021
*/

#ifndef _DCEL_POLYI_H_
#define _DCEL_POLYI_H_

#include "dcel_poly.H"

#include <iostream>

namespace dcel {

  template <class T>
  inline
  Polygon2D<T>::Polygon2D(const Vec3& a_normal, const std::vector<Vec3>& a_points) {
    this->define(a_normal, a_points);
  }

  template <class T>
  inline
  bool Polygon2D<T>::isPointInside(const Vec3& a_point, const InsideOutsideAlgorithm a_algorithm) const noexcept {
    bool ret;
    
    switch(a_algorithm){
    case InsideOutsideAlgorithm::SubtendedAngle:
      ret = this->isPointInsidePolygonSubtend(a_point);
      break;
    case InsideOutsideAlgorithm::CrossingNumber:
      ret = this->isPointInsidePolygonCrossingNumber(a_point);
      break;
    case InsideOutsideAlgorithm::WindingNumber:
      ret = this->isPointInsidePolygonWindingNumber(a_point);
      break;
    default:
      std::cerr << "In file 'dcel_polyI.H' function dcel::Polygon2D<T>::isPointInside - unsupported algorithm requested.\n";
    }

    return ret;
  }

  template <class T>
  inline
  Vec2T<T> Polygon2D<T>::projectPoint(const Vec3& a_point) const noexcept {
    return Vec2(a_point[m_xDir], a_point[m_yDir]);
  }

  template <class T>
  inline
  void Polygon2D<T>::define(const Vec3& a_normal, const std::vector<Vec3>& a_points) {
    const auto& nx = std::abs(a_normal[0]);
    const auto& ny = std::abs(a_normal[1]);
    const auto& nz = std::abs(a_normal[2]);

    m_ignoreDir = 0;
  
    for (int dir = 0; dir < 3; dir++){
      if(std::abs(a_normal[dir]) > std::abs(a_normal[m_ignoreDir])) {
	m_ignoreDir = dir;
      }
    }

    m_xDir = 3;
    m_yDir = -1;
  
    for (int dir = 0; dir < 3; dir++){
      if(dir != m_ignoreDir){
	m_xDir = std::min(m_xDir, dir);
	m_yDir = std::max(m_yDir, dir);
      }
    }

    for (const auto& p3 : a_points){
      m_points.emplace_back(this->projectPoint(p3));
    }
  }

  template <class T>
  inline 
  int Polygon2D<T>::computeWindingNumber(const Vec2& P) const noexcept {
    int wn = 0;    // the  winding number counter

    const int N = m_points.size();

    auto isLeft = [](const Vec2& P0, const Vec2& P1, const Vec2& P2){
      return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x -  P0.x)*(P1.y - P0.y);
    };

    // loop through all edges of the polygon
    for (int i = 0; i < N; i++) {   // edge from V[i] to  V[i+1]

      const Vec2& P1 = m_points[i];
      const Vec2& P2 = m_points[(i+1)%N];

      const T res = isLeft(P1, P2, P);
    
      if (P1.y <= P.y) {          // start y <= P.y
	if (P2.y  > P.y)      // an upward crossing
	  if (res > 0.)  // P left of  edge
	    ++wn;            // have  a valid up intersect
      }
      else {                        // start y > P.y (no test needed)
	if (P2.y <= P.y)     // a downward crossing
	  if (res < 0.)  // P right of  edge
	    --wn;            // have  a valid down intersect
      }
    }
  
    return wn;
  }

  template <class T>
  inline
  int Polygon2D<T>::computeCrossingNumber(const Vec2& P) const noexcept {
    int cn = 0; 

    const int N = m_points.size();

    constexpr T thresh = 1.E-6;
  
    for (int i = 0; i < N; i++) {    // edge from V[i]  to V[i+1]
      const Vec2& P1 = m_points[i];
      const Vec2& P2 = m_points[(i+1)%N];

      const bool upwardCrossing   = (P1.y <= P.y) && (P2.y >  P.y);
      const bool downwardCrossing = (P1.y >  P.y) && (P2.y <= P.y);

      if(upwardCrossing || downwardCrossing){
	const T t = (P.y - P1.y)/(P2.y - P1.y);

	if (P.x <  P1.x + t * (P2.x - P1.x)) {// P.x < intersect
	  cn += 1;   // a valid crossing of y=P.y right of P.x
	}
      }
    }

    return cn;
  }

  template <class T>
  inline
  T Polygon2D<T>::computeSubtendedAngle(const Vec2& p) const noexcept {
    T sumTheta = 0.0;
  
    const int N = m_points.size();

    constexpr T thresh = 1.E-6;
  
    for (int i = 0; i < N; i++){
      const Vec2 p1 = m_points[i]       - p;
      const Vec2 p2 = m_points[(i+1)%N] - p;
    
      const T theta1 = atan2(p1.y, p1.x);
      const T theta2 = atan2(p2.y, p2.x);

      T dTheta = theta2 - theta1;

      while (dTheta > M_PI)
	dTheta -= 2.0*M_PI;
      while (dTheta < -M_PI)
	dTheta += 2.0*M_PI;

      sumTheta += dTheta;
    }

    return sumTheta;
  }

  template <class T>
  inline
  bool Polygon2D<T>::isPointInsidePolygonWindingNumber(const Vec3& a_point) const noexcept {
    const Vec2 p = this->projectPoint(a_point);
  
    const int wn = this->computeWindingNumber(p);

    return wn != 0;
  }

  template <class T>
  inline
  bool Polygon2D<T>::isPointInsidePolygonCrossingNumber(const Vec3& a_point) const noexcept {
    const Vec2 p = this->projectPoint(a_point);
  
    const int cn  = this->computeCrossingNumber(p);
    
    const bool ret = (cn&1);

    return ret;
  }

  template <class T>
  inline
  bool Polygon2D<T>::isPointInsidePolygonSubtend(const Vec3& a_point) const noexcept {
    const Vec2 p = this->projectPoint(a_point);

    T sumTheta = this->computeSubtendedAngle(p); // Should be = 2pi if point is inside. 

    sumTheta = std::abs(sumTheta)/(2.*M_PI); 

    const bool ret = (round(sumTheta) == 1); // 2PI if the polygon is inside. 

    return ret;
  }
}
#endif
