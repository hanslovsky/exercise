#include <img2ascii.hxx>
#include <iostream>

img2ascii::img2ascii(const char* imgPath) {
  vigra::ImageImportInfo info(imgPath);
  if (info.isGrayscale()) {
    img_ = vigra::BImage(info.width(), info.height());
    importImage(info, destImage(img_));
  }
  else {
    vigra::BRGBImage img(info.width(), info.height());
    importImage(info, destImage(img));
    img_ = rgb2gs(img);
  }
  exportImage(srcImageRange(img_), vigra::ImageExportInfo("test.png"));
}

vigra::BImage rgb2gs(vigra::BRGBImage RGBImg) {
  vigra::BImage GSImage(RGBImg.width(), RGBImg.height());
  vigra::BRGBImage::Iterator sy = RGBImg.upperLeft();
  vigra::BRGBImage::Iterator send = RGBImg.lowerRight();
  vigra::BImage::Iterator dy = GSImage.upperLeft();
  for (; sy.y != send.y; ++sy.y, ++dy.y) {
    vigra::BRGBImage::Iterator sx = sy;
    vigra::BImage::Iterator dx = dy;
    for (; sx.x != send.x; ++sx.x, ++dx.x) {
      *dx = 1/3*(sx->red() + sx->green() + sx->blue());
    }
  }
  return GSImage;
}
