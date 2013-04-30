#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

struct Position {
  unsigned x;
  unsigned y;

  Position()
    : x(0),
      y(0)
  {}

  Position(unsigned x, unsigned y)
    : x(x),
      y(y)
  {}

  Position left() const;
  Position right() const;
  Position up() const;
  Position down() const;

  bool operator==(const Position& right) const;
};

std::istream& operator>>(std::istream& in, Position& position);
std::ostream& operator<<(std::ostream& out, const Position& position);

#endif
