#include <img2ascii.hxx>
#include <fstream>
#include <iostream>


img2ascii::img2ascii(const char* imgPath) {
  char symbols[] = SYMBOLS;
  symbols_ = std::vector<char>(symbols, symbols + sizeof(symbols)/sizeof(char));
  shades_ = symbols_.size();
  vigra::ImageImportInfo info(imgPath);
  if (info.isGrayscale()) {
    img_ = vigra::BImage(info.width(), info.height());
    importImage(info, destImage(img_));
  }
  else {
    RGBimg_ = new vigra::BRGBImage(info.width(), info.height());
    importImage(info, destImage(*RGBimg_));
    img_ = rgb2gs(*RGBimg_);
  }
}

img2ascii::~img2ascii() {
  delete RGBimg_;
}

void img2ascii::writeToFile(const char* filePath) {
  std::fstream f;
  f.open(filePath, std::fstream::out | std::fstream::trunc);
  for(int y = 0; y < img_.height() - PATCHHEIGHT; y += PATCHHEIGHT) {
    for(int x = 0; x < img_.width() - PATCHWIDTH; x += PATCHWIDTH) {
      double score = 0;
      for (int patchY = y; patchY < y + PATCHHEIGHT; patchY++) {
	for (int patchX = x; patchX < x + PATCHWIDTH; patchX++) {
	  score += 255 - (int)img_(patchX, patchY);
	}
      }
      score = (shades_ - 1)*score*1.0/(255*PATCHHEIGHT*PATCHWIDTH);
      f << symbols_.at(score);
    }
    f << '\n';
  }
  f.close();
}
  

vigra::BImage rgb2gs(vigra::BRGBImage& RGBImg) {
  vigra::BImage GSImage(RGBImg.width(), RGBImg.height());
  vigra::BRGBImage::Iterator sy = RGBImg.upperLeft();
  vigra::BRGBImage::Iterator send = RGBImg.lowerRight();
  vigra::BImage::Iterator dy = GSImage.upperLeft();
  for (; sy.y != send.y; ++sy.y, ++dy.y) {
    vigra::BRGBImage::Iterator sx = sy;
    vigra::BImage::Iterator dx = dy;
    for (; sx.x != send.x; ++sx.x, ++dx.x) {
      *dx = 1.0/3*(sx->red() + sx->green() + sx->blue());
    }
  }
  return GSImage;
}
