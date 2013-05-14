// stl
#include <vector>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>
#include <ostream>

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
    os << color.term_color_.c_str();
    return os;
  }


  ////
  //// AveragingStrategyMean
  ////
  ImgColorType AveragingStrategyMean::operator()(vigra::MultiArrayView<3, uint> patch) const {
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
  ImgColorType AveragingStrategyMedian::operator()(vigra::MultiArrayView<3, uint> patch) const {
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
  TermColorType ColorMatchStrategyRGB::operator()(ImgColorType color) const {
    return TermColorType();
  }


  ////
  //// ColorMatchStrategyHSV
  ////
  TermColorType ColorMatchStrategyHSV::operator()(ImgColorType color) const {
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


  ////
  //// OptionClass
  ////
  PatchArray2DPtr PatchArray2DFactory(vigra::MultiArrayView<3, uint> image, OptionClass options) {
    uint Y = image.shape()[0];
    uint X = image.shape()[1];
    uint patch_width = std::min(X/options.n_chars_per_column_, X);
    uint patch_height = std::min(static_cast<uint>(options.aspect_ratio_*X), Y);
    PatchArray2DPtr res(new PatchArray2D);
    for (int x = 0; x < X; x += patch_width) {
      res->patches_.push_back(std::vector<ImagePatch>());
      uint delta_x = std::min(patch_width, X - x);
      ImgColorType previous_color(vigra::TinyVector<uint, 3>(257, 257, 257));
      for (int y = 0; y < Y; y += patch_height) {
        uint delta_y = std::min(patch_height, Y - y);
        ImagePatch patch(image.subarray(vigra::TinyVector<uint, 3>(y,x,0),
                                        vigra::TinyVector<uint,3>(y+delta_y, x+delta_x, 3)),
                         previous_color);
        patch.calculate_current_color(*options.averaging_strategy_);
        previous_color = patch.get_current_color();
      }
    }
    return res;
  }


  ////
  //// ImagePatch
  ////
  void ImagePatch::calculate_current_color(const AveragingStrategyBase& strategy) {
    current_color_ = strategy(patch_);
    color_changed_ = !(previous_color_ == current_color_);
  }

  void ImagePatch::calculate_term_color(const ColorMatchStrategyBase& strategy) {
    term_color_ = strategy(current_color_);
  }

  bool ImagePatch::get_color_changed() const {
    return color_changed_;
  }

  ImgColorType ImagePatch::get_previous_color() const {
    return previous_color_;
  }

  ImgColorType ImagePatch::get_current_color() const {
    return current_color_;
  }

  TermColorType ImagePatch::get_term_color() const {
    return term_color_;
  }

  std::ostream& operator<<(std::ostream& os, const ImagePatch& patch) {
    os << patch.term_color_;
    return os;
  }


  ////
  //// PatchArray2D
  ////
  std::ostream& operator<<(std::ostream& os, const PatchArray2D& patch_array) {
    std::vector<std::vector<ImagePatch> >::const_iterator it_2d;
    std::vector<ImagePatch>::const_iterator it_1d;
    for (it_2d = patch_array.patches_.begin(); it_2d != patch_array.patches_.end(); ++it_2d) {
      for (it_1d = it_2d->begin(); it_1d != it_2d->end(); ++it_1d) {
        ImagePatch p = *it_1d;
        os << p;
      }
      os << "\n";
    }
    os << "\b";
    return os;
  }
  


}





