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

enum ActorType {
  kPlayer,
  kEnemy,
  kNeutral
};

class Actor {
 public:
  Actor();
  Actor(vec2 position, vec2 velocity, Rect collision, Rect hit_box,
        double max_health, double health, float speed,
        vector<bool> collision_layers, ActorType type);

  /**
   * Sets up the current actor
   * @param world the current world of the actor
   */
  virtual void Setup(World &world);

  /**
   * Updates the actor based on the passed timescale and a controller
   * @param time_scale the timescale of the world
   * @param world the world of the actor, may be modified
   * @param controller the player's controller
   */
  virtual void Update(float time_scale, World &world,
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

  /**
   * Checks whether this actor's hitbox is colliding with the collision of
   * another actor
   * @param other_actor the other actor to check collision with
   * @return a boolean representing whether this hitbox is colliding with the
   * other actor
   */
  virtual bool IsCollidingWithHitBox(const Actor &other_actor);

  /**
   * Subtracts health from the current actor
   * @param damage the amount of damage to take
   */
  virtual void Damage(double damage);

  vec2 GetPosition() const;
  vec2 GetVelocity() const;
  double GetHealth() const;
  double GetMaxHealth() const;

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
  ActorType type_;
  const static int kFrameSkip = 10;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTOR_H_
