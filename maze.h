// Chiamka Anaemeribe canaeme1

// Samuel Atefah; JHED: satefah1
// Marcelo Morales; JHED: lmoral10

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include "tile.h"
#include "position.h"

class Tile;
class Entity;
class Position;

// A Maze is a grid of Tile objects.
class Maze {
private:
  // fields
  int width;
  int height;
  std::vector<Tile*> tiles;

  // disallow copy ctor and assignment operator
  Maze(const Maze &);
  Maze &operator=(const Maze &);

public:
  Maze(int width, int height);
  ~Maze();

  // Get the width of the Maze
  int getWidth() const;

  // Get the height of the Maze
  int getHeight() const;

  // Return true if the specified position is in bounds
  // according to the Maze's width and height.
  bool inBounds(const Position &pos) const;

  // Set a Tile at the specified Position.  The Maze assumes responsibility
  // for deleting the Tile.
  void setTile(const Position &pos, Tile *tile);

  // Get the Tile at the specified Position.
  const Tile *getTile(const Position &pos) const;

  // Read a description of a Maze from specified istream, and return it.
  static Maze *read(std::istream &in);

private:
  // Add your own private member functions

  // Returns true if s is an integer
  static bool isInt(std::string s);
};

#endif
