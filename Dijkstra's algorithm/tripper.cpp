// Author Sean Davis
#include <iostream>
#include "tripper.h"
#include "RoadRunner.h"


using namespace std;
City::City(){
  for (int i = 0; i < 9;i++){
    connected[i] = -1;
    dist_to_city[i] = -1;
    road_ID[i] = -1;
  }
  
}
City::~City(){
  // delete[] connected;
  // delete[] dist_to_city; 
  // delete[] road_ID;
}

int Tripper::getDist(int city2, int city1){
  for (int i = 0;i < 8;i++){
    if (cities[city1].connected[i] == city2){
      return cities[city1].dist_to_city[i];
    }
  }
  //cout<<"returning -1"<<endl;
  return -1;
}

int Tripper::getRoad(int city2, int city1){
//	cout<<"getting road from : " <<city1<< " to :" << city2<<endl;
  for (int i = 0;i < 8;i++){
    if (cities[city1].connected[i] == city2){
      
    
      return cities[city1].road_ID[i];
    }
  }
  return -1;
}

Tripper::Tripper(Road *roads, int numRoads, int size)
{

  city_size = size;
  
  BinaryHeap heapS(10001);
  BinaryHeap heapT(10001);
  int itr;
  for (int i = 0; i<numRoads;i++){ //storing roads into class City cities
    itr = 0;
    while(cities[roads[i].city1].connected[itr]!=-1){
      itr++;
    }
    cities[roads[i].city1].connected[itr] = roads[i].city2;
    cities[roads[i].city1].dist_to_city[itr] = roads[i].distance;
    cities[roads[i].city1].road_ID[itr] = roads[i].num;

    
  } // end for loop  
  /*
   for (int i = 0 ; i < city_size*city_size ; i++){
     cout<<"city "<< i << "is connected to city ";
     for (int j = 0; j < 8; j++){
      cout<<cities[i].connected[j]<<" ";
     }
     cout<<endl;
     cout<< "with distance : ";
     for (int j = 0 ; j < 8 ; j++){
      cout<< cities[i].dist_to_city[j]<<" ";
     }
     cout<<endl;
   }
   */
  
} // Tripper()



Tripper::~Tripper()
{
  // delete[] dist[0];
  // delete[] dist[1];
  // delete[] dist;
  // delete[] prev[0];
  // delete[] prev[1];
  // delete[] prev;
  // delete[] known[0];
  // delete[] known[1];
  // delete[] known;
  // delete[] cities;
  // delete[] heapS;
  // delete[] heapT;


} // ~Tripper()

int Tripper::findMinDist(int S_or_T){
  Pair min_pair ;
  int min_i ;
  switch (S_or_T){
    case 0:
    min_pair = heapS.findMin();
    min_i = min_pair.city_num;
    //cout<<"popping dist : "<<min_pair.dist << " ,city_num = " << min_pair.city_num<<endl;
    while (known[S_or_T][min_i]==true){
      //cout<<"discard above\n\n\n\n"<<endl;
      heapS.deleteMin();
      min_pair = heapS.findMin();
      min_i = min_pair.city_num;
    }
    topS = min_pair.dist;
    heapS.deleteMin();
    break;
    case 1:
    min_pair = heapT.findMin();
    min_i = min_pair.city_num;
    //cout<<"popping dist : "<<min_pair.dist << " ,city_num = " << min_pair.city_num<<endl;
    while (known[S_or_T][min_i]==true){
      //cout<<"discard above\n\n\n\n"<<endl;
      heapT.deleteMin();
      min_pair = heapT.findMin();
      min_i = min_pair.city_num;
    }
    topT = min_pair.dist;
    heapT.deleteMin();
    break;
  }
  return min_i;
}

void Tripper::updateDist(int updating_city,int S_or_T){
  //cout<<mu<<endl;
  known[S_or_T][updating_city] = true;
  int itr = 0;
  int city_id;
  int city_dist;
  int temp_dist;
  Pair new_pair;
  
  //cout<<"for city : "<< updating_city << endl;
  for(;true;itr++){
    if (cities[updating_city].connected[itr] == -1)
      break;
    city_id = cities[updating_city].connected[itr];
    if (known[S_or_T][city_id]==false){
      city_dist = getDist(city_id,updating_city);
      temp_dist = dist[S_or_T][updating_city] + city_dist;
      if (dist[S_or_T][city_id]>temp_dist){  
        new_pair.dist = temp_dist;
        new_pair.city_num = city_id;
        //cout<<heap.currentSize<<endl;
        //cout<<"inserting : dist = " << new_pair.dist <<" ,city_num = "<< new_pair.city_num<<endl;
        switch (S_or_T){
          case 0:
            heapS.insert(new_pair);
            break;
          
          case 1:
            heapT.insert(new_pair);
            break;
        } // inserting min to either heap
        dist[S_or_T][city_id] = temp_dist;
        prev[S_or_T][city_id] = updating_city;
      }
    }
    
  }
  int  temp_mu;
  switch (S_or_T){
    case 0:
    if (known[1][updating_city] == true){
        
        temp_mu = dist[0][updating_city] + dist[1][updating_city];
        if (temp_mu < mu){
	    mu = temp_mu;
	    meeting_city = updating_city;
	}

    }
    break;
    case 1:
    if (known[0][updating_city] == true){
      temp_mu = dist[0][updating_city]+dist[1][updating_city];
      if (temp_mu<mu){
        meeting_city = updating_city;
        mu = temp_mu;
      }
    }
    break;
  }
}

void Tripper::initialize(){
  topS = 0;
  topT = 0;
  mu = 1000000;
  for (int i = 0; i < city_size*city_size;i++){
    dist[0][i] = 1000000;
    known[0][i] = false;
  }
  for (int i = 0; i < city_size*city_size;i++){
    dist[1][i] = 1000000;
    known[1][i] = false;
  }
  //cout<<"made it here ??"<<endl;
}

void Tripper::startChecking(int city1,int city2){
  int next_city = city1;
  dist[0][next_city] = 0;
  prev[0][next_city] = city1;
  known[0][next_city] = true;
  int back_city = city2;
  dist[1][back_city] = 0;
  prev[1][back_city] = city2;
  known[1][back_city] = true;
  while(topS+topT<mu+40){
    updateDist(next_city,0);
  
    next_city = findMinDist(0);
    
    updateDist(back_city,1);
    
    back_city = findMinDist(1);

    //cout<<mu<<endl;
  }
}

int Tripper::findPath(int city1, int city2, int path[], int *pathCount)
{ 
  //cout<<"made it here 5 "<<endl;
  initialize();
  //cout<<"made it here ??"<<endl;
  startChecking(city1,city2);
  
  
  // Edit Path
  
  int city_itr = meeting_city;
  int temp_city = meeting_city;
  int path_itr = 0;
  *pathCount = 0;
	
  while(city_itr != city1){
//	 cout<<city_itr<<endl;
     //cout<<"made it here 1 "<<endl;
     temp_city = getRoad(city_itr,prev[0][city_itr]);
     path[path_itr] = temp_city;
     //cout<<"ID : "<<path[path_itr]<<endl;
     city_itr = prev[0][city_itr];
     path_itr++;
     (*pathCount)++;
  }
  // cout<<"made it here 2 "<<endl;
  int temp_count = (*pathCount) ;
  int temp;
//	cout<<"switching"<<endl;
  for (int i = 0; i<temp_count/2; i++){
     temp = path[i];
     path[i] = path[temp_count-i-1];
     path[temp_count-i-1] = temp;
  }
  city_itr = meeting_city;
  temp_city = meeting_city;
  path_itr = (*pathCount);
	
  while(city_itr != city2){
	 // cout<<city_itr<<endl;
    temp_city = getRoad(prev[1][city_itr],city_itr);
    path[path_itr] = temp_city;
  //  cout<<"ID : "<<path[path_itr]<<endl;
    city_itr = prev[1][city_itr];
    path_itr++;
    (*pathCount)++;
  }
 // for (int i = 0; i<(*pathCount);i++){
 // 	cout<<path[i]<<endl;
 // }
  // cout<<"meeting city = "<< meeting_city<<endl; 
  //	for (int i = 0 ; i<temp_count;i++){
  //		cout<<path[i]<<endl;
  //	}
   
  // cout<<"made it here 3 "<<endl;
  heapS.makeEmpty();
  heapT.makeEmpty();
  //cout<<"made it here 4 "<<endl;
  //cout<<mu<<endl;
  return mu;  // to avoid warning for now

}  // findPath()










BinaryHeap::BinaryHeap( int capacity )
: currentSize(0)
{
  array = new Pair[capacity + 1];
}

const Pair & BinaryHeap::findMin( ) const
{
  return array[ 1 ];
}

void BinaryHeap::deleteMin( )
{
  array[ 1 ] = array[ currentSize-- ];
    int child;
    int hole = 1;
/* 2*/      Pair tmp = array[ 1 ];

/* 3*/      for( ; hole * 2 <= currentSize; hole = child )
            {
/* 4*/          child = hole * 2;
/* 5*/          if( child != currentSize && (array[ child + 1 ]).dist < (array[ child ]).dist )
/* 6*/              child++;
/* 7*/          if( (array[ child ]).dist < tmp.dist )
/* 8*/              array[ hole ] = array[ child ];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;
}

void BinaryHeap::insert(const Pair & x){
               // Percolate up
  int hole = ++currentSize;
  for( ; hole > 1 && x.dist < (array[ hole / 2 ]).dist; hole /= 2 )
    array[ hole ] = array[ hole / 2 ];
  array[ hole ] = x;
}

void BinaryHeap::makeEmpty( )
{
  currentSize = 0;
}

BinaryHeap::~BinaryHeap(){
  delete[] array;
}

void BinaryHeap::percolateDown( int hole )
{
/* 1*/      


// /* 3*/      for( ; hole * 2 <= currentSize; hole = child )
//             {
// /* 4*/          child = hole * 2;
// /* 5*/          if( child != currentSize && (array[ child + 1 ]).dist < (array[ child ]).dist )
// /* 6*/              child++;
// /* 7*/          if( (array[ child ]).dist < tmp.dist )
// /* 8*/              array[ hole ] = array[ child ];
//                 else
// /* 9*/              break;
//             }
// /*10*/      array[ hole ] = tmp;
}
