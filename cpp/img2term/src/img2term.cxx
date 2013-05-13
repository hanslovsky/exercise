// stl
#include <vector>
#include <map>
#include <string>

// boost
#include <boost/shared_ptr.hpp>

// vigra
#include <vigra/tinyvector.hxx>
#include <vigra/multi_array.hxx>

// own
#include "img2term/img2term.hxx"



namespace img2term {

  /* PatchArray2DPtr PatchArray2DFactory(vigra::MultiArrayView<3, uint> image, OptionClass options) {
    return PatchArray2DPtr(new PatchArray2D);
  } */

  TermColorType ColorMatchStrategyRGB::operator()(ImgColorType color) {
    return TermColorType();
  }
}


