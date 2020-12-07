//
// Created by Danny on 12/7/2020.
//

#include "actors/splatter_particle.h"
#include "world.h"

namespace final_project {

SplatterParticle::SplatterParticle(vec2 position, glm::vec4 color) :
    Actor(position, vec2(0), Rect(0,0,0,0), Rect(0,0,0,0), 0, 0, 0,
          {false, false, false, false}, ActorType::kNeutral), color_(color){

}

void SplatterParticle::Setup(World &world) {
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
  material_->uniform("uTex0", index);
  material_->uniform("frame", rand() % 3);
  material_->uniform("max_frames", 3);
  material_->uniform( "uColor", color_);
}

void SplatterParticle::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    0,
                    2*(position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y);

  ci::gl::scale(0.0625f,1,-0.0625f);
  rect_->draw();
}

}