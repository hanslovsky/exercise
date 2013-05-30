#ifndef OPTIONS_FROM_PARSE_HXX
#define OPTIONS_FROM_PARSE_HXX

// boost
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

// stl
#include <string>

// own
#include "img2term/img2term.hxx"


namespace po = boost::program_options; 


class OptionBuilder {
private:
  const po::variables_map& vm_;

  int n_chars_per_line();
  img2term::ColorMatchStrategyPtr color_match_strategy();
  img2term::CharVec characters();
  img2term::CharDrawerStrategyPtr char_drawer_strategy();
  img2term::AveragingStrategyPtr averaging_strategy();
  double get_ratio();

  int get_option(const std::string& option, std::string& value);

  OptionBuilder();
public:
  OptionBuilder(const po::variables_map& vm) : vm_(vm) {}
  boost::shared_ptr<img2term::OptionClass> build();
};


class ParserException : public std::exception {
private:
  std::string msg_;
public:
  ParserException(std::string msg) : msg_(msg) {}
  ~ParserException() throw() {}
  const char* what() {return msg_.c_str();}
};
  

#endif /* OPTIONS_FROM_PARSE_HXX */
