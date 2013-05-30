// stl
#include <vector>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>
#include <ostream>
#include <iostream>

// boost
#include <boost/shared_ptr.hpp>

// vigra
#include <vigra/tinyvector.hxx>
#include <vigra/multi_array.hxx>

// own
#include "img2term/img2term.hxx"
#include "img2term/term_colors.hxx"



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

  uint ImgColorType::to_grayscale() const {
    return (RGB_[0] + RGB_[1] + RGB_[2])/3;
  }

  vigra::TinyVector<double, 3> ImgColorType::to_HSV() const {
    const double R = RGB_[0];
    const double G = RGB_[1];
    const double B = RGB_[2];
    const double max = std::max(R, std::max(G, B));
    const double min = std::min(R, std::min(G, B));
    const double range = max - min;
    vigra::TinyVector<double, 3> res;

    // H:
    if (max == min) {
      res[0] = 0;
    } else if(max == R) {
      res[0] = 60*((G-B)/range);
    } else if(max == G) {
      res[0] = 60*(2 + (B-R)/range);
    } else {
      res[0] = 60*(4 + (R-G)/range);
    }

    // S:
    if (max == 0) {
      res[1] = 0;
    } else {
      res[1] = range/max;
    }

    // V:
    res[2] = max;
    
    return res;
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
    os << color.term_color_;
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
  /* TermColorType ColorMatchStrategyRGB::operator()(ImgColorType color, bool color_changed) const {
    return TermColorType("NEEDS TO BE IMPLEMENTED!");
    } */


  ////
  //// ColorMatchStrategyHSV
  ////
  /* TermColorType ColorMatchStrategyHSV::operator()(ImgColorType color, bool color_changed) const {
    return TermColorType("NEEDS TO BE IMPLEMENTED!");
    } */


  ////
  //// ColorMatchStrategyASCII
  ////
  TermColorType ColorMatchStrategyASCII::operator()(ImgColorType color, bool) const {
    uint index = color.to_grayscale()/256.0*dictionary_.size();
    assert(index < dictionary_.size());
    char tmp[2] = {dictionary_[index], '\0'};
    return TermColorType(std::string(tmp));
  }


  TermColorType ColorMatchStrategyDistance::operator()(ImgColorType color, bool color_changed) const {
    if (color_changed) {
      uint argmin = 0;
      double min = std::numeric_limits<double>::max();
      uint* c_ptr = COLOR_ARR_256;
      double curr_dist;
      for (uint index = 0; c_ptr != COLOR_ARR_256 + 768; ++index, c_ptr+=3) {
        ImgColorType comp_color(vigra::TinyVector<uint, 3>(*(c_ptr),
                                                           *(c_ptr+1),
                                                           *(c_ptr+2)
                                                           ));
        curr_dist = (*distance_)(color, comp_color);
        if (curr_dist < min) {
          min = curr_dist;
          argmin = index;
        }
      }
      std::string argmin_string = std::to_string(argmin);
      return TermColorType("\033[38;05;" +
                           argmin_string +
                           "m\033[48;05;" +
                           argmin_string + "m");
    } else {
      return TermColorType("");
    }
  }
    


  ////
  //// CharDrawerStrategySingleChar
  ////
  char CharDrawerStrategySingleChar::operator()(const CharVec& char_list) {
    return char_list[0];
  }


  ////
  //// CharDrawerStrategyASCII
  ////
  char CharDrawerStrategyASCII::operator()(const CharVec&) {
    return '\0';
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
  //// DistanceStrategyHSV
  ////
  double DistanceStrategyHSV::operator()(ImgColorType c1, ImgColorType c2) {
    const vigra::TinyVector<double, 3> HSV_1 = c1.to_HSV();
    const vigra::TinyVector<double, 3> HSV_2 = c2.to_HSV();
    double squared_sum = (HSV_1[0] - HSV_2[0])*(HSV_1[0] - HSV_2[0]);
    for (uint i = 1; i < 3; ++i) {
      squared_sum += param_*(HSV_1[i] - HSV_2[i])*(HSV_1[i] - HSV_2[i]);
    }
    return squared_sum;
  }

  ////
  //// OptionClass
  ////
  CharDrawerStrategyPtr OptionClass::get_char_drawer_strategy() const {
    return char_drawer_strategy_;
  }


  char OptionClass::print_char() const {
    char tmp = (*char_drawer_strategy_)(char_list_);
    return tmp;
  }


  PatchArray2DPtr PatchArray2DFactory(vigra::MultiArrayView<3, uint> image, OptionClass options) {
    uint Y = image.shape()[1];
    uint X = image.shape()[0];
    uint n_chars = std::min(options.n_chars_per_column_, X);
    uint patch_width = X/n_chars+1;
    uint patch_height = std::min(static_cast<uint>(options.aspect_ratio_*patch_width), Y);
    PatchArray2DPtr res(new PatchArray2D(options));
    for (uint y = 0; y < Y; y += patch_height) {
      res->patches_.push_back(std::vector<ImagePatch>());
      uint delta_y = std::min(patch_height, Y - y);
      ImgColorType previous_color(vigra::TinyVector<uint, 3>(257, 257, 257));
      std::vector<ImagePatch>& patch_vector = *(res->patches_.end()-1);
      for (uint x = 0; x < X; x += patch_width) {
        uint delta_x = std::min(patch_width, X - x);
        patch_vector.push_back(ImagePatch(image.subarray(vigra::TinyVector<uint, 3>(x,y,0),
                                                         vigra::TinyVector<uint,3>(x+delta_x, y+delta_y, 3)),
                                          previous_color)
                               );
        ImagePatch& patch = *(patch_vector.end()-1);
        patch.calculate_current_color(*options.averaging_strategy_);
        patch.term_color_ = (*(options.color_match_strategy_))(patch.current_color_, patch.get_color_changed());
        previous_color = patch.current_color_;
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
    term_color_ = strategy(current_color_, color_changed_);
  }

  bool ImagePatch::get_color_changed() const {
    return color_changed_;
  }

  void ImagePatch::set_term_color(TermColorType color) {
    term_color_ = color;
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
  char PatchArray2D::draw_char() const {
    return (*(options_.char_drawer_strategy_))(options_.char_list_);
  }

  std::ostream& operator<<(std::ostream& os, const PatchArray2D& patch_array) {
    std::vector<std::vector<ImagePatch> >::const_iterator it_2d;
    std::vector<ImagePatch>::const_iterator it_1d;
    for (it_2d = patch_array.patches_.begin(); it_2d != patch_array.patches_.end(); ++it_2d) {
      for (it_1d = it_2d->begin(); it_1d != it_2d->end(); ++it_1d) {
        
        os << *it_1d << patch_array.options_.print_char();
      }
      os << "\033[0m\n";
    }
    os << "\b";
    os << "\033[0m";
    return os;
  }
  


}





