#include "dcel_vertex.H"
#include "dcel_edge.H"
#include "dcel_face.H"
#include "dcel_mesh.H"
#include "dcel_parser.H"
#include "dcel_BVH.H"
#include "BoundingVolumes.H"
#include "BVH.H"

#include <chrono>
#include <random>

// Specifies precision for BVH/DCEL magic, and which bounding volume to use. 
using T         = float;
using face      = dcel::faceT<T>;
using mesh      = dcel::meshT<T>;
using BoundVol  = BoundingVolumes::AABBT<T>;

// Input file to read. 
const std::string fname = "./ply_inputs/armadillo.ply";

int main() {

  // Create a half-edge data structure mesh (dcel) from an input PLY file. 
  auto m = std::make_shared<mesh>();
  dcel::parser::PLY<T>::readASCII(*m, fname);
  m->reconcile();

  // Make the BVH root node and partition the dcel_face faces. The partitioning functions for dcel_face objects are defined in dcel_BVH.H
  auto root = std::make_shared<BVH::NodeT<T, face, BoundVol> >(m->getFaces());
  root->topDownSortAndPartitionPrimitives(dcel::defaultStopFunction<T, BoundVol>,
					  dcel::partitionSAH<T, BoundVol>,
					  dcel::defaultBVConstructor<T, BoundVol>);

  // To get a (signed) distance you will do (other BVH pruning functions are available but this is the fastest one). 
  const T dist = root->pruneOrdered2(Vec3T<T>::one());
}
