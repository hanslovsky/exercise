#include <iostream>
#include "../include/PNGImage.hxx"
#include <png.h>
#include <cmath>

#define PNGSIGSIZE 8
PNGImage::~PNGImage() {
  delete bitMap_;
  bitMap_ = 0;
}

void PNGImage::setMetaData(uint sizeX, uint sizeY, uint colorType,
			   uint bitDepth, uint channels) {
  setSizeX(sizeX);
  setSizeY(sizeY);
  setColorType(colorType);
  setBitDepth(bitDepth);
  setChannels(channels);
}

void PNGImage::setSizeX(uint sizeX) {
  metaData_.sizeX_ = sizeX;
}

void PNGImage::setSizeY(uint sizeY) {
  metaData_.sizeY_ = sizeY;
}

void PNGImage::setColorType(uint colorType) {
  metaData_.colorType_ = colorType;
}

void PNGImage::setBitDepth(uint bitDepth) {
  metaData_.bitDepth_ = bitDepth;
}

void PNGImage::setChannels(uint channels) {
  metaData_.channels_ = channels;
}

void PNGImage::pointBitMap(GrayValue *bitMap) {
  bitMap_ = bitMap;
}

uint PNGImage::getSizeX() {
  return metaData_.sizeX_;
}

uint PNGImage::getSizeY() {
  return metaData_.sizeY_;
}

uint PNGImage::getColorType() {
  return metaData_.colorType_;
}

uint PNGImage::getBitDepth() {
  return metaData_.bitDepth_;
}

uint PNGImage::getChannels() {
  return metaData_.channels_;
}

void PNGImage::printPixels() {
  uint sizeX = getSizeX();
  uint sizeY = getSizeY();
  uint bitDepth = getBitDepth();
  uint channels = getChannels();
  uint stepSize =  bitDepth * channels / 8;
  for (uint y = 0; y < sizeY; y++) {
    for (uint x = 0; x < sizeX*stepSize; x += stepSize) {
      double sum = 0;
      uint idx = y*sizeX + x;
      for (uint c = 0; c < channels; c++) {
	for (uint d = 0; d < bitDepth/8; d ++) {
	  // sum += pow(2, bitDepth/8 - d)*(uint)bitMap_[sizeX*y + x + c + d];
	  uint kk = (uint)bitMap_[idx + c + d];
	  if (kk > 255) {
	    std::cout << "x: " << x/stepSize << ", y: " << y << ", c: " << c;
	    std::cout << ", d: " << d << "  " << kk << std::endl;
	  }
	}
      }
      sum = sum/3;
      // if (sum > 255)
      // std::cout << "x: " << x/stepSize << ", y: " << y << "  " << sum << " " << std::endl;
    }
    std::cout << std::endl;
  }
}







bool isPNG(std::istream &s) {
  png_byte pngSig[PNGSIGSIZE];
  s.read((char*)pngSig, PNGSIGSIZE);
  if (!s.good())
    return false;
  s.seekg(0, std::ios::beg);
  int isPng = png_sig_cmp(pngSig, 0, PNGSIGSIZE);
  return (isPng == 0);
}

bool readPNG(std::istream &s, PNGImage &img) {
  if (!isPNG(s)) {
    std::cerr << "ERROR: File is not a PNG file!" << std::endl;
    return 0;
  }

  png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!pngPtr) {
    std::cerr << "ERROR: Could not initialize png read struct!" << std::endl;
    return 0;
  }

  png_infop infoPtr = png_create_info_struct(pngPtr);
  if (!infoPtr) {
    std::cerr << "ERROR: Could not initizalize png info struct!" << std::endl;
    png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
    return 0;
  }

  png_bytep *rowPtrs = 0;
  char *data = 0;

  if (setjmp(png_jmpbuf(pngPtr))) {
    png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
    if (rowPtrs)
      delete [] rowPtrs;
    if (data)
      delete [] data;
    std::cerr << "ERROR: An error occuredreading the png file!" << std::endl;
    return 0;
  }
  png_set_read_fn(pngPtr, (png_voidp) &s, readData);
  png_read_info(pngPtr, infoPtr);
  png_uint_32 sizeX = png_get_image_width(pngPtr, infoPtr);
  png_uint_32 sizeY = png_get_image_height(pngPtr, infoPtr);
  png_uint_32 colorType = png_get_color_type(pngPtr, infoPtr);
  png_uint_32 bitDepth = png_get_bit_depth(pngPtr, infoPtr);
  png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
  switch (colorType) {
  case PNG_COLOR_TYPE_PALETTE:
    png_set_palette_to_rgb(pngPtr);
    channels = 3;
    break;
  case PNG_COLOR_TYPE_GRAY:
    if (bitDepth < 8)
      png_set_expand_gray_1_2_4_to_8(pngPtr);
    bitDepth = 8;
    break;
  }
  if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(pngPtr);
    channels += 1;
  }
  if (bitDepth == 16)
    png_set_strip_16(pngPtr);

  rowPtrs = new png_bytep[sizeY];
  data = new char[sizeX * sizeY * bitDepth * channels / 8];
  const uint stepLength = sizeX * bitDepth * channels / 8;
  img.setMetaData(sizeX, sizeY, colorType, bitDepth, channels);
  img.pointBitMap(data);
  for (uint i = 0; i < sizeY; i++) {
    png_uint_32 q = i*stepLength;
    std::cout << stepLength << " " << q << std::endl;
    rowPtrs[i] = (png_bytep)data + q;
  }
  png_read_image(pngPtr, rowPtrs);
  data = 0;
  delete data;
  delete[] (png_bytep)rowPtrs;
  png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
  return 1;
}

void readData(png_structp pngPtr, png_bytep data, png_size_t length) {
  png_voidp a = png_get_io_ptr(pngPtr);
  ((std::istream*) a)->read((char*)data, length);
}
