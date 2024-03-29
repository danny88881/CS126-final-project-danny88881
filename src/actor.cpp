//
// Created by Danny on 11/15/2020.
//

#include "cinder/Rect.h"
#include "world.h"
#include "actor.h"

namespace final_project {

Actor::Actor() : position_(0,0), velocity_(0,0),
      knockback_velocity_(0), max_health_(3), health_(max_health_), speed_(5),
      collision_(-10, -10, 10, 10),
      hit_box_(-10, -10, 10, 10), collision_layers_(4, false),
      type_(kNeutral), freed_(false) {
}

Actor::Actor(vec2 position, vec2 velocity, Rect collision, Rect hit_box,
             double max_health, double health, float speed,
             vector<bool> collision_layers, ActorType type) :
      position_(position), velocity_(velocity), collision_(collision),
      hit_box_(hit_box), max_health_(max_health), health_(health),
      speed_(speed), collision_layers_(collision_layers), type_(type),
      knockback_velocity_(0), freed_(false)
{}

void Actor::Setup(World &world) {
}

void Actor::Update(float time_scale, World &world,
            const InputController &controller) {
  position_ += velocity_ * vec2(time_scale);
}

void Actor::Draw() const {
}

bool Actor::IsColliding(const Actor &other_actor) {
  bool common = false;
  for (size_t index = 0; index < collision_layers_.size(); ++index) {
    if (collision_layers_[index] && other_actor.collision_layers_[index]) {
      common = true;
      break;
    }
  }
  if (!common) {
    return false;
  }
  if ((collision_.x1_ + position_.x
      > other_actor.collision_.x2_ + other_actor.position_.x)
      ||(collision_.x2_ + position_.x
          < other_actor.collision_.x1_ + other_actor.position_.x)
      ||(collision_.y1_ + position_.y
          > other_actor.collision_.y2_ + other_actor.position_.y)
      ||(collision_.y2_ + position_.y
          < other_actor.collision_.y1_ + other_actor.position_.y) )
    return false;
  else
    return true;
}

bool Actor::IsCollidingWithHitBox(const Actor &other_actor) {
  if (type_ == other_actor.type_ && type_ != ActorType::kNeutral) {
    return false;
  }
  if ((hit_box_.x1_ + position_.x
      > other_actor.collision_.x2_ + other_actor.position_.x)
      ||(hit_box_.x2_ + position_.x
          < other_actor.collision_.x1_ + other_actor.position_.x)
      ||(hit_box_.y1_ + position_.y
          > other_actor.collision_.y2_ + other_actor.position_.y)
      ||(hit_box_.y2_ + position_.y
          < other_actor.collision_.y1_ + other_actor.position_.y) )
    return false;
  else
    return true;
}

void Actor::Damage(double damage) {
  health_ -= damage;
}

vec2 Actor::GetPosition() const {
  return vec2(position_);
}

vec2 Actor::GetVelocity() const {
  return vec2(velocity_);
}

double Actor::GetHealth() const {
  return health_;
}

double Actor::GetMaxHealth() const {
  return max_health_;
}

void Actor::SetKnockback(vec2 knockback) {
  knockback_velocity_ = knockback;
}

bool Actor::GetFreed() const {
  return freed_;
}

}