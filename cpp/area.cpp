#include "area.hpp"

#include "position.hpp"

#include <cassert>

size_t Area::position_to_index(const Position& position) const {
  size_t index = position.x + position.y * width;
  assert(index < data.size());
  return index;
}

Area::Area(size_t width, size_t height)
  : width(width),
    height(height)
{
  data.resize(width * height);
}

size_t Area::get_width() const {
  return width;
}

size_t Area::get_height() const {
  return height;
}

char Area::operator()(const Position& position) const
{
  return data[position_to_index(position)];
}

char& Area::operator()(const Position& position) {
  return data[position_to_index(position)];
}

std::istream& operator>>(std::istream& in, Area& area) {
  for (std::vector<char>::iterator i = area.data.begin(); i != area.data.end(); ++i) {
    in >> *i;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Area& area) {
  for (unsigned y = 0; y < area.get_height(); ++y) {
    for (unsigned x = 0; x < area.get_width(); ++x) {
      out << area(Position(x, y));
    }
    out << "\n";
  }
  return out;
}
