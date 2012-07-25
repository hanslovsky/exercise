#ifndef PARSER_HXX
#define PARSER_HXX

#include <vector>
#include <string>
#include <boost/any.hpp>
  

class Parser {
private:
  std::vector<boost::any> options_;
  std::vector<const char*> descriptions_;
  std::vector<const char*> names_;
  std::vector<const char*> shorts_;
  std::vector<bool> required_;
  std::vector<bool> set_;
  int argc_;
  std::vector<const char*> argv_;
  char* name_;

public:
  Parser(int argc, char *argv[]);
  ~Parser();
  void addOption(boost::any option, const char* description,
		 const char* names, const char* shorts, bool required);
  int parseOptions();
  bool checkValid();
  void printHelp();
  boost::any getOptionValue(const char* names);
};


#endif
