#ifndef FORMATGUARDIO_H
#define FORMATGUARDIO_H

#include <iomanip>

namespace ilyak {
  class FormatGuardIO {
  public:
    FormatGuardIO(std::basic_ios< char >& s);
    ~FormatGuardIO();

  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}
#endif
