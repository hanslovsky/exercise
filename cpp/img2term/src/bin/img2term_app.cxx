// stl
#include <iostream>
#include <string>
#include <vector>

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/impex.hxx>
#include <vigra/imageinfo.hxx>

// own
#include <img2term/img2term.hxx>


// #define SYMBOLS {'.', ',', ':', ';', '+', '*', '#'}
#define SYMBOLS {' ', '.', ',', ':', ';', '+', '*', '&', '#', '%', '@'}



int main(int argc, char** argv) {
  if (argc != 2) {
    return 1;
  }
  char sym_arr[] = SYMBOLS;
  uint n = sizeof(sym_arr)/sizeof(char);
  std::vector<char> sym(sym_arr, sym_arr+n);
  std::string filename(argv[1]);
  vigra::ImageImportInfo info(filename.c_str());
  vigra::MultiArray<2, vigra::TinyVector<img2term::uint, 3> > src_image(vigra::Shape2(info.width(), info.height()));
  vigra::importImage(info, vigra::destImage(src_image));
  vigra::MultiArray<3, img2term::uint> image(vigra::Shape3(info.width(), info.height(), 3));
  image.copy(src_image.expandElements(2));
  vigra::MultiArrayView<3, img2term::uint> image_view(image);
  vigra::exportImage(vigra::srcImageRange(src_image), vigra::ImageExportInfo("out.png"));
  
  img2term::OptionClass options_1(120,
                                  img2term::ColorMatchStrategyPtr(new img2term::ColorMatchStrategyASCII(sym)),
                                  img2term::CharVec(1, '#'),
                                  img2term::CharDrawerStrategyPtr(new img2term::CharDrawerStrategySingleChar),
                                  img2term::AveragingStrategyPtr(new img2term::AveragingStrategyMean),
                                  2.5);

  img2term::DistanceStrategyPtr distance(new img2term::DistanceStrategyHSV(0.5));
  img2term::OptionClass options_2(120,
                                  img2term::ColorMatchStrategyPtr(new img2term::ColorMatchStrategyDistance(distance)),
                                  img2term::CharVec(1, '#'),
                                  img2term::CharDrawerStrategyPtr(new img2term::CharDrawerStrategySingleChar),
                                  img2term::AveragingStrategyPtr(new img2term::AveragingStrategyMean),
                                  2.5);

  img2term::DistanceStrategyPtr distance_rgb(new img2term::DistanceStrategyRGB);
  img2term::OptionClass options_3(150,
                                  img2term::ColorMatchStrategyPtr(new img2term::ColorMatchStrategyDistance(distance_rgb)),
                                  img2term::CharVec(1, '#'),
                                  img2term::CharDrawerStrategyPtr(new img2term::CharDrawerStrategySingleChar),
                                  img2term::AveragingStrategyPtr(new img2term::AveragingStrategyMean),
                                  2.5);
  
  img2term::PatchArray2DPtr patches = img2term::PatchArray2DFactory(image, options_3);
  std::cout << *patches;
  return 0;
}
