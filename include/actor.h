//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTOR_H_
#define FINAL_PROJECT_INCLUDE_ACTOR_H_

#include "input_controller.h"
#include "cinder/gl/gl.h"
#include <vector>

namespace final_project {

using glm::vec2;
using std::vector;

class World;

// Top left to bottom right
struct Rect {
  int x1_;
  int y1_;
  int x2_;
  int y2_;

  Rect(int x1, int y1, int x2, int y2) : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {};
};

class Actor {
 public:
  Actor();
  Actor(vec2 position, vec2 velocity, Rect collision, Rect hit_box,
        double max_health, double health, float speed,
        vector<bool> collision_layers);

  /**
   * Sets up the current actor
   * @param world the current world of the actor
   */
  virtual void Setup(World &world);

  /**
   * Updates the actor based on the passed timescale and a controller
   * @param time_scale the timescale of the world
   * @param actors the actors in the same world
   * @param controller the player's controller
   */
  virtual void Update(float time_scale, const vector<Actor*> &actors,
                      const InputController &controller);

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
  vec2 knockback_velocity_;
  Rect collision_;
  Rect hit_box_;
  double max_health_;
  double health_;
  float speed_;
  vector<bool> collision_layers_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTOR_H_
