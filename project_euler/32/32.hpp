#ifndef EULER_32_HPP
#define EULER_32_HPP

#include <iostream>
#include <set>
#include <algorithm>


bool check_product(int x1, int x2, int res) {
  return (x1*x2) == res;
}

template <typename T>
int get_int_from_array(T* begin, T* end) {
  --end;
  --begin;
  int n_digits = end-begin;
  int res = 0;
  for (int n = 1; end != begin; --end, n *= 10) {
    res += n*(*end);
  }
  return res;
}


void get_set_of_pandigital_products(int* begin, int* end, std::set<int>& prods) {
  int n_digits = end-begin;
  int n_max = 5;
  int x1, x2, res;
  do {
    for (int i = 0; i < n_max-1; ++ i) {
      x1 = get_int_from_array(begin, begin+i);
      x2 = get_int_from_array(begin+i, begin+n_max);
      res = get_int_from_array(begin+n_max, begin+n_digits);
      if (check_product(x1, x2, res)) {
        prods.insert(res);
      }
    }
  } while (std::next_permutation(begin, end));
}


#endif
