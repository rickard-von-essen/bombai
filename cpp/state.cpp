#include "state.hpp"

#include "position.hpp"
#include "bomb.hpp"

#include <cassert>

State::State(size_t area_width, size_t area_height)
  : area(area_width, area_height)
{}

unsigned State::count_bombs_for_player(unsigned id) const {
  unsigned count = 0;
  for (std::list<Bomb>::const_iterator i = bombs.begin();
       i != bombs.end(); ++i) {
    if (i->owner == id) {
      ++count;
    }
  }
  return count;
}

bool State::is_clear(const Position& position) const {
  return (area(position) == FLOOR &&
	  !any_bomb_at(position));
}

bool State::any_bomb_at(const Position& position) const {
  for (std::list<Bomb>::const_iterator i = bombs.begin();
       i != bombs.end(); ++i) {
    if (position == i->position) {
      return true;
    }
  }
  return false;
}

Position State::get_player_position(unsigned player_id) const {
  std::map<unsigned, Position>::const_iterator i = player_positions.find(player_id);
  assert(i != player_positions.end());
  return i->second;
}

std::istream& operator>>(std::istream& in, State& state) {
  in >> state.area;

  unsigned live_player_count;
  in >> live_player_count;

  for (unsigned i = 0; i < live_player_count; ++i) {
    unsigned player_id;
    in >> player_id;
    in >> state.player_positions[player_id];
  }

  unsigned bomb_count;
  in >> bomb_count;
  for (unsigned i = 0; i < bomb_count; ++i) {
    Bomb bomb;
    in >> bomb;
    state.bombs.push_back(bomb);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const State& state) {
  out << state.area;

  for (std::map<unsigned, Position>::const_iterator i = state.player_positions.begin();
       i != state.player_positions.end(); ++i) {
    out << i->first << " " << i->second << "\n";
  }

  for (std::list<Bomb>::const_iterator i = state.bombs.begin();
       i != state.bombs.end(); ++i) {
    out << *i << "\n";
  }

  return out;
}
