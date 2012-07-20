#include <vigra/impex.hxx>

int main() {
  vigra::ImageImportInfo info("herc.jpg");
  if (info.isGrayscale()) {
    vigra::BImage in(info.width(), info.height());
    vigra::importImage(info, destImage(in));
  }
  else {
    vigra::BRGBImage in(info.width(), info.height());
    vigra::BRGBImage out(info.width(), info.height());
    vigra::RGBValue<int> offset(255, 255, 255);
    vigra::importImage(info, destImage(in));
    vigra::BRGBImage::Iterator dy = in.upperLeft();
    vigra::BRGBImage::Iterator end = in.lowerRight();
    vigra::BRGBImage::Iterator oy = out.upperLeft();
    for (; dy.y != end.y && dy.y !=end.y-1; ++dy.y, ++oy.y) {
      vigra::BRGBImage::Iterator dx = dy;
      vigra::BRGBImage::Iterator ox = oy;
      for (; dx.x != end.x; ++dx.x, ++ox.x) {
	vigra::RGBValue<int> pix = *dx;
	*ox = offset - pix;
      }
    }
    vigra::exportImage(vigra::srcImageRange(out), vigra::ImageExportInfo("hercinv.jpg"));
  }
  return 0;
}
