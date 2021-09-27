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

constexpr int DIM = 3;

// Input file to read. 
const std::string fname = "./ply_inputs/armadillo.ply";

// How to draw random positions
const int numRanMeshQueries = 32;
const int numRanBVHQueries  = std::pow(numRanMeshQueries, 3);
const Vec3T<T> lo(-100., -100., -100.);
const Vec3T<T> hi( 100.,  100.,  100.);
const Vec3T<T> delta = hi - lo;

int main() {

  // Create a half-edge data structure mesh (dcel) from an input PLY file.
  std::cout << "Reading input file ...";
  auto m = std::make_shared<mesh>();
  dcel::parser::PLY<T>::readASCII(*m, fname);
  m->reconcile();
  const int numFaces = m->getFaces().size();
  std::cout << "File is = '" << fname + "', which has " << numFaces << " faces\n";

  // Make the BVH root node and partition the dcel_face faces. The partitioning functions for dcel_face objects are defined in dcel_BVH.H
  std::cout << "Partitioning BVH...";
  auto root = std::make_shared<BVH::NodeT<T, face, BoundVol> >(m->getFaces());
  root->topDownSortAndPartitionPrimitives(dcel::defaultStopFunction<T, BoundVol>,
					  dcel::partitionMinimumOverlap<T, BoundVol>, //dcel::partitionSAH<T, BoundVol>,
					  dcel::defaultBVConstructor<T, BoundVol>);
  std::cout << " done\n";

  // Init RNG.
  auto rng     = std::mt19937_64(0);
  auto udist01 = std::uniform_real_distribution<T>(0.0, 1.0);

  // Draw a couple of random positions and time the output when using the BVH.
  T totalDistance = 0.0;
  T reguCalls     = 0.0;
  T leafCalls     = 0.0;
  auto totalTime  = std::chrono::duration<T> (0.);
  
  for (int ipos = 0; ipos < numRanBVHQueries; ipos++){
    BVH::reguCalls = 0;
    BVH::leafCalls = 0;
    
    Vec3T<T> randomPosition = lo;
    for (int dir = 0; dir < DIM; dir++){
      randomPosition[dir] += delta[dir]*udist01(rng);
    }
    
    auto tStart = std::chrono::high_resolution_clock::now();
    totalDistance += root->pruneOrdered2(randomPosition);
    auto tEnd = std::chrono::high_resolution_clock::now();
    
    totalTime += std::chrono::duration_cast<std::chrono::duration<T> >(tEnd -tStart);

    reguCalls += 1.0*BVH::reguCalls;
    leafCalls += 1.0*BVH::leafCalls;
  }

  std::cout << "\n";
  std::cout << "BVH queries:\n";
  std::cout << "============\n";
  std::cout << "Number of point queries = " << numRanBVHQueries                   << "\n"
	    << "Regu node queries       = " << reguCalls/numRanBVHQueries         << "\n"
    	    << "Leaf node queries       = " << leafCalls/numRanBVHQueries         << "\n"
    	    << "Total distance          = " << totalDistance                      << "\n"
	    << "Total time              = " << totalTime.count()                  << "\n"
	    << "Avg. time per query     = " << totalTime.count()/numRanBVHQueries << "\n"
	    << "Avg. time per tri       = " << totalTime.count()/(numRanBVHQueries*numFaces) << "\n";


  // Below here, we draw random positions and query the DCEL mesh structure directly. 
  totalDistance = 0.0;
  totalTime     = std::chrono::duration<T> (0.);

  for (int ipos = 0; ipos < numRanMeshQueries; ipos++){

    Vec3T<T> randomPosition = lo;
    for (int dir = 0; dir < DIM; dir++) randomPosition[dir] += delta[dir]*udist01(rng);

    // Compute the signed distance computation.
    const auto tStart = std::chrono::high_resolution_clock::now();
    totalDistance += m->signedDistance(randomPosition);
    const auto tEnd   = std::chrono::high_resolution_clock::now();
    totalTime += std::chrono::duration_cast<std::chrono::duration<T> >(tEnd -tStart);
  }

  std::cout << "\n";
  std::cout << "Direct mesh queries:\n";
  std::cout << "====================\n";
  std::cout << "Number of point queries = " << numRanMeshQueries                   << "\n"
	    << "Total distance          = " << totalDistance                      << "\n"
	    << "Total time              = " << totalTime.count()                   << "\n"
	    << "Avg. time per query     = " << totalTime.count()/numRanMeshQueries << "\n"
	    << "Avg. time per tri       = " << totalTime.count()/(numRanMeshQueries*numFaces) << "\n\n";

}
