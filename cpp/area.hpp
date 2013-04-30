#ifndef AREA_HPP
#define AREA_HPP

#include <iostream>
#include <vector>

const char WALL = '#';
const char FORCE_FIELD = '+';
const char FLOOR = '.';

class Position;

class Area {
  std::vector<char> data;

  size_t width;
  size_t height;

  size_t position_to_index(const Position& position) const;

public:
  Area(size_t width, size_t height);

  size_t get_width() const;
  size_t get_height() const;

  char operator()(const Position& position) const;
  char& operator()(const Position& position);

  friend std::istream& operator>>(std::istream& in, Area& area);
};

std::istream& operator>>(std::istream& in, Area& area);
std::ostream& operator<<(std::ostream& out, const Area& area);

#endif
