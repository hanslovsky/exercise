#ifndef PNGIMAGE_HXX
#define PNGIMAGE_HXX

#include <iostream>
#include <png.h>

typedef char GrayValue;

class PNGImage {
 private:
  struct info {
    uint sizeX_;
    uint sizeY_;
    uint colorType_;
    uint bitDepth_;
    uint channels_;
  };
  info metaData_;
  GrayValue *bitMap_;
 public:
  PNGImage() : bitMap_(0)
  {}
  ~PNGImage();
  
  void setMetaData(uint sizeX, uint sizeY, uint colorType,
		   uint bitDepth, uint channels);
  void setSizeX(uint sizeX);
  void setSizeY(uint sizeY);
  void setColorType(uint colorType);
  void setBitDepth(uint bitDepth);
  void setChannels(uint channels);
  void pointBitMap(GrayValue *bitMap);

  uint getSizeX();
  uint getSizeY();
  uint getColorType();
  uint getBitDepth();
  uint getChannels();

  // temporary
  void printPixels();
  
};

bool isPNG(std::istream &s);
bool readPNG(std::istream &s, PNGImage &img);
bool readPNG(const char *path, PNGImage &img);
void readData(png_structp, png_bytep, png_size_t);


#endif
