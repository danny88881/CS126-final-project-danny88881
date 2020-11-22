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
                            uniform vec4 uColor;
                            uniform int frame;
                            in vec2 TexCoord0;
                            out vec4 oColor;
                            void main(void) {
                              oColor = texture( uTex0, TexCoord0 ) * uColor;
                            })));

  rect_ = ci::gl::Batch::create(ci::geom::Plane(), material_);

  ci::ColorAf color( 1,1,1,1 );
  material_->uniform("uTex0", index);
  material_->uniform( "uColor", color );
}

void Player::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    0,
                    2*(position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y);
  ci::gl::scale(0.1f,1,-0.1f);
  rect_->draw();
}

void Player::Update(float time_scale, const vector<Actor *> &actors,
                    const InputController &controller) {
  float hdir = (float)(controller.IsKeyPressed(Key::kRight) -
                       controller.IsKeyPressed(Key::kLeft));
  float vdir = (float)(controller.IsKeyPressed(Key::kDown) -
                       controller.IsKeyPressed(Key::kUp));
  vec2 direction(hdir, vdir);
  direction = glm::normalize(direction);
  velocity_ = direction * vec2(speed_);
  vec2 last_position = position_;
  position_ += velocity_ * time_scale;

  bool collision_occurred = false;
  for (const Actor *actor : actors) {
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