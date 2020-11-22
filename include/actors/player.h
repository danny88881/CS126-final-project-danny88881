//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_

#include "cinder/app/App.h"
#include "actor.h"

namespace final_project {

class World;

class Player : public Actor {
 public:
  Player();
  Player(vec2 position);

  virtual void Setup(World &world) override;

  virtual void Update(float time_scale, const vector<Actor*> &actors,
                      const InputController &controller) override;
  virtual void Draw() const override;
 private:
  const std::string kSpriteSheetPath = "sprites/player/CharacterSpriteSheet.png";
  ci::gl::TextureRef sprite_sheet_;
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_
