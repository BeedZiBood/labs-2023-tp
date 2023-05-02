#include "TypesIO.h"
#include <bitset>
std::istream &operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::scientific >> dest.num;
}
std::istream& operator >>(std::istream& in, LiteralIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (dest.literal.find(c) == std::string::npos))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream &operator>>(std::istream &in, BinUnsignedLongLongIO &&dest)
{
  in >> DelimiterIO{ '0' } >> LiteralIO{ "bB" };
  unsigned long long num = 0;
  in >> num;
  unsigned long long res = 0;
  int pow = 1;
  while (num != 0)
  {
    if (num % 10 == 1 || num % 10 == 0)
    {
      res += num % 10 * pow;
      pow *= 2;
      num /= 10;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  dest.num = res;
  return in;
}
std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char delim = '0';
  in >> delim;
  if (in && (delim != dest.char_))
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
  return std::getline(in >> DelimiterIO{ '"' }, dest.string, '"');
}
