#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include <vector>

class Game;
class Position;
class State;

class Engine {
  const unsigned my_id;
  const Game& game;

  static void randomize();
  static unsigned random(unsigned max_value);

public:
  Engine(unsigned player_id, const Game& game);

  std::string generate_action() const;
  void get_available_moves(const State& state,
			   const Position& position,
			   std::vector<std::string>& available_moves) const;
  std::string generate_random_bomb_timer() const;
};

#endif
