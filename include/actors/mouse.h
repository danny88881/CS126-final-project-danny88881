//
// Created by Danny on 11/20/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_MOUSE_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_MOUSE_H_

#include "cinder/app/App.h"
#include "actor.h"

namespace final_project {

class World;

class Mouse : public Actor {
 public:
  Mouse();

  virtual void Setup(World &world);
  virtual void Update(float time_scale, const vector<Actor*> &actors,
                      const InputController &controller) override;
  virtual void Draw() const override;
 private:
  const std::string kSpritePath = "sprites/ui/Mouse.png";
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_MOUSE_H_
