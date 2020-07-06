// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#ifndef ASTARCHASEHERO_H
#define ASTARCHASEHERO_H

#include "entitycontroller.h"
#include <map>
#include <vector>
#include <set>

class Maze;
class Position;

class AStarChaseHero : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  AStarChaseHero(const AStarChaseHero &);
  AStarChaseHero &operator=(const AStarChaseHero &);
  
  // Helper class that computes the A* algorithm.                                                                                                                                                        
  class AStar {
  private:
    // fields                                                                                                                                                                                            
    Maze &m_maze;
    Position &m_start;
    Position &m_goal;
    std::map<Position, Position> previous;
    
    // disallow copy ctor and assignment operator                                                                                                                                                        
    AStar(const AStar &);
    AStar &operator=(const AStar &);
    
  public:
    AStar(Maze &maze, Position &start, Position &goal);
    ~AStar();
    
    // Check whether specified Entity (the actor) is allowed to move                                                                                                                                     
    // from the specified source Position to the specified destination Position.                                                                                                                         
    // Note that the source position is not necessarily the actor's Position,                                                                                                                            
    // because this function could be called in pathfinding to evaluate                                                                                                                                  
    // a hypothetical move.                                                                                                                                                                             
    bool allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const;

    // Returns f(pos) = g(pos) + h(pos).
    int f(Position &pos, int g_num);

    // Returns a vector filled with valid neighbors to the current_pos.
    std::vector<Position> getValidNeighbors(Game *game, Entity *entity, const Position &current_pos);
    
    // Performs the A* algorithm and returns a vector of Positions that represents a path to the goal.                                                                                                   
    std::vector<Position> search(Game *game, Entity *entity);    
    
  private:
    // Compute g(n), the distance from start to pos.                                                                                                                                                    
    int g(std::map<Position, int> postion_to_g, Position &current_pos, Position &prev_pos);
    
    // Compute the heuristic function for a given Position using the distanceFrom function.                                                                                                              
    int h(const Position &pos) const;

    // Returns the start to the goal path.
    std::vector<Position> path(Position &current_pos); 
    
  };
  
public:
  AStarChaseHero();
  virtual ~AStarChaseHero();

  // Determines the closest hero to the controlled Entitty pointer.
  Entity * closestHero(std::vector<Entity *> heroes, Entity *entity);
  
  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;
};

#endif // ASTARCHASEHERO_H
