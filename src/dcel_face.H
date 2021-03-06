/*!
  @file   dcel_face.H
  @brief  Implementation of dcel_face.H
  @author Robert Marskar
  @date   March 2021
*/

#ifndef _DCEL_FACE__
#define _DCEL_FACE__

#include "Vec.H"

#include "dcel_algorithms.H"
#include "dcel_vertex.H"
#include "dcel_edge.H"
#include "dcel_poly.H"

#include <memory>
#include <vector>

namespace dcel {

  template <class T> class vertexT;
  template <class T> class edgeT;
  template <class T> class faceT;
  template <class T> class edgeIteratorT;
  
  template <class T>
  class faceT {
  public:

    using Vec3   = Vec3T<T>;
    
    using vertex = vertexT<T>;
    using edge   = edgeT<T>;
    using face   = faceT<T>;

    using vertexPtr = std::shared_ptr<vertex>;
    using edgePtr   = std::shared_ptr<edge>;
    using facePtr   = std::shared_ptr<face>;

    using edgeIterator = edgeIteratorT<T>;
    
    faceT();
    
    faceT(const edgePtr& a_edge);
    
    faceT(const face& a_otherFace);
    
    ~faceT();

    inline
    void define(const Vec3& a_normal, const edgePtr& a_edge) noexcept;

    inline
    void reconcile() noexcept;

    inline
    void setHalfEdge(const edgePtr& a_halfEdge) noexcept;

    inline
    void setInsideOutsideAlgorithm(const InsideOutsideAlgorithm& a_algorithm) noexcept;

    inline
    edgePtr& getHalfEdge() noexcept;

    inline
    const edgePtr& getHalfEdge() const noexcept;

    inline
    Vec3T<T>& getCentroid() noexcept;

    inline
    const Vec3T<T>& getCentroid() const noexcept;

    inline
    T& getCentroid(const int a_dir) noexcept;

    inline
    const T& getCentroid(const int a_dir) const noexcept;

    inline
    Vec3T<T>& getNormal() noexcept;

    inline
    const Vec3T<T>& getNormal() const noexcept;

    inline
    T signedDistance(const Vec3& a_x0) const noexcept;

    inline
    T unsignedDistance2(const Vec3& a_x0) const noexcept;

    inline
    std::vector<Vec3T<T> > getAllVertexCoordinates() const noexcept;

    inline
    std::vector<vertexPtr> gatherVertices() const noexcept;

    inline
    Vec3T<T> getSmallestCoordinate() const noexcept;

    inline
    Vec3T<T> getHighestCoordinate() const noexcept;
  
  protected:
    
    edgePtr m_halfEdge; // One of the edges. This must always be != nullptr for a valid face.
    
    std::vector<edgePtr > m_edges; // Exists because of performance reasons. 

    T m_area;
    
    Vec3 m_normal;
    Vec3 m_centroid;

    // 2D polygon
    std::shared_ptr<Polygon2D<T> > m_poly2;
    InsideOutsideAlgorithm m_poly2Algorithm;

    inline
    void computeArea() noexcept;

    inline
    void computeCentroid() noexcept;

    inline
    void computeNormal() noexcept;

    inline
    void computePolygon2D() noexcept;
    
    inline
    void normalizeNormalVector() noexcept;

    inline
    T getArea() noexcept;

    inline
    T getArea() const noexcept;

    inline
    void computeAndStoreEdges() noexcept;

    inline
    Vec3T<T> projectPointIntoFacePlane(const Vec3& a_p) const noexcept;

    inline
    bool isPointInsideFace(const Vec3& a_p) const noexcept;
  };

}

#include "dcel_faceI.H"

#endif
