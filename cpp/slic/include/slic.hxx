#ifndef SLIC_HXX
#define SLIC_HXX



#include <algorithm>
#include <functional>
#include <limits>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>

#include<vigra/stdimage.hxx>



using namespace vigra;

template <typename T>
class L2Squared;

template <typename T, typename Distance = L2Squared<T> >
class KMeans;

template <int N = 2>
class Slic;

//template <int N>
//typename Slic<N>::DataPoint operator+(typename Slic<N>::DataPoint const& p1, typename Slic<N>::DataPoint const& p2);


template <typename T>
bool isContained(T* begin, T* end, T value) {
  for(; begin != end; begin++) {
    if (*begin == value)
      return true;
  }
  return false;
}

template <typename T>
void divideByScalar(T* start, T* end, T* dest, double scalar) {
  for (; start != end; start++, dest++) {
    *dest = *start/scalar;
  }
}


template <int N>
class Slic {
public:
  struct DataPoint;
  class SlicSquaredDistance;
  
private:
  // data
  BRGBImage img_;
  int* labels_;
  // DataPoint* centers_;
  // DataPoint* data_;
  double* centers_;
  double* data_;
  int nSamples_;
  
  // parameters
  int kx_, ky_;
  int width_;
  double maxSpatialDistance_;
  double weight_;

   
public:
  // constructors, destructor
  Slic() : nSamples_(0) {}
  Slic(BRGBImage& img, int kx, int ky, double maxDist, double weight) :
    img_(img), labels_(0), centers_(0), data_(0), nSamples_(img.width()*img.height()), kx_(kx),
    ky_(ky), maxSpatialDistance_(maxDist), weight_(weight)
  {transformData();}
  Slic(BRGBImage& img, int width, double maxDist, double weight) :
    img_(img), labels_(0), centers_(0), data_(0), nSamples_(img.width()*img.height()),
    width_(width), maxSpatialDistance_(maxDist), weight_(weight)
  {transformDataGivenWidth();}
  ~Slic();


  // data structure to include coordinates and RGB
  struct DataPoint {
    // tiny vectors for coordinates and rgb. split up neccessary for SlicDistance
    TinyVector<double, N> coord_;
    TinyVector<double, 3> RGB_;

    
    DataPoint() {}
    DataPoint(double* coord, double* RGB) :
      coord_(TinyVector<double, N>(coord)), RGB_(TinyVector<double, 3>(RGB)) {}
    DataPoint(TinyVector<double, N> coord, TinyVector<double, 3> RGB) :
      coord_(coord), RGB_(RGB) {}

    DataPoint operator=(DataPoint const& rhs);
    DataPoint operator=(int const& rhs);
    
    friend DataPoint operator+(DataPoint const& p1, DataPoint const& p2) {
      DataPoint p;
      p.coord_ = p1.coord_;
      p.coord_ += p2.coord_;
      p.RGB_ = p1.RGB_;
      p.RGB_ += p2.RGB_;
      return p;
    }
      
    friend DataPoint operator-(DataPoint const& p1, DataPoint const& p2) {
      DataPoint p;
      p.coord_ = p1.coord_;
      p.coord_ -= p2.coord_;
      p.RGB_ = p1.RGB_;
      p.RGB_ -= p2.RGB_;
      return p;
    }
      
    friend DataPoint operator*(DataPoint const& p1, DataPoint const& p2) {
      DataPoint p;
      p.coord_ = p1.coord_;
      p.coord_ *= p2.coord_;
      p.RGB_ = p1.RGB_;
      p.RGB_ *= p2.RGB_;
      return p;
    }
    
    friend DataPoint operator*(double const& scalar, DataPoint const& p) {
      DataPoint res;
      res.coord_ = p.coord_;
      res.coord_ *= scalar;
      res.RGB_ = p.RGB_;
      res.RGB_ *= scalar;
      return res;
    }
    
    friend DataPoint operator*(DataPoint const& p, double const& scalar) {
      return operator*(scalar, p);
    }
    friend DataPoint operator/(DataPoint const& p, double const& scalar) {
      DataPoint res;
      res.coord_ = p.coord_;
      res.coord_ /= scalar;
      res.RGB_ = p.RGB_;
      res.RGB_ /= scalar;
      return res;
    }
      
  };
  

  // distance for Slic
  // obsolete: own datapoint structure
  /*
  class SlicSquaredDistance {
  private:
    double limit_;
    double weight_;
  public:
    SlicSquaredDistance(double limit, double weight) : limit_(limit), weight_(weight) {}
    double operator()(DataPoint* p1, DataPoint* p2, int n);
    }; */

  class SlicSquaredDistance {
  private:
    double limit_;
    double weight_;
  public:
    SlicSquaredDistance(double limit, double weight) : limit_(limit), weight_(weight) {}
    double operator()(double* p1, double* p2, int n);
  };


  void deletePointers();
  // transform data into (x,y,r,g,b)
  void initializeClusters();
  void transformData();
  void transformDataGivenWidth();
  double infer();

  void setImage(BRGBImage img);
  void setK(int kx, int ky) {kx = kx_, ky = ky_;}
  void setWidth(int width) {width_ = width;}
  void setMaxSpatialDistance(double maxDist) {maxSpatialDistance_ = maxDist;}
  void setWeight(double weight) {weight_ = weight;}

  BRGBImage getImage() {return img_;}
  void getK(int* kx, int* ky) {*kx = kx_, *ky =ky_;}
  int getWidth() {return width_;}
  double getMaxSpatialDistance() {return maxSpatialDistance_;}
  double getWeight() {return weight_;}
  
};



template<int U>
typename Slic<U>::DataPoint Slic<U>::DataPoint::operator=(typename Slic<U>::DataPoint const& rhs) {
  coord_ = rhs.coord_;
  RGB_ = rhs.RGB_;
  return rhs;
}

template<int U>
typename Slic<U>::DataPoint Slic<U>::DataPoint::operator=(int const& rhs) {
  coord_.init(rhs);
  RGB_.init(rhs);
  return *this;
}

/* 
// templated typenames only supported from gcc 4.7+
template<int U>
// typedef typename Slic<U>::DataPoint DataPoint
typename Slic<U>::DataPoint operator+(typename Slic<U>::DataPoint const& p1, typename Slic<U>::DataPoint const& p2) {
  typename Slic<U>::DataPoint p;
  p.coord_ = p1.coord_;
  p.coord_ += p2.coord_;
  p.RGB_ = p1.RGB_;
  p.RGB_ += p2.RGB_;
  return p;
}

template<int U>
// typedef typename Slic<U>::DataPoint DataPoint
typename Slic<U>::DataPoint operator-(typename Slic<U>::DataPoint const& p1, typename Slic<U>::DataPoint const& p2) {
  typename Slic<U>::DataPoint p;
  p.coord_ = p1.coord_;
  // p.coord_ -= p2.coord_;
  p.RGB_ = p1.RGB_;
  // p.RGB_ -= p2.RGB_;
  return p;
}

template<int U>
// typedef typename Slic<U>::DataPoint DataPoint
typename Slic<U>::DataPoint operator*(typename Slic<U>::DataPoint const& p1, typename Slic<U>::DataPoint const& p2) {
  typename Slic<U>::DataPoint p;
  p.coord_ = p1.coord_;
  p.coord_ *= p2.coord_;
  p.RGB_ = p1.RGB_;
  p.RGB_ *= p2.RGB_;
  return p;
}

template<int U>
typename Slic<U>::DataPoint operator*(double const& scalar, typename Slic<U>::DataPoint const& p) {
  typename Slic<U>::DataPoint res;
  res.coord_ = p.coord_;
  res.coord_ *= scalar;
  res.RGB_ = p.RGB_;
  res.RGB_ *= scalar;
  return res;
}

template<int U>
typename Slic<U>::DataPoint operator*(typename Slic<U>::DataPoint const& p, double const& scalar) {
  return operator*(scalar, p);
}

template<int U>
typename Slic<U>::DataPoint operator/(typename Slic<U>::DataPoint const& p, double const& scalar) {
  typename Slic<U>::DataPoint res;
  res.coord_ = p.coord_;
  res.coord_ /= scalar;
  res.RGB_ = p.RGB_;
  res.RGB_ /= scalar;
  return res;
  }*/

// obsolete: using datastructure DataPoint
/* template<int N>
double Slic<N>::SlicSquaredDistance::operator()(typename Slic<N>::DataPoint* p1, typename Slic<N>::DataPoint* p2, int n) {
  double sum = 0.0;
  double sumCoord = 0.0;
  double sumRGB = 0.0;
  typename Slic<N>::DataPoint p = (operator-(*p1, *p2))*(operator-(*p1, *p2));
  for (typename TinyVector<double, N>::iterator it = p.coord_.begin(); it != p.coord_.end(); it++) {
    sumCoord += *it;
  }
  for (typename TinyVector<double, 3>::iterator it = p.RGB_.begin(); it != p.RGB_.end(); it++) {
    sumRGB += *it;
  }
  if (sumCoord > limit_)
    return std::numeric_limits<double>::max();
  sum = sumCoord + weight_*sumRGB;
  return sum;
  } */

template<int N>
Slic<N>::~Slic() {
  deletePointers();
}

template<int N>
double Slic<N>::SlicSquaredDistance::operator()(double* p1, double* p2, int n) {
  double sum = 0.0;
  double sumCoord = 0.0;
  double sumRGB = 0.0;
  for (int i = 0; i < N; i++, p1++, p2++) {
    sumCoord += (*p1-*p2)*(*p1-*p2);
  }
  for (int i = 0; i < 3; i++, p1++, p2++) {
    sumRGB += (*p1-*p2)*(*p1-*p2);
  }
  if (sumCoord > limit_)
    return std::numeric_limits<double>::max();
  sum = sumCoord + weight_*sumRGB;
  return sum;
}


template<int N>
void Slic<N>::deletePointers() {
  if(data_)
    delete[] data_, data_ = 0;
  if(centers_)
    delete[] centers_, centers_ = 0;
  if(labels_)
    delete[] labels_, labels_ = 0;
}


template<int N>
void Slic<N>::initializeClusters() {
  if(centers_)
    delete[] centers_, centers_ = 0;
  int sampleDim = N+3;
  centers_ = new double[kx_*ky_*sampleDim];
  double width = 1.0*width_;
  double startWidth = 0.5*width;
  double startWidthY = startWidth;
  double startWidthX;
  double* centers = centers_;
  for (int y = 0; y < ky_; y++, startWidthY += width) {
    startWidthX = startWidth;
    for (int x = 0; x < kx_; x++, startWidthX += width, centers+=N) {
      *centers     = x;
      *(centers+1) = y;
      *(centers+2) = 128.0;
      *(centers+3) = 128.0;
      *(centers+4) = 128.0;
    }
  }
}
  
  

template<int N>
void Slic<N>::transformData() {
  deletePointers();
  int sampleDim = N+3;
  data_ = new double[nSamples_*sampleDim];
  std::fill_n(data_, nSamples_*sampleDim, 0);
  labels_ = new int[nSamples_];
  width_ = img_.width()/kx_;
  std::fill_n(labels_, nSamples_, -1);
  int sample = 0;
  BRGBImage::Iterator end = img_.lowerRight();
  BRGBImage::Iterator ity = img_.upperLeft();
  int coordX, coordY = 0;
  for (; ity.y != end.y; ++ity.y) {
    BRGBImage::Iterator itx = ity;
    coordX = 0;
    for (; itx.x != end.x; ++itx.x) {
      //std::cout << sample << "  " << nSamples_*sampleDim << "\n";
      *(data_ + sample)   = (double) coordX;
      *(data_ + sample+1) = (double) coordY;
      *(data_ + sample+2) = (double) itx->red();
      *(data_ + sample+3) = (double) itx->blue();
      *(data_ + sample+4) = (double) itx->green();
      sample+=sampleDim;
      coordX++;
    }
    coordY++;
  }
  initializeClusters();
}

    
template<int N>
void Slic<N>::transformDataGivenWidth() {
  kx_ = img_.width()/width_;
  ky_ = img_.height()/width_;
  transformData();
}


template<int N>
double Slic<N>::infer() {
  KMeans<double, Slic<N>::SlicSquaredDistance> kMeans(Slic<N>::SlicSquaredDistance(maxSpatialDistance_, weight_), kx_*ky_, 2, 10000);
  return kMeans.infer(data_, nSamples_, N+3, labels_, centers_, 1);
}


template <typename T, typename Distance>
class KMeans {
private:
  Distance metric_;
  int k_;
  int maxIter_;
  double threshold_;
  int* clusterSize_;
  
  void initializeRandom(int* indices, int max);
  double assignLabels(T* data, int nSamples, int nDim, int* labels, T* centers);
  void updateCenters(T* data, int nSamples, int nDim, int* labels, T* centers);
  
public:
  KMeans(Distance metric, int k = 2, int maxIter = 1000, double threshold = 0) :
    metric_(metric), k_(k), maxIter_(maxIter), threshold_(threshold), clusterSize_(0)
  {clusterSize_ = new int[k_];}
  ~KMeans();

  double infer(T* data, int nSamples, int nDim, int* labels, T* centers, int initialize = 0);
};

template <typename T, typename Distance>
KMeans<T, Distance>::~KMeans() {
  //  if(clusterSize_)
    //    delete[] clusterSize_, clusterSize_ = 0;
}

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
      if (!isContained(randNumbers, randNumbers + k_, number))
	break;
    }
    *(randNumbers + i) = number;
  }
  return;
}


template <typename T, typename Distance>
double KMeans<T, Distance>::assignLabels(T* data, int nSamples, int nDim, int* labels, T* centers) {
  double minDist, dist;
  T* tmp;
  T* cluster;
  double sumDistances = 0.0;
  for (int sample = 0; sample < nSamples; sample++) {
    minDist = 10000000.0;
    tmp = data + nDim*sample;
    for (int c = 0; c < k_; c++) {
      cluster = centers + c;
      dist = metric_(cluster, tmp, nDim);
      if (dist < minDist) {
	minDist = dist;
	*(labels + sample) = c;
      }
      sumDistances += minDist;
    }
  }
  tmp = 0;
  cluster = 0;
  return sumDistances;    
}


template <typename T, typename Distance>
void KMeans<T, Distance>::updateCenters(T* data, int nSamples, int nDim, int* labels, T* centers) {
  std::fill_n(clusterSize_, k_, 0);
  std::fill_n(centers, k_*nDim, 0);
  T* end = data + nSamples*nDim;
  for(; data != end; data+=nDim, labels++) {
    std::transform(data, data+nDim, centers + *labels, centers + *labels, std::plus<T>());
    *(clusterSize_ + *labels) += 1;
  }
  for (int c = 0; c < k_; c++) {
    divideByScalar<T>(centers + c*nDim, centers + (c+1)*nDim,
		   centers + c*nDim, *(clusterSize_ + c));
    // std::transform(centers + c*nDim, centers + (c+1)*nDim,
    // centers + c*nDim, std::bind2nd(std::divides<T>(), *(clusterSize_ + c)));
  }
  return;
}
	

template <typename T, typename Distance>
double KMeans<T, Distance>::infer(T* data, int nSamples, int nDim, int* labels, T* centers, int initialize) {
  if (!initialize) {
    int randIndices[k_];
    initializeRandom(randIndices, nSamples - 1);
    for (int i = 0; i < k_; i++) {
      int index = randIndices[i];
      std::copy(data + nDim*index, data + nDim*(index+1), centers + nDim*i);
    }
  }

  double sumDistances = 10000000.0;
  int nIter = 0;
  while  (sumDistances >= threshold_ && nIter < maxIter_) {
    sumDistances = assignLabels(data, nSamples, nDim, labels, centers);
    updateCenters(data, nSamples, nDim, labels, centers);
    nIter++;
    
  }
  return sumDistances;
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
  double operator()(T* p1, T* p2, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++, p1++, p2++) {
      sum += (*p2 - *p1)*(*p2 - *p1);
    }
    return sum;
  }
};



#endif /* SLIC_HXX */
