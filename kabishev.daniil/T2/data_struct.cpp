#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <string>

namespace nspace
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'd' };
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    bool keys_valid[2] {false, false};
    std::size_t keys_valid_size = sizeof(keys_valid) / sizeof(keys_valid[0]);
    std::size_t keys_valid_last = keys_valid_size - 1;
    std::string key_current;
    {
      using sep = DelimiterIO;
      using dbl = DoubleIO;
      using str = StringIO;
      in >> sep{ '{' };
      for (std::size_t i = 0; i < keys_valid_size; ++i)
      {
        in >> str{ key_current };
        if (in && key_current == "key1")
        {
          in >> sep{ ':' } >> dbl{ input.key1 };
          if (i != keys_valid_last)
          {
            in >> sep{ ',' };
          }
          if (in)
          {
            keys_valid[0] = true;
          }
        }
        else if (in && key_current == "key2")
        {
          in >> sep{ ':' } >> str{ input.key2 };
          if (i != keys_valid_last)
          {
            in >> sep{ ',' };
          }
          if (in)
          {
            keys_valid[1] = true;
          }
        }
      }
      in >> sep{ '}' };
    }
    if (in)
    {
      if ((keys_valid[0] == keys_valid[1]) == true)
      {
        dest = std::move(input);
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }

  bool DataStruct::operator < (const DataStruct & other)
  {
    if (key1 != other.key1)
    {
      return (key1 < other.key1);
    }
    else
    {
      return key2.size() < other.key2.size();
    }
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "{ ";
    out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
    out << "\"key2\": " << src.key2;
    out << " }";
    return out;
  }
}
