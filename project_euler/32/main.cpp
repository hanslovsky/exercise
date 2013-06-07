#include <iostream>
#include <set>
#include <numeric>

#include "32.hpp"


int main() {
  int digits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> prods;
  get_set_of_pandigital_products(digits, digits+9, prods);
  std::cout << "Sum of pandigital products for n=9: "
            << std::accumulate(prods.begin(), prods.end(), 0)
            << '\n';
  return 0;
}
