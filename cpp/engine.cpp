#include "engine.hpp"

#include "game.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sstream>

void Engine::randomize() {
  srand(time(NULL));
}

unsigned Engine::random(unsigned max_value) {
  return rand() % max_value;
}

Engine::Engine(unsigned player_id, const Game& game)
  : my_id(player_id),
    game(game)
{
  randomize();
}

std::string Engine::generate_action() const {
  const State& state = game.get_state();
  std::vector<std::string> available_moves;
  get_available_moves(state,
		      state.get_player_position(my_id),
		      available_moves);

  unsigned count = available_moves.size();
  if (state.count_bombs_for_player(my_id) < Bomb::MAX_BOMBS) {
    ++count;
  }

  unsigned choice = random(count);
  if (choice < available_moves.size()) {
    return available_moves[choice];
  }

  return generate_random_bomb_timer();
}

void Engine::get_available_moves(const State& state,
				 const Position& position,
				 std::vector<std::string>& available_moves) const {
  available_moves.push_back("pass");
  if (state.is_clear(position.up())) {
    available_moves.push_back("up");
  }
  if (state.is_clear(position.down())) {
    available_moves.push_back("down");
  }
  if (state.is_clear(position.left())) {
    available_moves.push_back("left");
  }
  if (state.is_clear(position.right())) {
    available_moves.push_back("right");
  }
}

std::string Engine::generate_random_bomb_timer() const {
  std::stringstream ss;
  unsigned timer = random(Bomb::MAX_TIMER - Bomb::MIN_TIMER) + Bomb::MIN_TIMER;
  ss << timer;
  return ss.str();
}
