//Marcelo Morales
//lmoral10

#include "ui.h"
#include <string>
#include "position.h"
#include "textui.h"
#include <iostream>
#include <stdio.h>
#include "maze.h"
#include "game.h"
#include "tile.h"
#include "position.h"
#include "goal.h"
#include "tilefactory.h"
#include "wall.h"
#include "entity.h"
using std::cout;
using std::endl;
using std::cin;

class UI;

TextUI :: TextUI() : message("") {
    

}

TextUI :: ~TextUI() {

}

// get requested move direction
Direction TextUI :: getMoveDirection() {
    
    bool correct_input = false;
    Direction direction_to_go = Direction :: NONE;

    while (correct_input == false ) {
        char move;
        cout << "Your move (u/d/l/r): ";
        cin >> move;

        if (move == 'u') {
            //Direction for up
            correct_input = true;
            direction_to_go = Direction :: UP;
            break;
        }
        if (move == 'd') {
            correct_input = true;
            direction_to_go = Direction :: DOWN;
            break;
        }
        if (move == 'l') {
            correct_input = true;
            direction_to_go = Direction :: LEFT;
            break;
        }
        if (move == 'r') {
            correct_input = true;
            direction_to_go = Direction :: RIGHT;
            break;
        }
        else {
            cout << "Unknown direction" << endl;

        }
    }
    return direction_to_go;
}

//The displayMessage member function should save the parameter string value in a field.
void TextUI :: displayMessage(const std::string &msg, bool endgame) {
    (void)endgame;
    this->message = msg; //saving it in field
}


void TextUI :: render(Game *game) {

    Maze* my_maze = game->Game :: getMaze();

    for (int i = 0; i < my_maze->getHeight(); ++i) {
      for (int j = 0; j < my_maze->getWidth(); ++j) {
	Position current_position(j, i);
	
	const Tile* current_tile = my_maze->getTile(current_position);
	std:: string tile_glyph = current_tile->getGlyph();
	Entity* current_entity = game->getEntityAt(current_position);
	std::string current_property;
	bool captured_glyph_print = false;
	
	if(current_entity) {
	  current_property = current_entity->getProperties();
	    
	  //check for hero
	  if (current_property.find('h') != std::string::npos) {
	    Position location_of_hero = current_entity->getPosition();
	    
	    std::vector<Entity *> vector_of_minotaurs = game->getEntitiesWithProperty('m');
                //hero found will check of something else is there
	    
	    if (!vector_of_minotaurs.empty()) {
	      
	      for (std::vector<Entity *> :: const_iterator it = vector_of_minotaurs.cbegin(); it != vector_of_minotaurs.cend(); ++it) {
		Entity* minotaur = *it;
		Position minotaur_location = minotaur->getPosition();
		//same place, do not print hero, print minotaur
		if (minotaur_location == location_of_hero) {
		  std::string minotaur_glyph = minotaur->getGlyph();
		  cout << minotaur_glyph;
		  captured_glyph_print = true;
		  break;
		  //have already printed glyph, go to next tile in maze
		}
		
	      }
	    }
	  }
	}
	    
	if (captured_glyph_print == true) {
	  //do not want to print glyph twice, go on to next tile in for loop
	  continue;
	}
	
	if (current_entity == nullptr) {
	  cout << tile_glyph;
	  continue;
	}
	
	std:: string entity_glyph = current_entity->getGlyph();
	    
	
	cout << entity_glyph;
	
	//cleanup
	tile_glyph.clear();
	entity_glyph.clear();
	
      }
      cout << endl;
    }
    
  this->TextUI :: displayMessage(message, false); //check if false

  if (!message.empty()) { //string is not empty check
      cout << message << endl;  //printing message
      message.clear(); //clearing message
  }

}


