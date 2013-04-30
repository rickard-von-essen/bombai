#ifndef BOMB_HPP
#define BOMB_HPP

#include "position.hpp"

struct Bomb {
  unsigned owner;
  unsigned ticks_left;
  Position position;

  Bomb(unsigned owner, const Position& position, unsigned ticks_left)
    : owner(owner),
      ticks_left(ticks_left),
      position(position)
  {}

  Bomb()
    : owner(0),
      ticks_left(0),
      position(Position())
  {}

  static const unsigned MIN_TIMER = 5;
  static const unsigned MAX_TIMER = 25;
  static const unsigned MAX_BOMBS = 5;
};

std::istream& operator>>(std::istream& in, Bomb& bomb);
std::ostream& operator<<(std::ostream& out, const Bomb& bomb);


#endif
