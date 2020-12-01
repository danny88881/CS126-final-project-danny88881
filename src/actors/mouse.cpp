//
// Created by Danny on 11/20/2020.
//

#include "world.h"
#include "actors/mouse.h"

namespace final_project {

Mouse::Mouse() : Actor(vec2(0,0), vec2(0,0), Rect(0,0,0,0),
            Rect(0,0,0,0), -1, -1, 0, {false, false, false, false}, kNeutral) {
}

void Mouse::Setup(World &world) {
  int index = world.LoadTexture(kSpritePath);

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

void Mouse::Update(float time_scale, World &world,
                    const InputController &controller) {
  position_ = cinder::app::getWindow()->getMousePos();
}

void Mouse::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    0.9f,
                    2*(position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y);
  ci::gl::scale(0.0625f,1,-0.0625f);
  rect_->draw();
}

}