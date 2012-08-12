#include <img2ascii.hxx>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  img2ascii a("bla.jpg");
  a.writeToFile("out.txt");
  return 0;
}
