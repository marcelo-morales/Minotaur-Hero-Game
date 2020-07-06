// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#include "gamerules.h"
#include "basicgamerules.h"
#include "maze.h"
#include "entity.h"
#include "position.h"
#include "tile.h"
#include <vector>
using std::vector;

BasicGameRules::BasicGameRules() {
}

BasicGameRules::~BasicGameRules() {
}

// Check whether specified Entity (the actor) is allowed to move
// from the specified source Position to the specified destination Position.
// Note that the source position is not necessarily the actor's Position,
// because this function could be called in pathfinding to evaluate
// a hypothetical move.
bool BasicGameRules :: allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const {
	// check if source and dest are adjacent
	if (source.distanceFrom(dest) != 1) {
		return false;
	}

	// check for game's maze
	Maze* maze = game->getMaze();
	if (!maze) { return false; }


	// check if dest position is in bounds
	if (game->getMaze()->inBounds(dest) == false) { return false; }


	// check tile at dest is occupied, if occupied...
	Entity *occupier = game->getEntityAt(dest);


	if (occupier) {
		// check occupying entity is moveable and can move to another empty tile
		if (occupier->hasProperty('v')) {
			// get direction of actor
			Direction actorDir = getDirection(source, dest);
			// check if displace position of dest is in bounds
			Position displaced = dest.displace(actorDir);
			if (maze->inBounds(displaced) == false) {
			  return false;
			}
			// check if there is an entity on displaced position
			if (game->getEntityAt(displaced)) {
			  return false;
			}
			// check if occupier can move onto tile at displaced
			if (maze->getTile(displaced)->checkMoveOnto(occupier, dest, displaced)
					== MoveResult::BLOCK) {
			  return false;
			}
			return true;
		}
		// check occupying entity is hero and actor is my_minotaur
		return (occupier->hasProperty('h') && actor->hasProperty('m'))
			|| (occupier->hasProperty('m') && actor->hasProperty('h'));
	}

	// check tile's checkMoveOnto
	if (maze->getTile(dest)->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW) {
	  return true;
	}
	return false;
}

// Return the direction (UP, DOWN, LEFT, or RIGHT) from <source> to <dest>
// Assumptions: <source> and <dest> are 1 move away from each other
Direction BasicGameRules::getDirection(const Position &source, const Position &dest) {
	int xDis = dest.getX() - source.getX();
        int yDis = dest.getY() - source.getY();
	if (xDis < 0) {  	// dest is behind of source
		return Direction::LEFT;
	} else if (xDis > 0) {	// dest is ahead of source
		return Direction::RIGHT;
	} else if (yDis < 0) {	// dest is above source
		return Direction::UP;
	} else {		// dest is below source
		return Direction::DOWN;
	}
}

// Carry out the move of specified Entity (the actor) to the
// specified destination Position.  This should only be called
// if allowMove returned true.
void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const {
        // get direction                                                                         
        Direction direct = getDirection(actor->getPosition(), dest);

        // check if theres an occuping entity at dest and move                                                                  
        Entity* occupier = game->getEntityAt(dest);
        // if actor is not mino nor occupier is hero or vice versa
	if (occupier && occupier->hasProperty('v')) {
		occupier->setPosition(dest.displace(direct));
	}

        // move actor                                          
        actor->setPosition(dest);
}

// Check the Game state to determine the GameResult
GameResult BasicGameRules::checkGameResult(Game *game) const {

    //all entities present in game
    vector<Entity *> vector_of_entities = game->getEntities();
    int index = 0;

    //loop through all the entities
    for (vector<Entity *>::const_iterator it = vector_of_entities.cbegin();
	 it != vector_of_entities.cend(); ++it) {
        Entity *current_entity = *it;


        if (current_entity->hasProperty('h') && checkPlayerWins(game, current_entity)) {
	        return GameResult::HERO_WINS;
        }
	    else if (current_entity->hasProperty('m') && checkMinotaurWins(vector_of_entities, index)) {
	        return GameResult::HERO_LOSES;
        }
    
      ++index;
    }
    
    
    //got out of for loop, result of game is unknown then 
    return GameResult::UNKNOWN;
}

//helper function to check if a current player has won the game
//checks if the current positon of a player is in the goal
//if so, player has won, return true
//if position of player is not in goal, return false
bool BasicGameRules::checkPlayerWins(Game *game, Entity *player) const {
    Maze *my_maze = game->getMaze();
    Position player_position = player->getPosition();
    const Tile *player_tile = my_maze->getTile(player_position);
    return player_tile->isGoal();

}


//helper function to check if a minotaur has won the game
bool BasicGameRules::checkMinotaurWins(std::vector<Entity *> vector_of_entities, int index_of_a_minotaur) const {
     
     //minotaur entity
     Entity* my_minotaur = vector_of_entities[index_of_a_minotaur];
     
     //position of a minotaur
     Position minotaur_location = my_minotaur->getPosition();
     
     
     for (std::vector<Entity *> :: const_iterator it = vector_of_entities.cbegin(); it != vector_of_entities.cend(); ++it) {

        Entity *player = *it;

        Position player_location = player->getPosition();

        if (player_location == minotaur_location && player->hasProperty('h')) {
            //player is in same position as minotaur, minotaur won

	  return true;
        }
    }
 
     //got out of for loop, so minotaur lost, minotaur and player do not share same position
    return false;

}

