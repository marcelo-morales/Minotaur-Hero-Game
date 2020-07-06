// Chiamka Anaemeribe canaeme1

// Samuel Atefah; JHED: satefah1
// Marcelo Morales; JHED: lmoral10

#include "maze.h"
#include "tilefactory.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <iterator>

Maze::Maze(int width, int height) {
	this->width = width;
	this->height = height;
	this->tiles.resize(width * height);
}

Maze::~Maze() {
	// delete tiles
	for (std::vector<Tile*>::iterator it = tiles.begin();
			it != tiles.end(); ++it) {
		delete *it;
	}
	tiles.clear();
}

int Maze::getWidth() const { return width; }

int Maze::getHeight() const { return height; }

bool Maze::inBounds(const Position &pos) const{ 
	return pos.inBounds(width, height);
}

void Maze::setTile(const Position &pos, Tile *tile) {
	tiles[width * pos.getY() + pos.getX()] = tile;
}

const Tile* Maze::getTile(const Position &pos) const {
	return tiles[width * pos.getY() + pos.getX()];
}

Maze* Maze::read(std::istream &in) {
	char c = '0';
	int testWidth = 0;
	int testHeight = 0;
	int inWidth = 0;
	int inHeight = 0;
	std::string inWidthStr;
	std::string inHeightStr;

	// check if width and height are valid 
	in >> inWidthStr;
	in >> inHeightStr;
	if (!(isInt(inWidthStr) && isInt(inHeightStr))) {
		return NULL;
	}
	inWidth = std::stoi(inWidthStr);
	inHeight = std::stoi(inHeightStr);
	if (inWidth < 0 || inHeight < 0) {
		return NULL;
	}
	in.get(c); // dump '\n'

	// set tiles from input stream
	Maze* inMaze = new Maze(inWidth, inHeight);
	while (in.get(c)) {
		if (c != '#' && c != '.' && c != '<' && c != 'm' && c != '\n') {
		  in.putback(c); 
		  if(testHeight == inHeight) {
		    return inMaze;
		  }
		  delete inMaze;
		  return NULL;
		}
		if (c == '\n') {
			if (testWidth < inWidth) { //actual width is smaller than given
				delete inMaze;
				return NULL;
			}
			testWidth = 0; 
			testHeight++;
			if (testHeight > inHeight) {  //actual height is bigger
				delete inMaze;
				return NULL;
			}

		} else {
			testWidth++;
			if (testWidth > inWidth) { //actual width is bigger
				delete inMaze;
				return NULL;
			}
			Position pos(testWidth - 1, testHeight);
			inMaze->setTile(pos, TileFactory::getInstance()
					->createFromChar(c));
		
		}
	}	
	if (testHeight < inHeight) { //actual height is smaller
		delete inMaze;
		return NULL;
	}
	return inMaze;
}

bool Maze::isInt(std::string in) {
	return !in.empty() && std::all_of(in.begin(), in.end(), ::isdigit);
}
