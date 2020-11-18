//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTOR_H_
#define FINAL_PROJECT_INCLUDE_ACTOR_H_

#include "cinder/Rect.h"
#include "cinder/gl/gl.h"

namespace final_project {

using glm::vec2;
using ci::RectT;

class World;

class Actor {
 public:
  Actor();

  /**
   * Updates the actor based on the passed timescale
   * @param time_scale the timescale of the world
   * @param world the world that the actor is in
   */
  virtual void Update(float time_scale, const World &world);

  /**
   * Draws the actor onto the world
   */
  virtual void Draw() const;

  /**
   * Checks whether the two actors' collision boxes are intersecting
   * @param other_actor the other actor to check collision with
   * @return a boolean representing whether their collisions are intersecting
   */
  virtual bool IsColliding(const Actor &other_actor);

 protected:
  vec2 position_;
  vec2 velocity_;
  RectT<int> collision_;
  double max_health_;
  double health_;
  float speed_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTOR_H_
