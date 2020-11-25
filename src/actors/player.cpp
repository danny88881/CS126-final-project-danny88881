//
// Created by Danny on 11/15/2020.
//

#include "cinder/gl/gl.h"
#include "world.h"
#include "actors/player.h"

namespace final_project {

using glm::vec2;

Player::Player() : Actor(vec2(0,0), vec2(0,0), Rect(-20,-20,20,20),
                         Rect(-20,-20,20,20), 3, 3, 4,
            {true, false, false, false}), frame_index_(0), x_scale_(1),
      attack_(false), attack_frame_length_(12), attack_frame_(12),
      can_attack_(true), attack_frame_delay_(12) {
}

Player::Player(vec2 position) : Player() {
  position_ = position;
}

void Player::Setup(World &world) {
  int index = world.LoadTexture(kSpriteSheetPath);
  material_ = ci::gl::GlslProg::create(
      ci::gl::GlslProg::Format()
          .vertex(CI_GLSL(
                      150,
                      uniform mat4 ciModelViewProjection;
                          in vec4 ciPosition;
                          in vec2 ciTexCoord0;
                          out vec2 TexCoord0;
                          void main(void) {
                            gl_Position = ciModelViewProjection * ciPosition;
                            TexCoord0 = ciTexCoord0;
                          }))
          .fragment(CI_GLSL(
                        150,
                        uniform sampler2D uTex0;
                            uniform sampler2D uTex1;
                            uniform vec4 uColor;
                            uniform int frame;
                            uniform int max_frames;
                            in vec2 TexCoord0;
                            out vec4 oColor;
                            void main(void) {

                              float u = TexCoord0.x * (1.0 / max_frames)
                              + (frame) * 1.0 / max_frames;

                              vec4 color = texture2D(uTex0,
                                            vec2(u, TexCoord0.y))
                                           * uColor;
                              oColor = color;
                            }))
      );
  rect_ = ci::gl::Batch::create(ci::geom::Plane(), material_);
  ci::ColorAf color( 1,1,1,1 );
  material_->uniform("uTex0", index);
  material_->uniform("frame", 0);
  material_->uniform("max_frames", kMaxFrames);
  material_->uniform( "uColor", color );

  int scythe_index = world.LoadTexture(kScytheSpritePath);
  scythe_material_ = ci::gl::GlslProg::create(
      ci::gl::GlslProg::Format()
          .vertex(CI_GLSL(
                      150,
                      uniform mat4 ciModelViewProjection;
                          in vec4 ciPosition;
                          in vec2 ciTexCoord0;
                          out vec2 TexCoord0;
                          void main(void) {
                            gl_Position = ciModelViewProjection * ciPosition;
                            TexCoord0 = ciTexCoord0;
                          }))
          .fragment(CI_GLSL(
                        150,
                        uniform sampler2D uTex0;
                            uniform vec4 uColor;
                            in vec2 TexCoord0;
                            out vec4 oColor;
                            void main(void) {
                              vec4 color = texture2D(uTex0, TexCoord0) * uColor;
                              oColor = color;
                            }))
  );
  scythe_rect_ = ci::gl::Batch::create(ci::geom::Plane(), scythe_material_);
  scythe_material_->uniform("uTex0", scythe_index);
  scythe_material_->uniform( "uColor", color );
}

void Player::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    0,
                    2*(position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y);

  if (glm::length(velocity_) > 0) {
    int cur_frame = (int)std::floor((double)frame_index_ / kFrameSkip);
    material_->uniform("frame", cur_frame);
  } else {
    material_->uniform("frame", 0);
  }

  ci::gl::scale((float)x_scale_ * 0.0625f,1,-0.0625f);
  rect_->draw();
  if (attack_frame_ >= attack_frame_length_) {
    ci::gl::scale((float)x_scale_ * 2.0f, 1, 2.0f);
    scythe_rect_->draw();
  }
}

void Player::Update(float time_scale, const World &world,
                    const InputController &controller) {
  ++frame_index_;
  if (frame_index_ >= kMaxFrames * kFrameSkip) {
    frame_index_ = 0;
  }
  float hdir = (float)(controller.IsKeyPressed(Key::kRight) -
                       controller.IsKeyPressed(Key::kLeft));
  float vdir = (float)(controller.IsKeyPressed(Key::kDown) -
                       controller.IsKeyPressed(Key::kUp));
  vec2 direction(hdir, vdir);
  direction = glm::normalize(direction);
  velocity_ = direction * vec2(speed_);

  /*if (can_attack_ && controller.GetMouseState()) {
    attack_ = true;
    can_attack_ = false;
    attack_frame_ = 0;
  }
  if (attack_) {
    ++attack_frame_;
  }
  if (attack_frame_ > attack_frame_length_ + attack_frame_delay_) {
    attack_ = false;
    can_attack_ = true;
  }*/

  if (velocity_.x > 0) {
    x_scale_ = -1;
  } else if (velocity_.x < 0) {
    x_scale_ = 1;
  }

  vec2 last_position = position_;
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
}

}  // namespace final_project