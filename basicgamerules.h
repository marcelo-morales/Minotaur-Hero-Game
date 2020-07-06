// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#ifndef BASICGAMERULES_H
#define BASICGAMERULES_H

#include "gamerules.h"
#include "position.h"

class BasicGameRules : public GameRules {
private:
  // copy constructor and assignment operator are disallowed
  BasicGameRules(const BasicGameRules &);
  BasicGameRules &operator=(const BasicGameRules &);

public:
  BasicGameRules();
  virtual ~BasicGameRules();

  virtual bool allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const;
  virtual void enactMove(Game *game, Entity *actor, const Position &dest) const;
  virtual GameResult checkGameResult(Game *game) const;

private:
  virtual bool checkPlayerWins(Game *game, Entity *player) const;
  virtual bool checkMinotaurWins(std::vector<Entity *> entity_vec, int index) const;
  static Direction getDirection(const Position &source, const Position &dest);
};

#endif // BASICGAMERULES_H
