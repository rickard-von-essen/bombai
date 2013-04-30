#ifndef GAME_HPP
#define GAME_HPP

#include "state.hpp"

#include <iostream>

class Game {
  unsigned number_of_players;
  unsigned max_number_of_turns;
  State state;

  bool skip_actions(std::istream& in) const;

public:
  Game(unsigned number_of_players, unsigned max_number_of_turns,
       size_t area_width, size_t area_height);

  bool read_round(std::istream& in);
  const State& get_state() const;

  friend std::ostream& operator<<(std::ostream& out, const Game& game);
};

std::ostream& operator<<(std::ostream& out, const Game& game);

#endif
