#include "engine.hpp"
#include "game.hpp"

#include <iostream>

int main() {
  unsigned player_id;
  std::cin >> player_id;

  unsigned number_of_players;
  unsigned max_number_of_turns;
  size_t width;
  size_t height;
  std::cin >> number_of_players
	   >> max_number_of_turns
	   >> width
	   >> height;

  Game game(number_of_players, max_number_of_turns, width, height);
  Engine engine(player_id, game);
  while (game.read_round(std::cin)) {
    std::cout << engine.generate_action() << std::endl;
  }
}
