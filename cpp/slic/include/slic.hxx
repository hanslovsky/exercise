#ifndef SLIC_HXX
#define SLIC_HXX

#include <algorithm>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>

#include <iostream>

template <typename T>
class L2Squared;


class Slic {

};

template <typename T, typename Distance = L2Squared<T> >
class KMeans {
private:
  Distance metric_;
  int k_;
  int maxIter_;
  void initializeRandom(int* indices, int max);
public:
  KMeans(Distance metric, int k = 2, int maxIter = 1000) :
    metric_(metric), k_(k), maxIter_(maxIter) {}
  double infer(T* data, int nSamples, int nDim, int* labels, T* centers, int initialize = 0);
};

template <typename T, typename Distance>
void KMeans<T, Distance>::initializeRandom(int* randNumbers, int max) {
  boost::mt19937 gen;
  gen.seed(static_cast<unsigned int>(std::time(0)));
  boost::uniform_int<> dist(0, max);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > generate(gen, dist);
  std::fill_n(randNumbers, k_, -1);
  int number;
  for (int i = 0; i < k_; i++) {
    while(true) {
      number = generate();
      if (!std::binary_search(randNumbers, randNumbers + k_, number))
	break;
    }
    *(randNumbers + i) = number;
  }
  return;
}



template <typename T, typename Distance>
double KMeans<T, Distance>::infer(T* data, int nSamples, int nDim, int* labels, T* centers, int initialize) {
  if (initialize == 0) {
    int randIndices[k_];
    initializeRandom(randIndices, nSamples - 1);
    for (int i = 0; i < k_; i++) {
      int index = randIndices[i];
      std::copy(data + nDim*index, data + nDim*(index+1), centers + nDim*i);
    }
  }
  double minDist;
  double dist;
  int minc;
  T* tmp;
  for (int i = 0; i < nSamples; i++) {
    minDist = 10000000.0;
    minc = 0;
    tmp = data + nDim*i;
    for (int c = 0; c < k_; c++) {
      T* cluster = centers + c;
      dist = metric_(cluster, tmp, nDim);
      if (dist < minDist) {
	minDist = dist;
	*(labels + i) = c;
      }
    }
  }
  tmp = 0;
  int* bla = new int(3);
  return 3.0;
}


template <typename T>
class L2Squared {
public:
  double operator()(T p1, T p2) { 
    return (p2 - p1)*(p2 - p1);
  }
};

template <typename T>
class L2SquaredArray {
public:
  double operator()(T*& p1, T*& p2, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++, p1++, p2++) {
      sum += (*p2 - *p1)*(*p2 - *p1);
    }
    return sum;
  }
};



#endif /* SLIC_HXX */
