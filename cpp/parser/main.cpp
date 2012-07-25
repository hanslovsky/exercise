#include <iostream>
#include <parser.hxx>

int main(int argc, char** argv) {
  Parser parser(argc, argv);
  parser.addOption(5, "bla\n\tokee", "BLA VALUE", "--bla", 1);
  parser.parseOptions();
  return 0;
}
