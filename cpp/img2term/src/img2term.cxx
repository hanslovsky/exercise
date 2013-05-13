// stl
#include <vector>
#include <map>
#include <string>
#include <numeric>

// boost
#include <boost/shared_ptr.hpp>

// vigra
#include <vigra/tinyvector.hxx>
#include <vigra/multi_array.hxx>

// own
#include "img2term/img2term.hxx"



namespace img2term {


  ////
  //// ImgColorType
  ////
  const vigra::TinyVector<uint, 3>& ImgColorType::get_RGB() {
    return RGB_;
  }

  bool operator==(const ImgColorType& c1, const ImgColorType& c2) {
    return c1.RGB_[0] == c2.RGB_[0] &&
      c1.RGB_[1] == c2.RGB_[1] &&
      c1.RGB_[2] == c2.RGB_[2];
  }


  ////
  //// TermColorType
  ////
  std::string TermColorType::get_term_color() {
    return term_color_;
  }

  bool operator==(const TermColorType& c1, const TermColorType& c2) {
    return c1.term_color_.compare(c2.term_color_) == 0;
  }

  std::ostream& operator<<(std::ostream& os, const TermColorType& color) {
    return os << color.term_color_;
  }


  ////
  //// AveragingStrategyMean
  ////
  ImgColorType AveragingStrategyMean::operator()(vigra::MultiArrayView<3, uint> patch) {
    uint patch_size = patch.shape()[0]*patch.shape()[1];
    vigra::TinyVector<uint, 3> res;
    for(uint channel = 0; channel < 3; ++channel) {
      vigra::MultiArrayView<2, uint, vigra::StridedArrayTag> sub_patch = patch.bindAt(2, channel);
      res[channel] = std::accumulate(sub_patch.begin(), sub_patch.end(), 0)/patch_size;
    }
    return ImgColorType(res);
  }


  ////
  //// AveragingStrategyMedian
  ////
  ImgColorType AveragingStrategyMedian::operator()(vigra::MultiArrayView<3, uint> patch) {
    uint patch_size = patch.shape()[0]*patch.shape()[1];
    vigra::TinyVector<uint, 3> res;
    for(uint channel = 0; channel < 3; ++channel) {
      vigra::MultiArrayView<2, uint, vigra::StridedArrayTag> sub_patch = patch.bindAt(2, channel);
      std::vector<uint> value_list(sub_patch.begin(), sub_patch.end());
      std::sort(value_list.begin(), value_list.end());
      res[channel] = value_list[patch_size/2];
    }
    return ImgColorType(res);
  }


  ////
  //// ColorMatchStrategyRGB
  ////
  TermColorType ColorMatchStrategyRGB::operator()(ImgColorType color) {
    return TermColorType();
  }


  ////
  //// ColorMatchStrategyHSV
  ////
  TermColorType ColorMatchStrategyHSV::operator()(ImgColorType color) {
    return TermColorType();
  }


  ////
  //// CharDrawerStrategySingleChar
  ////
  char CharDrawerStrategySingleChar::operator()(const CharVec& char_list) {
    return char_list[0];
  }


  ////
  //// DistanceStrategyRGB
  ////
  double DistanceStrategyRGB::operator()(ImgColorType c1, ImgColorType c2) {
    const vigra::TinyVector<uint, 3>& RGB_1 = c1.get_RGB();
    const vigra::TinyVector<uint, 3>& RGB_2 = c2.get_RGB();
    double squared_sum = 0.0;
    for (uint i = 0; i < RGB_1.size(); ++i) {
      squared_sum += (RGB_1[i] - RGB_2[i])*(RGB_1[i] - RGB_2[i]);
    }
    return squared_sum;
  }
}


