#include "IOFmtGuard.h"
#include "IOStructs.h"
#include <iostream>
#include <iomanip>

namespace nesterov
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> data) && (data.find("key") != 0))
    {
      in.setstate(std::ios::failbit);
    }
    dest.exp = data;
    return in;
  }

  std::istream &operator>>(std::istream &in, HexIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOFmtGuard iofmtguard(in);
    return in >> std::hex >> dest.ref;
  }

  std::istream &operator>>(std::istream &in, RationalIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    return in >> sep{'('} >> sep{':'} >> sep{'N'} >> dest.ref.first >> sep{':'} >> sep{'D'} >> dest.ref.second >> sep{':'} >> sep{')'};
  }
}
