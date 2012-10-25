#include <svm.hpp>
#include <iostream>
#include <fstream>


using namespace std;


int main() {
  int n = 8;
  double data[n*2];
  int labels[n];
  for (int i = 0; i < 4; i++) {
    labels[i] = 1;
    labels[i+4] = -1;
  }
  /*
  data[0] = 1;
  data[1] = 0.9;
  data[2] = 1.3;
  data[3] = 1.6;
  data[4] = 2;
  data[5] = 1.9;
  data[6] = 3;
  data[7] = 0.1;

  data[8] = 0.5;
  data[9] = 1;
  data[10] = 0.9;
  data[11] = 0.7;
  data[12] = 2.5;
  data[13] = 3;
  data[14] = 2.2;
  data[15] = 2.23;

  data[16] = 1;
  data[17] = 1.7;
  data[18] = 1.3;
  data[19] = 1.2;

  labels[8] = -1;
  labels[9] = 1; */

  data[0] = 0.2;
  data[1] = 1.0;
  data[2] = 4.0;
  data[3] = 2.8;
  data[4] = 2.0;
  data[5] = 0.5;
  data[6] = 1.0;
  data[7] = 1.7;

  data[8] = 0.7;
  data[9] = 1.5;
  data[10] = 5.0;
  data[11] = 3.7;
  data[12] = 3.0;
  data[13] = 3.5;
  data[14] = 1.5;
  data[15] = 1.7;

  ofstream of("coords.txt", ios_base::trunc);
  for (int i = 0; i < 2*n; i+=2) {
    of << data[i] << ";" << data[i+1] << "\n";
  }
  of.close();

      
  

  SVM<double> svm(data, labels, n, 2);
  svm.trainSVM_primal(0);
  Solution s = svm.giveSolution();
  cout << s;  
  return 0;
}
