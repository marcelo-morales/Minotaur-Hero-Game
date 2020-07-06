// Samuel Atefah; JHED: satefah1                                                                                                                                                                
// Chiamaka Anaemeribe; JHED: canaeme1                                                                                                                                                                   
// Marcelo Morales; JHED: lmoral10

#ifndef UICONTROL_H
#define UICONTROL_H

#include "entitycontroller.h"

// UIControl is an EntityController implementation which uses
// the singleton UI object to determine the requested move
// direction for controlled Entity.
class UIControl : public EntityController {
private:
  // copy constructor and assignment operator disallowed
  UIControl(const UIControl &);
  UIControl &operator=(const UIControl &);

public:
  UIControl();
  virtual ~UIControl();

  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;
};

#endif // UICONTROL_H
