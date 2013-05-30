#ifndef IMG_2_TERM_HXX
#define IMG_2_TERM_HXX

// stl
#include <vector>
#include <map>
#include <string>
#include <ostream>

// boost
#include <boost/shared_ptr.hpp>

// vigra
#include <vigra/tinyvector.hxx>
#include <vigra/multi_array.hxx>




namespace img2term {

  // classes


  class ImgColorType;


  class TermColorType;


  class HSVColorType;


  class AveragingStrategyBase;


  class AveragingStrategyMean;


  class AveragingStrategyMedian;
  
  
  class ColorMatchStrategyBase;


  class ColorMatchStrategyRGB;


  class ColorMatchStrategyHSV;


  class ColorMatchStrategyASCII;


  class ColorMatchStrategyDistance;


  class CharDrawerStrategyBase;


  class CharDrawerStrategySingleChar;


  class CharDrawerStrategyASCII;


  class DistanceStrategyBase;


  class DistanceStrategyRGB;


  class DistanceStrategyHSV;

  
  class OptionClass;


  class ImagePatch;


  class PatchArray2D;


  // typedefs
  
  // typedef std::vector<std::vector<ImagePatch> > PatchArray2D;

  
  typedef boost::shared_ptr<PatchArray2D> PatchArray2DPtr;


  typedef unsigned int uint;


  typedef std::vector<char> CharVec;


  typedef std::map<ImgColorType, TermColorType> ColorDict;


  typedef boost::shared_ptr<AveragingStrategyBase> AveragingStrategyPtr;

  
  typedef boost::shared_ptr<ColorMatchStrategyBase> ColorMatchStrategyPtr;


  typedef boost::shared_ptr<CharDrawerStrategyBase> CharDrawerStrategyPtr;


  typedef boost::shared_ptr<DistanceStrategyBase> DistanceStrategyPtr;



  
  
  // functions
  
  PatchArray2DPtr PatchArray2DFactory(vigra::MultiArrayView<3, uint> image, OptionClass options);


  /*std::ostream& operator<<(std::ostream& os, TermColorType& color);

  
  std::ostream& operator<<(std::ostream& os, ImagePatch& patch);

  
  std::ostream& operator<<(std::ostream& os, PatchArray2D& patch_array);*/



  class ImgColorType {
  private:
    vigra::TinyVector<uint, 3> RGB_;
  public:
    ImgColorType() :
      RGB_(vigra::TinyVector<uint, 3>(0, 0, 0))
    {}
    ImgColorType(vigra::TinyVector<uint, 3> RGB) :
      RGB_(RGB)
    {}
    const vigra::TinyVector<uint, 3>& get_RGB();
    uint to_grayscale() const;
    vigra::TinyVector<double, 3> to_HSV() const;
    friend bool operator==(const ImgColorType& c1, const ImgColorType& c2);
  };


  class TermColorType {
  private:
    std::string term_color_;
  public:
    TermColorType() :
      term_color_("")
    {}
    TermColorType(std::string term_color) :
      term_color_(term_color)
    {}
    std::string get_term_color();
    friend bool operator==(const TermColorType& c1, const TermColorType& c2);
    friend std::ostream& operator<<(std::ostream& os, const TermColorType& color);
  };


  class AveragingStrategyBase {
  private:
  public:
    virtual ImgColorType operator()(vigra::MultiArrayView<3, uint> patch) const = 0;
  };


  class AveragingStrategyMean : public AveragingStrategyBase {
  private:
  public:
    virtual ImgColorType operator()(vigra::MultiArrayView<3, uint> patch) const;
  };


  class AveragingStrategyMedian : public AveragingStrategyBase {
  private:
  public:
    virtual ImgColorType operator()(vigra::MultiArrayView<3, uint> patch) const;
  };


  class DistanceStrategyBase {
  private:
  public:
    virtual double operator()(ImgColorType c1, ImgColorType c2) = 0;
  };

  
  class DistanceStrategyRGB : public DistanceStrategyBase {
  private:
  public:
    virtual double operator()(ImgColorType c1, ImgColorType c2);
  };


  class DistanceStrategyHSV : public DistanceStrategyBase {
  private:
    double param_;
  public:
    DistanceStrategyHSV() :
      param_(1.0)
    {}
    DistanceStrategyHSV(double param) :
      param_(param)
    {}
    virtual double operator()(ImgColorType c1, ImgColorType c2);
  };


  class ColorMatchStrategyBase {
    // ColorDict dictionary_;
  public:
    virtual TermColorType operator()(ImgColorType color, bool color_changed) const = 0;
  };


  class ColorMatchStrategyRGB : public ColorMatchStrategyBase {
  private:
    // ColorMatchStrategyRGB();
  public:
    // ColorMatchStrategyRGB(ColorDict dictionary) :
    // dictionary_(dictionary)
    // {}
    virtual TermColorType operator()(ImgColorType color, bool color_changed) const;
  };


  class ColorMatchStrategyHSV : public ColorMatchStrategyBase {
  private:
    // ColorMatchStrategyHSV();
  public:
    //ColorMatchStrategyHSV(ColorDict dictionary) :
    // dictionary_(dictionary)
    // {}
    virtual TermColorType operator()(ImgColorType color, bool color_changed) const;
  };


  class ColorMatchStrategyASCII : public ColorMatchStrategyBase {
  private:
    std::vector<char> dictionary_;
  public:
    ColorMatchStrategyASCII() :
      dictionary_(0)
    {dictionary_.push_back('.'); dictionary_.push_back('#');}
    ColorMatchStrategyASCII(std::vector<char> dictionary) :
      dictionary_(dictionary)
    {}
    virtual TermColorType operator()(ImgColorType color, bool) const;
  };


  class ColorMatchStrategyDistance : public ColorMatchStrategyBase {
  private:
    DistanceStrategyPtr distance_;
  public:
    ColorMatchStrategyDistance() :
      distance_(DistanceStrategyPtr(new DistanceStrategyRGB))
    {}
    ColorMatchStrategyDistance(DistanceStrategyPtr distance) :
      distance_(distance)
    {}
    virtual TermColorType operator()(ImgColorType color, bool color_changed) const;
  };

  class CharDrawerStrategyBase {
  private:
  public:
    virtual char operator()(const CharVec& char_list) = 0;
  };


  class CharDrawerStrategySingleChar : public CharDrawerStrategyBase {
  private:
  public:
    virtual char operator()(const CharVec& char_list);
  };


  class CharDrawerStrategyASCII : public CharDrawerStrategyBase {
  private:
  public:
    virtual char operator()(const CharVec& char_list);
  };



  class OptionClass {
  private:
    uint n_chars_per_column_;
    ColorMatchStrategyPtr color_match_strategy_;
    CharVec char_list_;
    CharDrawerStrategyPtr char_drawer_strategy_;
    AveragingStrategyPtr averaging_strategy_;
    double aspect_ratio_;
  public:
    OptionClass() :
      n_chars_per_column_(80),
      color_match_strategy_(ColorMatchStrategyPtr(new ColorMatchStrategyASCII)),
      char_list_(CharVec(1, '#')),
      char_drawer_strategy_(CharDrawerStrategyPtr(new CharDrawerStrategySingleChar)),
      averaging_strategy_(AveragingStrategyPtr(new AveragingStrategyMean)),
      aspect_ratio_(2.0)
    {}
    
    OptionClass(uint n_chars_per_column,
                ColorMatchStrategyPtr color_match_strategy,
                CharVec char_list,
                CharDrawerStrategyPtr char_drawer_strategy,
                AveragingStrategyPtr averaging_strategy,
                double aspect_ratio) :
      n_chars_per_column_(n_chars_per_column),
      color_match_strategy_(color_match_strategy),
      char_list_(char_list),
      char_drawer_strategy_(char_drawer_strategy),
      averaging_strategy_(averaging_strategy),
      aspect_ratio_(aspect_ratio)
    {}

    CharDrawerStrategyPtr get_char_drawer_strategy() const;
    char print_char() const;

    friend PatchArray2DPtr PatchArray2DFactory(vigra::MultiArrayView<3, uint> image, OptionClass options);
    friend class PatchArray2D;
  };


  class ImagePatch {
  private:
    vigra::MultiArrayView<3, uint> patch_;
    ImgColorType previous_color_;
    bool color_changed_;
    
    ImgColorType current_color_;
    TermColorType term_color_;
  public:
    ImagePatch() :
      patch_(vigra::MultiArrayView<3, uint>()),
      previous_color_(ImgColorType()),
      color_changed_(0)
    {}
    ImagePatch(vigra::MultiArrayView<3, uint> patch,
               ImgColorType previous_color) :
      patch_(patch),
      previous_color_(previous_color),
      color_changed_(0)
    {}
    void calculate_current_color(const AveragingStrategyBase& strategy);
    void calculate_term_color(const ColorMatchStrategyBase& strategy);

    bool get_color_changed() const;

    void set_term_color(TermColorType color);

    ImgColorType get_previous_color() const;
    ImgColorType get_current_color() const;
    TermColorType get_term_color() const;

    friend std::ostream& operator<<(std::ostream& os, const ImagePatch& patch);
    friend PatchArray2DPtr PatchArray2DFactory(vigra::MultiArrayView<3, uint> image, OptionClass options);
  };


  class PatchArray2D {
  private:
    OptionClass options_;
  public:
    typedef std::vector<std::vector<ImagePatch> > Patches;
    Patches patches_;
    PatchArray2D() :
      options_(OptionClass()),
      patches_(0)
    {}
    PatchArray2D(const OptionClass& options) :
      options_(options),
      patches_(0)
    {}

    char draw_char() const;
    
    friend std::ostream& operator<<(std::ostream& os, const PatchArray2D& patch_array);
  };


  

}








#endif /* IMG_2_TERM_HXX */
