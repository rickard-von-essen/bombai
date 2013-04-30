#include "bomb.hpp"

std::istream& operator>>(std::istream& in, Bomb& bomb) {
  in >> bomb.owner >> bomb.position >> bomb.ticks_left;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Bomb& bomb) {
  out << bomb.owner << " " << bomb.position << " " << bomb.ticks_left;
  return out;
}
