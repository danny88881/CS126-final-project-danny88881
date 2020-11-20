//
// Created by Danny on 11/15/2020.
//

#include "cinder/gl/gl.h"
#include "world.h"
#include "actors/player.h"

namespace final_project {

using glm::vec2;

Player::Player() : Actor() {

}

Player::Player(vec2 position) : Actor() {
  position_ = position;
}

void Player::Draw() const {
  ci::gl::color(1,0,0,1);
  ci::gl::drawSolidCircle(position_, 10);
}

void Player::Update(float time_scale, const vector<Actor*> &actors,
                    const InputController &controller) {
  float hdir = (float)(controller.IsKeyPressed(Key::kRight)
      - controller.IsKeyPressed(Key::kLeft));
  float vdir = (float)(controller.IsKeyPressed(Key::kDown)
      - controller.IsKeyPressed(Key::kUp));
  vec2 direction(hdir, vdir);
  direction /= vec2((float)direction.length());
  velocity_ = direction * vec2(speed_);
  vec2 last_position = position_;
  position_ += velocity_ * time_scale;

  bool collision_occurred = false;
  for (const Actor* actor : actors) {
    if (actor != this && IsColliding(*actor)) {
      collision_occurred = true;
      break;
    }
  }

  if (collision_occurred) {
    position_ = last_position;
  }
}

}