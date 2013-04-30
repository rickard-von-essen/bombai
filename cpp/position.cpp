#include "position.hpp"

Position Position::left() const {
  return Position(x - 1, y);
}

Position Position::right() const {
  return Position(x + 1, y);
}

Position Position::up() const {
  return Position(x, y - 1);
}

Position Position::down() const {
  return Position(x, y + 1);
}

bool Position::operator==(const Position& right) const {
  return x == right.x && y == right.y;
}

std::istream& operator>>(std::istream& in, Position& position) {
  in >> position.x >> position.y;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Position& position) {
  out << position.x << " " << position.y;
  return out;
}
