#ifndef IMG2ASCII_HXX
#define IMG2ASCII_HXX

#include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>

class img2ascii {
  vigra::BImage img_;
public:
  img2ascii(const char* imgPath);
  img2ascii(vigra::BImage& img);
};

vigra::BImage rgb2gs(const vigra::BRGBImage& img);


#endif
