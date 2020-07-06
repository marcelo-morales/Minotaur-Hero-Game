// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#include "game.h"
#include <iostream>
#include <vector>
#include <string>
#include "entity.h"
#include "entitycontroller.h"
#include "gamerules.h"
#include "basicgamerules.h"
#include "ui.h"
#include "mysterycontroller.h"
#include "maze.h"
#include "ecfactory.h"
#include "position.h"
#include "assert.h"

using std::vector;
using std::cout;
using std::endl;


//A Game object is just a container for Maze, UI, GameRules and Entiyy
/*class GameRules;
class BasicGameRules;
class Maze;
class Game;
class Entity;
class Position;
*/

//constructor
Game :: Game() : my_maze(nullptr), my_ui(nullptr), my_gameRules(nullptr) { }

//destructor
Game :: ~Game() {
    delete my_maze; //deleting
    delete my_gameRules;
    delete my_ui;
    for (std::vector<Entity *> :: iterator it = vector_of_entities.begin(); it !=  vector_of_entities.end(); ++it) {
      delete *it;
    }
}

void Game :: setMaze(Maze *maze) {
    this->my_maze = maze;
}

void Game :: setUI(UI *ui) {
    this->my_ui = ui;
}

void Game :: setGameRules(GameRules *gameRules) {
    this->my_gameRules = gameRules;
}

void Game :: addEntity(Entity *entity) {
    vector_of_entities.push_back(entity);
}

Entity* Game :: getEntityAt(const Position &pos) {
    for (std::vector<Entity *> :: const_iterator it = vector_of_entities.cbegin(); 
		    it !=  vector_of_entities.cend(); ++it) {
        Entity* current_entity = *it;
        Position check = current_entity->getPosition();
        if (check == pos) {
            return current_entity;
        }
    }
    return nullptr;
}

const Game::EntityVec& Game::getEntities() const {
    return this->vector_of_entities;
}

std::vector<Entity *> Game :: getEntitiesWithProperty(char prop) const{
    std::vector<Entity*> vector_properties;
    
    for (std::vector<Entity *>::const_iterator it = vector_of_entities.cbegin();
		    it != vector_of_entities.cend(); ++it) {
      if ((*it)->hasProperty(prop)) {
		vector_properties.push_back(*it);
	}
    }
    return vector_properties;
}

Maze * Game :: getMaze() {
    return this->my_maze;
}

UI * Game :: getUI() {
    return this->my_ui;
}

GameRules * Game :: getGameRules() {
    return this->my_gameRules;
}


void Game :: gameLoop() {

   GameRules* my_game_rules = this->getGameRules();
   std::string message;

   //Entity objects should take turn one at a time, in round robin fashion, until game ends
   bool quit_loop = false;

   while (quit_loop == false) {

        for (std::vector<Entity *> :: const_iterator it = vector_of_entities.cbegin(); it != vector_of_entities.cend(); ++it) {
            Entity* current_entity = *it;
            EntityController* current_controller = current_entity->getController();
     		
            GameResult result = my_game_rules->checkGameResult(this);
	    
            if (result == GameResult::HERO_WINS ) {
	      my_ui->render(this);
	      message = ": Hero wins";
	      cout << message << endl;
	      quit_loop = true;
	      break;
            }
            if (result == GameResult::HERO_LOSES) {
	      my_ui->render(this);
	      message = ": Hero loses";
	      cout << message << endl;
	      quit_loop = true;
	      break;
            }

            UI* my_ui = this->getUI();
            
	    if (current_controller->isUser()) {
                my_ui->render(this);
            }
	    
            std::string glyph = current_entity->getGlyph();

            takeTurn(current_entity);
        }
   }

}

void Game :: takeTurn(Entity *actor) {


  Direction new_direction = actor->getController()->getMoveDirection(this, actor);
  GameRules* my_game_rules = getGameRules();
  
  Position destination = actor->getPosition().displace(new_direction);

  if (my_game_rules->allowMove(this, actor, actor->getPosition(), destination)) {
     my_game_rules->enactMove(this, actor, destination);
  } else if (actor->getController()->isUser()) {
     std::cout << ": Illegal move" << std::endl;	
  }

}

Game * Game :: loadGame(std::istream &in) {
    Game * new_game = new Game();
    
    new_game->setMaze(Maze::read(in));
    // check for NULL Maze
    if (!new_game->getMaze()) {
	delete new_game;
        return NULL;
    }
    bool check_file_read = false;


    while (in) {
        check_file_read = true;

        std::string entity_descriptor;
        int x_coord;
        int y_coord;

       
        in >> entity_descriptor;
        in >> x_coord;
        in >> y_coord;

	if(entity_descriptor == "") {

	  return new_game;
	  
	}
	
        Entity* entity = new Entity();

        //setting the glyph for specific entity
        std::string glyph = entity_descriptor.substr(0, 1);
        //char specifying what controller it is
        char specify_controller = entity_descriptor.at(1);

        //setting glyph
        entity->setGlyph(glyph);

	// Marcelo, i commented out the if statement becaause it was creating valgrind issues.
	EntityController * my_controller = EntityControllerFactory::getInstance()->createFromChar(specify_controller);
	// if (EntityControllerFactory::getInstance()->createFromChar(specify_controller) == nullptr) {
	if(my_controller == nullptr) {
	  delete entity;
	  delete new_game;
	  //delete my_controller;
	  return nullptr; //game data is invalid
        }

	// EntityController *my_controller = EntityControllerFactory::getInstance()->createFromChar(specify_controller); 
        //setting controller
        entity->setController(my_controller);

        //remaining characters is property
        //didn't specify end of substr so should be til end?
        std::string properties = entity_descriptor.substr(2);
        //setting properties
        entity->setProperties(properties);

        //setting the position of the entity
        Position(x_coord, y_coord);
        entity->setPosition(Position(x_coord, y_coord));

	// Marcelo please check to make sure this is appropriate/reasonable
	new_game->addEntity(entity);
	//		delete entity;
    }
    
    if (check_file_read == false) {
      delete new_game;
      return nullptr; //still false, cold not read file, so return nullptr
    }


return new_game;

}

