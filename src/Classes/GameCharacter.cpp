#include "GameCharacter.h"

using std::string;

GameCharacter::GameCharacter(const Vec2 &spawn, Sprite *sprite, string &name) {
  this->spawn = spawn;
  this->sprite = sprite;
  this->sprite->setName(name);
}

void GameCharacter::updatePosition(const Vec2 &position) {
  sprite->setPosition(position);
}

void GameCharacter::setTarget(const Vec2 &target) {
  this->target = target;
}

Sprite *GameCharacter::getSprite() {
  return sprite;
}
const Vec2 &GameCharacter::getSpawn() const {
  return spawn;
}

const Vec2 &GameCharacter::getTarget() const {
  return target;
}
