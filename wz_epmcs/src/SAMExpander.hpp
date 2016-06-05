#ifndef CAFE_SAMEXPANDER_HPP__
#define CAFE_SAMEXPANDER_HPP__

namespace sam {
    class SamConsumer;
}

class SAMExpander {
public:
  SAMExpander();
  ~SAMExpander();
  std::string nextFile();
private:
  sam::SamConsumer *_samConsumer;
  std::string       _currentFile;
};

#endif // CAFE_SAMEXPANDER_HPP__
