#include <iostream>
#include <parser.hxx>
#include <boost/any.hpp>
#include <string>

Parser::Parser(int argc, char** argv) :
  argc_(argc), name_(argv[0]) {
  for (int i = 1; i < argc_; i++) {
    argv_.push_back(argv[i]);
  }
  std::string hlp = "";
  options_.push_back(hlp);
  descriptions_.push_back("Show this help message");
  names_.push_back("none");
  shorts_.push_back("--help");
  required_.push_back(0);
  set_.push_back(0);
}

Parser::~Parser() {
  std::cout << std::endl;
}

void Parser::addOption(boost::any option, const char* description,
		       const char* names, const char* shorts, bool required) {
  options_.push_back(option);
  descriptions_.push_back(description);
  names_.push_back(names);
  shorts_.push_back(shorts);
  required_.push_back(required);
  set_.push_back(0);
}

int Parser::parseOptions() {
  for (int i = 0; i < argc_ - 1; i++) {
    const char* arg = argv_.at(i);
    if (!strcmp(arg, "--help")) {
      printHelp();
      return 1;
    }
  }
  return 0;
}

bool Parser::checkValid() {
  for (uint i = 0; i < required_.size(); i++) {
    if(required_.at(i) == 1 && set_.at(i) == 0)
      return 0;
  }
  return 1;
}

void Parser::printHelp() {
  std::cout << name_ << ":\n\noptions:\n\n";
  for (uint i = 0; i < shorts_.size(); i++) {
    std::cout << shorts_.at(i) << " <" << names_.at(i) << ">\n";
    std::cout << "\t" << descriptions_.at(i) << "\n";
  }
}
