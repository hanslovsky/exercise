#ifndef SVM_HPP
#define SVM_HPP

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

// choose exact integral type
/* #ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else */
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
// #endif

typedef CGAL::Quadratic_program_solution<ET> Solution;

template<typename T>
class SVM {
private:
  T* features_;
  int* labels_;
  Solution s_;
  // number of samples
  int n_;
  // number of features
  int p_;
public:
  SVM() : features_(0), labels_(0), n_(0), p_(0) {}
  SVM(T* features, int* labels, int n, int p);
  ~SVM();
  // n samples, p features
  // labels must be from {-1, 1}
  void addData(T* features, int* labels, int n, int p);
  void trainSVM_primal(double C);
  void trainSVM_dual();
  // using Radial Basis Functions (RBF)
  void trainSVM_RBF();
  Solution giveSolution() {return s_;}
};

//
template<typename T>
SVM<T>::SVM(T* features, int* labels, int n, int p) :
  features_(features),
  labels_(labels),
  n_(n),
  p_(p)
{

}

template<typename T>
SVM<T>::~SVM() {
  if (features_!= 0) {
    features_ = 0;
    labels_ = 0;
  }
}

template<typename T>
void SVM<T>::addData(T* features, int* labels, int n, int p) {
  if (features_!= 0) {
    features_ = 0;
    labels_ = 0;
  }
  n_ = n;
  p_ = p;
  /* features_ = new T[n*p];
  labels_ = new int[n];
  for (int i = 0; i < n*p; i++) {
    features_[i] = features[i];
  }
  for (int i = 0; i < n; i++) {
    if (labels[i] != -1 and labels[i] != 1)
      throw 20;
    labels_[i] = labels[i];
    } */
  features_ = features;
  labels_ = labels;
}


template<typename T>
void SVM<T>::trainSVM_primal(double C) {
  if (labels_ == 0)
    throw 10;
  // Setting up QP
  //
  // need to reformulate QP:
  //
  // 1/2*w^Tw + C*sum(slack_i)
  // s.t.
  // slack_i >= 0
  // label_i*(w^Tfeatures_i + b) >= 1-slack_i
  // ==> X = (w, slack, b)^T
  // ==> X^TDX + k^TX is new QP
  // s.t. AX >= 1
  // D = diag(...1/2..., 0, 0)
  // k = (0, ...C..., 0)^T
  // A_i = (...features_ij*labels_i..., 0...1...0, labels_i)
  //
  // len(X) = p+n+1
  
  CGAL::Quadratic_program<T> qp;
  // SVM decision boundary
  for (int i = 0; i < p_; i++) {
    qp.set_l(i, 0);
    qp.set_u(i, 0);
  }

  // slack
  for (int i = p_; i < p_ + n_; i++) {
    qp.set_l(i, 1, 0);
    qp.set_u(i, 0);
  }

  // offset
  qp.set_l(p_ + n_, 0);
  qp.set_u(p_ + n_, 0);

  // Setup constraint Matrix A
  for (int i = 0; i < n_; i++) {
    int index = i*p_;
    for (int j = 0; j < p_; j++) {
      T value = features_[index+j]*labels_[i];
      qp.set_a(j, i, value);
    }
    for (int j = p_; j < p_ + n_; j++) {
      if (j - p_ == i)
	qp.set_a(j, i, 1);
      else
	qp.set_a(j, i, 0);
    }
    qp.set_a(n_ + p_, i, labels_[i]);
    qp.set_b(i, 1);
  }

  // Setup D
  for (int i = 0; i <= n_ + p_; i++) {
    for (int j = 0; j < i; j++) {
      if (i < n_ && i == j)
	qp.set_d(i, j, 1);
      else
	qp.set_d(i, j, 0);
    }
  }

  // Setup k (use set_c in CGAL)
  for (int i = 0; i <= n_ + p_; i++) {
    if (i >= p_ && i < n_ + p_)
      qp.set_c(i, C);
    else
      qp.set_c(i, 0);
  }
  // Solving QP
  s_ = CGAL::solve_quadratic_program(qp, ET());

}
  

  

#endif
