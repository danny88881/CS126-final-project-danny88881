//
// Created by Danny on 11/30/2020.
//

#include "world.h"
#include "actors/slime.h"
#include "actors/splatter_particle.h"

namespace final_project {

Slime::Slime(vec2 position) : Enemy("sprites/enemies/slime.png", 2, 16, position,
            vec2(0), Rect(-10,-10,10,10), Rect(-15,-15,15,15), 3, 3, 4,
            glm::vec4((rand() % 256) / 256.0f,
                    (rand() % 256) / 256.0f,
                    (rand() % 256) / 256.0f, 1)), last_hp_(3) {
}

void Slime::Update(float time_scale, World &world,
                    const InputController &controller) {
  ++frame_index_;
  if (frame_index_ >= max_frames_ * frame_skip_) {
    frame_index_ = 0;
  }
  vec2 last_position = position_;

  if (glm::length(velocity_) < 0.008) {
    if (world.GetPlayer() != nullptr) {
      velocity_ =
          glm::normalize(world.GetPlayer()->GetPosition() - position_) * speed_;
    } else {
      int rand1 = rand() % 101 - 50;
      int rand2 = rand() % 101 - 50;
      if (rand1 != 0 && rand2 != 0) {
        velocity_ = glm::normalize(vec2(rand1, rand2)) * speed_;
      }
    }
  } else {
    velocity_ *= 0.9;
  }
  if (glm::length(knockback_velocity_) >= 0.4) {
    velocity_ = knockback_velocity_;
    knockback_velocity_ *= 0.8;
  }
  if (last_hp_ != health_) {
    last_hp_ = health_;
    /* size_t particle_count = rand() % 3 + 2;
    for (size_t index = 0; index < particle_count; ++index) {
      vec2 offset = vec2(rand() % 21 - 10, rand() % 21 - 10);
      auto particle = new SplatterParticle(position_ + offset, modulate_);
      world.AddActor(particle);
    } don't spawn particle effect */
  }

  bool collision_occurred = false;
  for (const Actor *actor : world.GetActors()) {
    if (actor != this && IsColliding(*actor)) {
      collision_occurred = true;
      break;
    }
  }

  position_ += velocity_ * time_scale;

  // double collision check prevents slimes from sticking
  if (!collision_occurred) {
    collision_occurred = false;
    for (const Actor *actor : world.GetActors()) {
      if (actor != this && IsColliding(*actor)) {
        collision_occurred = true;
        break;
      }
    }
  } else {
    collision_occurred = false;
  }

  if (collision_occurred) {
    position_ = last_position;
  }

  for (Actor *actor : world.GetActors()) {
    if (actor != this && IsCollidingWithHitBox(*actor)) {
      //actor->Damage(kDamage); slimes do no damage
      vec2 knockback = glm::normalize(actor->GetPosition() - position_)
                 * vec2((float)kKnockbackForce);
      actor->SetKnockback(knockback);
    }
  }

  if (health_ <= 0) {
    world.QueueFree(this);
    world.AddPoint();
    /* size_t particle_count = rand() % 3 + 2;
    for (size_t index = 0; index < particle_count; ++index) {
      vec2 offset = vec2(rand() % 21 - 10, rand() % 21 - 10);
      auto particle = new SplatterParticle(position_ + offset, modulate_);
      world.AddActor(particle);
    } don't spawn particle effect */
    return;
  }
}

}