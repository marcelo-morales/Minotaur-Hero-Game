//Marcelo Morales
//lmoral10

// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1

#include "entity.h"
#include "position.h"
#include "entitycontroller.h"
#include "game.h"
#include "basicgamerules.h"
#include "gamerules.h"
#include <cctype>
#include <vector>
#include <algorithm>

//constructor
Entity::Entity() : glyph("\0"), controller(nullptr), current_position(0, 0)    { }

//destructor is for dynamic memory allocation
Entity::~Entity() {

  delete this->controller;
}


void Entity :: setGlyph(const std::string &glyph) {
    //setting glyph
    this->glyph = glyph;
}

//properties
//h - how do i set it to a Her
//m = how do i set it to a min
//v

//parameter string that is passed to this function should
//only contain the properties
void Entity :: setProperties(const std::string &props) {
	for (int i = 0; i < (int)props.length(); i++) {
		if (!this->hasProperty(props[i])) {
			properties.push_back(props[i]);
		}
	}
}

 std::string Entity :: getGlyph() const {
     return this->glyph;
 }

 std::string Entity :: getProperties() const {
	std::string props;
	for (std::vector<char>::const_iterator it = properties.begin();
			it != properties.end(); it++) {
		props += *it;
	}
	return props;
 }

 bool Entity :: hasProperty(char prop) const {
     return std::find(properties.begin(), properties.end(), prop)
	     != properties.end();
 }


//second character is entitiycontroller, tells entity how it will move
 void Entity :: setController(EntityController *controller) {
     this->controller = controller;    
 }


 EntityController* Entity :: getController() {
     return controller;
 }

 void Entity :: setPosition(const Position &pos) {
      
      this->current_position = pos;

 }

 Position Entity :: getPosition() const {

     return this->current_position;
 }


