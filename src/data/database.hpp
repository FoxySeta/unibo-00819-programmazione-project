/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  database.hpp: user interface of Data::Database and its helper entities.
*/

#ifndef DATA_DATABASE_HPP
#define DATA_DATABASE_HPP

#include <istream>
#include <ostream>

#include "../engine/colorable.hpp"
#include "../nostd/pair.hpp"
#include "../nostd/wstring.hpp"

namespace Data {
/*
  A Database collects every game object in an organized way. It is loaded from
  *non-standard* CSV, INI and plain text files.
*/
class Database {
public:
  using Subpalette = Nostd::Pair<Engine::Color, Engine::Color>;
  const struct Palette {
    Subpalette logo, frame, button, slider, message, gauge;
  } palette;

  constexpr static wchar_t separator{','}, escape{'\\'}, newline{'\n'};
};

std::basic_istream<wchar_t> &get_CSV_WString(std::basic_istream<wchar_t> &,
                                             Nostd::WString &);

std::basic_ostream<wchar_t> &put_CSV_WString(std::basic_ostream<wchar_t> &,
                                             const Nostd::WString &);

} // namespace Data

#endif
