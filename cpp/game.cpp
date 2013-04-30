#include "game.hpp"

bool Game::skip_actions(std::istream& in) const {
  // Since we have read the entire state we can skip the actions
  for (unsigned i = 0; i < number_of_players; ++i) {
    int player_id;
    std::string action;
    if(!(in >> player_id >> action)) {
      return false;
    }
  }
  return true;
}

Game::Game(unsigned number_of_players, unsigned max_number_of_turns,
	   size_t area_width, size_t area_height)
  : number_of_players(number_of_players),
    max_number_of_turns(max_number_of_turns),
    state(area_width, area_height)
{ }

bool Game::read_round(std::istream& in) {
  if (!(in >> state)) {
    return false;
  }
  if (!skip_actions(in)) {
    return false;
  }
  return true;
}

const State& Game::get_state() const {
  return state;
}

std::ostream& operator<<(std::ostream& out, const Game& game) {
  out << game.state;
  return out;
}
