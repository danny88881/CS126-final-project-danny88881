//
// Created by Danny on 11/15/2020.
//

#include "cinder/gl/gl.h"
#include "actors/player.h"

namespace final_project {

using glm::vec2;

Player::Player() {

}

void Player::Draw() const {

}

void Player::Update(double time_scale, const World &world,
                    const InputController &controller) {
  float hdir = (float)(controller.IsKeyPressed(Key::kRight)
      - controller.IsKeyPressed(Key::kLeft));
  float vdir = (float)(controller.IsKeyPressed(Key::kDown)
      - controller.IsKeyPressed(Key::kRight));
  vec2 direction(hdir, vdir);
  direction /= vec2((float)direction.length());
  velocity_ = direction * vec2(speed_);


}

}