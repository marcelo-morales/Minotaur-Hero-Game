// Chiamka Anaemeribe canaeme1

// Samuel Atefah; JHED: satefah1
// Marcelo Morales; JHED: lmoral10

#include "wall.h"

// A Wall is a tile that no Entity can move onto
Wall::~Wall() {
}

MoveResult Wall::checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const {
        (void) entity; (void) fromPos; (void) tilePos;
        return MoveResult::BLOCK;
}

bool Wall::isGoal() const { return false; }

std::string Wall::getGlyph() const { return "#"; }
