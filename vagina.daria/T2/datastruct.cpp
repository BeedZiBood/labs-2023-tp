#include "datastruct.h"
#include <iomanip>
#include <vector>
#include <iterator>
#include "IOFmtGuard.h"
#include "TypesIO.h"

std::istream& vagina::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using ull = BinUnsignedLongLongIO;
    using dbl = DoubleIO;
    using str = StringIO;
    std::string keyN = "";
    in >> sep{ '(' } >> sep { ':' };
    for (auto i = 1; i <= 3; i++)
    {
      in >> keyN;
      if (keyN == "key1")
      {
        in >> dbl{ input.key1 } >> sep { ':' };
      }
      else if (keyN == "key2")
      {
        in >> ull{ input.key2 } >> sep { ':' };
      }
      else if (keyN == "key3")
      {
        in >> str{ input.key3 } >> sep { ':' };
      }
      if (!sentry)
      {
        return in;
      }
    }
    if (input.key3 == "" || input.key1 == 0)
    {
      in.setstate(std::ios::failbit);
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}
std::ostream& vagina::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1 " << std::scientific << std::setprecision(2) << src.key1 << ":";
  out << "key2 " << "0b";
  auto num = src.key2;
  std::vector < int > vect;
  int i = 0;
  while (num)
  {
    vect.push_back(num % 2);
    num /= 2;
    i++;
  }
  std::copy(vect.rbegin(),vect.rend(),
    std::ostream_iterator< int >(out)
  );
  out << ":key3 " << std::quoted(src.key3);
  out << ":)";
  return out;
}
bool vagina::comp(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 < rhs.key1)
  {
    return true;
  }
  else if ((lhs.key1 == rhs.key1) && lhs.key2 < rhs.key2)
  {
    return true;
  }
  else if ((lhs.key1 == rhs.key1) && (lhs.key2 == rhs.key2) && lhs.key3 < rhs.key3)
  {
    return true;
  }
  else
  {
    return false;
  }
}
