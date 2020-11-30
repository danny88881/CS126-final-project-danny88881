//
// Created by Danny on 11/30/2020.
//

#include "world.h"
#include "actors/slime.h"

namespace final_project {

Slime::Slime(vec2 position) : Enemy("sprites/enemies/slime.png", 2, 16, position,
            vec2(0), Rect(-10,-10,10,10), Rect(-15,-15,15,15), 3, 3, 4) {
}

void Slime::Update(float time_scale, World &world,
                    const InputController &controller) {
  ++frame_index_;
  if (frame_index_ >= max_frames_ * frame_skip_) {
    frame_index_ = 0;
  }
  vec2 last_position = position_;

  if (glm::length(velocity_) < 0.05) {
    velocity_ = glm::normalize(world.GetPlayer()->GetPosition() - position_)
                * speed_;
  } else {
    velocity_ *= 0.9;
  }
  if (glm::length(knockback_velocity_) >= 0.4) {
    velocity_ = knockback_velocity_;
    knockback_velocity_ *= 0.8;
  }
  position_ += velocity_ * time_scale;

  bool collision_occurred = false;
  for (const Actor *actor : world.GetActors()) {
    if (actor != this && IsColliding(*actor)) {
      collision_occurred = true;
      break;
    }
  }

  if (collision_occurred) {
    position_ = last_position;
  }

  for (Actor *actor : world.GetActors()) {
    if (actor != this && IsCollidingWithHitBox(*actor)) {
      actor->Damage(kDamage);
      vec2 knockback = glm::normalize(actor->GetPosition() - position_)
                 * vec2((float)kKnockbackForce);
      actor->SetKnockback(knockback);
    }
  }
}

}