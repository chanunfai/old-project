// Author Sean Davis
#ifndef _TRIPPER_H
#define	_TRIPPER_H

#include "RoadRunner.h"

class City{
public:
  City();
  ~City();
  int connected[10];
  int dist_to_city[10]; 
  int road_ID[10];
  int table_size;
};


class Pair{
public:
  int city_num;
  int dist;
  // friend bool operator< (Pair const& lhs,Pair const& rhs){
  //   return (lhs.dist<rhs.dist);
  // }
};

class BinaryHeap{
public:
  explicit BinaryHeap( int capacity = 100000 );
  ~BinaryHeap();
  bool isEmpty( ) const;
  bool isFull( ) const;
  const Pair & findMin( ) const;
  void deleteMin( );
  void insert( const Pair &x);
  void percolateDown( int hole );
  void makeEmpty( );
  int currentSize;  // Number of elements in heap
  Pair* array;
};


class Tripper {
public:
  Tripper(Road *roads, int numRoads, int size);
  int findPath(int city1, int city2, int path[], int *pathCount);
  ~Tripper();
  int getDist(int city1, int city2);
  int findMinDist(int S_or_T);
  void updateDist(int updating_city,int S_or_T);
  int getRoad(int city1, int city2);
  void initialize();
  void startChecking(int city1,int city2);
  void hash(int city1,int city2,int dist,int num);
private:
  int table_size;
  
  int topS;
  int topT;
  int mu;
  int min_mu;
  int meeting_city;
  int dist[2][10000];
  int prev[2][10000];
  bool known[2][10000];
  int city_size;
  BinaryHeap heapS;
  BinaryHeap heapT;

  City cities[10000];
}; // class Tripper



#endif	/* _TRIPPER_H */

