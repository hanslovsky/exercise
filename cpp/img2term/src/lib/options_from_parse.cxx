// boost
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>
#include <boost/any.hpp>

// stl
#include <string>
#include <vector>

// own
// #include "img2term/term_colors.hxx"
#include "img2term/options_from_parse.hxx"


////
//// OptionBuilder
////
int OptionBuilder::n_chars_per_line() {
  std::string columns;
  if (get_option("columns", columns)) {
    try {
      return std::stoi(columns);
    } catch(std::invalid_argument) {
      throw ParserException("Could not convert to int: " + columns);
    }
  } else {
    throw ParserException("Number of columns not specified!");
  }
}


img2term::ColorMatchStrategyPtr OptionBuilder::color_match_strategy() {
  std::string strategy;
  if (get_option("matching", strategy)) {
    if (strategy.compare("ascii") == 0) {
      char SYMBOL_ARRAY[] = {' ', '.', ',', ':', ';', '+', '*', '&', '#', '%', '@'};
      uint N_SYMBOLS = sizeof(SYMBOL_ARRAY)/sizeof(char);
      std::vector<char> symbols(SYMBOL_ARRAY, SYMBOL_ARRAY + N_SYMBOLS);
      return img2term::ColorMatchStrategyPtr(new img2term::ColorMatchStrategyASCII(symbols));
    } else if(strategy.compare("color") == 0) {
      return img2term::ColorMatchStrategyPtr(new img2term::ColorMatchStrategyDistance);
    } else {
      throw ParserException("Matching Strategy does not match any existing: " + strategy);
    }
  } else {
    throw ParserException("Matching Strategy not specified!");
  }
}


img2term::CharVec OptionBuilder::characters() {
  return img2term::CharVec(1, '#');
}


img2term::CharDrawerStrategyPtr OptionBuilder::char_drawer_strategy() {
  std::string strategy;
  if (get_option("drawer", strategy)) {
    if (strategy.compare("ascii") == 0) {
      return img2term::CharDrawerStrategyPtr(new img2term::CharDrawerStrategyASCII);
    } else if (strategy.compare("single") == 0) {
      return img2term::CharDrawerStrategyPtr(new img2term::CharDrawerStrategySingleChar);
    } else {
      throw ParserException("Char Drawing Strategy does not match any existing: " + strategy);
    }
  } else {
    throw ParserException("Char Drawing Strategy not specified!");
  }
}


img2term::AveragingStrategyPtr OptionBuilder::averaging_strategy() {
  std::string strategy;
  if (get_option("averaging", strategy)) {
    if (strategy.compare("mean") == 0) {
      return img2term::AveragingStrategyPtr(new img2term::AveragingStrategyMean);
    } else if(strategy.compare("median") == 0) {
      return img2term::AveragingStrategyPtr(new img2term::AveragingStrategyMedian);
    } else {
      throw ParserException("Averaging Strategy does not match any exisiting: " + strategy);
    }
  } else {
    throw ParserException("Averaging Strategy not specified!");
  }
}


double OptionBuilder::get_ratio() {
  std::string ratio;
  if (get_option("ratio", ratio)) {
    try {
      return std::stod(ratio);
    } catch(std::invalid_argument) {
      throw ParserException("Could not convert to double: " + ratio);
    }
  } else {
    throw ParserException("Ratio not specified!");
  }
}    


int OptionBuilder::get_option(const std::string& option, std::string& value) {
  int count = vm_.count(option);
  if (count) {
    value = vm_[option].as<std::string>();
  }
  return count;
}


boost::shared_ptr<img2term::OptionClass> OptionBuilder::build() {
  boost::shared_ptr<img2term::OptionClass> option_ptr(
                                                      new img2term::OptionClass(n_chars_per_line(),
                                                                                color_match_strategy(),
                                                                                characters(),
                                                                                char_drawer_strategy(),
                                                                                averaging_strategy(),
                                                                                get_ratio()
                                                                                )
                                                      );
  return option_ptr;
}
