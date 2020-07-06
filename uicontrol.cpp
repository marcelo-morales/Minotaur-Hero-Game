// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#include "uicontrol.h"
#include "ui.h"

// Default constructor implementation.
UIControl::UIControl() : EntityController() {}

UIControl::~UIControl() {

}


// Return a Direction specifying the direction in which                                                                                                                                                 
// specified Entity should try to move.
Direction UIControl::getMoveDirection(Game *game, Entity *entity) {
  
  UI *ui = UI::getInstance();
  Direction dir = ui->getMoveDirection();

  // Unused variables
  (void) game;
  (void) entity;

  //  delete ui;  
  return dir;
  
}

// Return true since this EntityController is controlled by                                                                                                                                             
// user input.
bool UIControl::isUser() const {

  return true;

}
