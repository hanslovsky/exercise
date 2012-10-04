#ifndef IMG2ASCII_HXX
#define IMG2ASCII_HXX

#include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>
#include <vector>

#ifndef SYMBOLS
#define SYMBOLS {' ', '.', ',', ':', ';', '+', '*', '&', '#', '%', '@'}
#endif
#define PATCHWIDTH 5
#define PATCHHEIGHT 10


class img2ascii {
  vigra::BImage img_;
  vigra::BRGBImage *RGBimg_;
  std::vector<char> symbols_;
  unsigned int shades_;
public:
  img2ascii(const char* imgPath);
  img2ascii(vigra::BImage& img);
  ~img2ascii();
  void writeToFile(const char* filePath);

  vigra::BImage getImage();
};

vigra::BImage rgb2gs(vigra::BRGBImage& img);


#endif
