//
// Created by Danny on 12/7/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_SPLATTER_PARTICLE_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_SPLATTER_PARTICLE_H_

#include "actor.h"
#include "cinder/gl/gl.h"

namespace final_project {

using glm::vec2;

class SplatterParticle : public Actor {
 public:
  SplatterParticle(vec2 position, glm::vec4 color);

  virtual void Setup(World &world) override;
  virtual void Draw() const override;

 private:
  glm::vec4 color_;
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
  std::string kSpriteSheetPath = "sprites/effects/splatter.png";
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_SPLATTER_PARTICLE_H_
