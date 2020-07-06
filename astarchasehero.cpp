// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#include "astarchasehero.h"
#include "maze.h"
#include "position.h"
#include "basicgamerules.h"
#include "entity.h"
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <tuple>

using std::set; using std::vector; using std::priority_queue; using std::greater;
using std::map; using std::pair;
using std::make_pair; using std::tuple; using std::make_tuple;
using std::get;

AStarChaseHero::AStar::AStar(Maze &maze, Position &start, Position &goal) : m_maze(maze),  m_start(start), m_goal(goal) {}

AStarChaseHero::AStar::~AStar() {
}

// Check whether specified Entity (the actor) is allowed to move                                                                                                                                     
// from the specified source Position to the specified destination Position.                                                                                                                         
// Note that the source position is not necessarily the actor's Position,                                                                                                                            
// because this function could be called in pathfinding to evaluate                                                                                                                                  
// a hypothetical move.   
bool AStarChaseHero::AStar::allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const {
  
  return game->getGameRules()->allowMove(game, actor, source, dest);
}

// Compute g(n), the distance from start to pos.                                                                                                                                                      
int AStarChaseHero::AStar::g(std::map<Position, int> position_to_g, Position &current_pos, Position &prev_pos) {

  int distance = current_pos.distanceFrom(prev_pos) + position_to_g[prev_pos];
  return distance;
}

// Compute the heuristic function for a given Position using the distanceFrom function.                                                                                                              
int AStarChaseHero::AStar::h(const Position &pos) const{
  
  return pos.distanceFrom(m_goal);
}

 // Returns f(pos) = g(pos) + h(pos).                                                                                                                                                                  
int AStarChaseHero::AStar::f(Position &pos, int g_num) {
  
  return g_num + h(pos);
}

// Returns the start to the goal path.                                                                                                                             
std::vector<Position> AStarChaseHero::AStar::path(Position &current_pos) {
  
  vector<Position> end_to_start;
  vector<Position> start_to_end;
  
  end_to_start.push_back(current_pos);
  
  while(previous.find(current_pos) != previous.end()) {
    
    current_pos = previous[current_pos];
    end_to_start.push_back(current_pos);
  }
  
  for(vector<Position>::const_reverse_iterator it = end_to_start.crbegin();
      it != end_to_start.crend(); ++it) {

    start_to_end.push_back(*it);
  }
  
  return start_to_end;
}

// Returns a vector filled with valid neighbors to the current_pos.                                                                                                                                   
std::vector<Position> AStarChaseHero::AStar::getValidNeighbors(Game *game, Entity *entity, const Position &current_pos) {
  
  vector<Position> neighborhood;

  Position rightDir(current_pos.getX() +1, current_pos.getY());
  
  bool right = allowMove(game, entity, current_pos, rightDir);
  bool left = allowMove(game, entity, current_pos, current_pos.displace(Direction::LEFT));
  bool up = allowMove(game, entity, current_pos, current_pos.displace(Direction::UP));
  bool down = allowMove(game, entity, current_pos, current_pos.displace(Direction::DOWN));
  
  if(right) {neighborhood.push_back(current_pos.displace(Direction::RIGHT));}
  if(left) {neighborhood.push_back(current_pos.displace(Direction::LEFT));}
  if(up) {neighborhood.push_back(current_pos.displace(Direction::UP));}
  if(down) {neighborhood.push_back(current_pos.displace(Direction::DOWN));}
  
 
  return neighborhood;
}

// Performs the A* algorithm and returns a vector of Positions that represents a path to the goal.                                                                                                      
std::vector<Position> AStarChaseHero::AStar::search(Game *game, Entity *entity) {
  
  // Map from Position object to g(n).
  map<Position, int> pos_to_g;
  
  // Map from Position object to f(n) = g(n) + h(n).
  map<Position, int> pos_to_f;
  
  pos_to_g[m_start] = 0;
  pos_to_f[m_start] = -h(m_start);

  priority_queue<tuple<int, int, Position>> openQueue;
  
  vector<Position> start_to_end_path;
  
  openQueue.push(make_tuple(pos_to_f[m_start], -h(m_start), m_start));

  Position current_pos; 
  while(!openQueue.empty()) {

   current_pos = get<2>(openQueue.top()); 
     
    if(current_pos == m_goal) {
      
      return path(current_pos);
    }
    
    openQueue.pop();
    
    vector<Position> neighborhood = getValidNeighbors(game, entity, current_pos);

    for(vector<Position>::iterator it = neighborhood.begin();
	it != neighborhood.end(); ++it) {

      Position neighbor = *it;
      
      int g_num = g(pos_to_g, neighbor, current_pos);
      
      if(pos_to_g.find(neighbor) == pos_to_g.end()) {
    
	previous[neighbor] = current_pos;
	pos_to_g[neighbor] = g_num;
	pos_to_f[neighbor] = -f(neighbor,g_num);

	openQueue.push(make_tuple(pos_to_f[neighbor], -h(neighbor), neighbor));
      }
    }
  }
 
  return start_to_end_path;
}

AStarChaseHero::AStarChaseHero() : EntityController() {}

AStarChaseHero::~AStarChaseHero() {
}

// Determines the closest hero to the controlled Entity pointer.                                                                                                                                        
Entity * AStarChaseHero::closestHero(std::vector<Entity *> heroes, Entity *entity) {

  Entity * closest = heroes.front();
  Position closestPos = closest->getPosition();
  Position entityPos = entity->getPosition();

  int leastDistance = entityPos.distanceFrom(closestPos);

  // Checks to see which is the closest hero.                                                                                                                                                            
  for(vector<Entity *>::const_iterator it = heroes.cbegin();
      it != heroes.cend(); ++it) {

    Position heroPos = (*it)->getPosition();
    int distance = entityPos.distanceFrom(heroPos);

    if(distance < leastDistance) {
      leastDistance = distance;
      closest = *it;
    }
  }

  return closest;
}

Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity) {

  vector<Entity *> heroes = game->getEntitiesWithProperty('h');

  if(heroes.empty()) {
    return Direction::NONE;
  }

  // Gets closest hero to entity.                                                                                                                                                                        
  Entity * hero = this->closestHero(heroes, entity);

  Position entityPos = entity->getPosition();

  Position heroPos = hero->getPosition();
  
  AStar astar(*(game->getMaze()), entityPos, heroPos);

  vector<Position> path = astar.search(game, entity);

  if(path.empty()) {

    return Direction::NONE;

  }
  else {

    Position nextMove = path[1];

    if(nextMove == entityPos.displace(Direction::RIGHT)) {

      return Direction::RIGHT;
    }
    if(nextMove == entityPos.displace(Direction::LEFT)) {

      return Direction::LEFT;
    }
    if(nextMove == entityPos.displace(Direction::UP)) {

      return Direction::UP;
    }
    else {

      return Direction::DOWN;
    }

  }
}

bool AStarChaseHero::isUser() const {
  return false;
}
