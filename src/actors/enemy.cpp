//
// Created by Danny on 11/30/2020.
//

#include "world.h"
#include "actors/enemy.h"

namespace final_project {

Enemy::Enemy(std::string sprite_sheet_path, int max_frames, int frame_skip,
             vec2 position, vec2 velocity, Rect collision, Rect hit_box,
             double max_health, double health, float speed)
    : sprite_sheet_path_(sprite_sheet_path), max_frames_(max_frames),
      frame_skip_(frame_skip), frame_index_(0), x_scale_(1),
      Actor(position, velocity, collision, hit_box, max_health, health, speed,
            {false, true, false, false}, ActorType::kEnemy) {
}

void Enemy::Setup(World &world) {
  int index = world.LoadTexture(sprite_sheet_path_);
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
  material_->uniform("max_frames", max_frames_);
  material_->uniform( "uColor", color );
}

void Enemy::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    (position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y,
                    2*(position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y);

  int cur_frame = (int)std::floor((double)frame_index_ / frame_skip_);
  material_->uniform("frame", cur_frame);


  ci::gl::scale((float)x_scale_ * 0.0625f,1,-0.0625f);
  rect_->draw();
  //ci::gl::setMatricesWindow(cinder::app::getWindowSize());
  //ci::gl::color(1,0,0,1);
  //ci::gl::drawLine(glm::vec2(hit_box_.x1_ + position_.x,hit_box_.y1_ + position_.y),
  //                 glm::vec2(hit_box_.x2_ + position_.x,hit_box_.y2_ + position_.y));
}
}