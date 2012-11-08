#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// reads the data pasted to a txt file from project euler
// it reads each line and then splits each line by the seperator ' '
void readTriangleToVector(ifstream& f, vector<vector<int> >& data) {
  string line;
  while (f.good()) {
    getline(f, line);
    vector<int> tmp;
    string::iterator it = line.begin();
    while (!line.empty()) {
      stringstream numberAsStream;
      int number;
      while (*it != ' ' and it != line.end()) {
	numberAsStream << *it;
	it++;
      }
      numberAsStream >> number;
      tmp.push_back(number);
      if (it == line.end()) {
	break;
      }
      else {
	it++;
      }
    }
    if (tmp.size() > 0)
      data.push_back(tmp);
  }
}

int main() {
  // reading the data
  ifstream f("triangle.txt", fstream::in);
  vector<vector<int> > data;
  readTriangleToVector(f, data);
  /* for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data.at(i).size(); j++) {
      printf("%02d ", data.at(i).at(j));
    }
    cout << "\n";
    } */

  // at each point of the triangle, the maximum sum
  // is the number at that plus the maximum of the left
  // and the right predecessor
  // the "top" of the triangle and points on the edges are
  // special cases that have to be treated seperately
  vector<vector<int> > maxPath;
  for (int i = 0; i < data.size(); i++) {
    vector<int> tmp;
    // top
    if (i == 0) {
      tmp.push_back(data.at(i).at(0));
    }
    else {
      for (int j = 0; j < data.at(i).size(); j++) {
	// left edge
	if (j == 0) {
	  int add = maxPath.at(i - 1).at(0) + data.at(i).at(j);
	  tmp.push_back(add);
	}
	// right edge
	else if (j == data.at(i).size() - 1) {
	  int add = maxPath.at(i - 1).at(j - 1) + data.at(i).at(j);
	  tmp.push_back(add);
	}
	// general case
	else {
	  int add = data.at(i).at(j) + max(maxPath.at(i-1).at(j-1), maxPath.at(i-1).at(j));
	  tmp.push_back(add);
	}
      }
    }
    maxPath.push_back(tmp);
  }
  int maxSum = 0;
  int rows = maxPath.size();
  for (int i = 0; i < maxPath.at(rows - 1).size(); i++) {
    if (maxPath.at(rows - 1).at(i) > maxSum)
      maxSum = maxPath.at(rows - 1).at(i);
  }
  cout << maxSum << "\n";
  return 0;
}
