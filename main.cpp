// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

//driver program to play the game

#include <iostream>
#include "game.h"
#include "basicgamerules.h"
#include "textui.h"
#include <fstream>


using std::cout;
using std::endl;

class BasicGameRules;
class Game;
class TextUI;


int main(int argc, char *argv[]) {
  const char *filename;
  if (argc < 2) {
    std::cerr << "Error: Need filename" << std::endl;
    return 1;
  }
  filename = argv[1];

  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Error: Could not open maze file" << std::endl;
    return 1;
  }

  Game *game = Game::loadGame(in);
  if (!game) {
    std::cerr << "Error: Invalid game file" << std::endl;
    return 1;
  }

  game->setUI(new TextUI());
  game->setGameRules(new BasicGameRules());
  game->gameLoop();

  delete game;

  return 0;
}
