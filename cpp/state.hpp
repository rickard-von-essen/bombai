#ifndef STATE_HPP
#define STATE_HPP

#include "area.hpp"
#include "bomb.hpp"

#include <iostream>
#include <map>
#include <list>

class Position;

class State {
  Area area;
  std::map<unsigned, Position> player_positions;
  std::list<Bomb> bombs;

public:
  State(size_t area_width, size_t area_height);

  unsigned count_bombs_for_player(unsigned id) const;
  bool is_clear(const Position& position) const;
  Position get_player_position(unsigned player_id) const;
  bool any_bomb_at(const Position& position) const;

  friend std::istream& operator>>(std::istream& in, State& state);
  friend std::ostream& operator<<(std::ostream& out, const State& state);
};

std::istream& operator>>(std::istream& in, State& state);
std::ostream& operator<<(std::ostream& out, const State& state);

#endif
