#include "customtypes.h"

std::istream& dmitriev::operator>>(std::istream& inp, SeparatorIO&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  char c = '\0';
  inp >> c;
  if (inp && c != data.expected)
  {
    inp.setstate(std::ios::failbit);
  }

  return inp;
}

std::ostream& dmitriev::operator<<(std::ostream& out, const SeparatorIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << data.expected;
}

std::istream& dmitriev::operator>>(std::istream& inp, LableIO&& data)
{
  // TODO: �������� ����� �������� return
}

std::ostream& dmitriev::operator<<(std::ostream& out, const LableIO& data)
{
  // TODO: �������� ����� �������� return
}

std::istream& dmitriev::operator>>(std::istream& inp, DoubleI&& data)
{
  // TODO: �������� ����� �������� return
}

std::ostream& dmitriev::operator<<(std::ostream& out, const DoubleO& data)
{
  // TODO: �������� ����� �������� return
}

std::istream& dmitriev::operator>>(std::istream& inp, LongLongI&& data)
{
  // TODO: �������� ����� �������� return
}

std::ostream& dmitriev::operator<<(std::ostream& out, const LongLongO& data)
{
  // TODO: �������� ����� �������� return
}

std::istream& dmitriev::operator>>(std::istream& inp, StringI&& data)
{
  // TODO: �������� ����� �������� return
}

std::ostream& dmitriev::operator<<(std::ostream& out, const StringO& data)
{
  // TODO: �������� ����� �������� return
}
