//
// Created by Danny on 11/25/2020.
//

#include "attack.h"
#include "world.h"

namespace final_project {

Attack::Attack() : Actor(vec2(0,0), vec2(0,0), Rect(0,0,0,0),
                          Rect(-20,-20,20,20), -1, -1, 0,
                          {false, false, false, false}, ActorType::kNeutral),
      damage_(1), sprite_sheet_path_("sprites/weapon/32slash.png"),
      max_frames_(1), frame_life_(2), frame_index_(0), direction_(kNone) {
}

Attack::Attack(AttackDirection direction) : Attack() {
  direction_ = direction;
}

Attack::Attack(float damage, std::string sprite_sheet_path, int max_frames,
               int frame_life) : Actor() {
  damage_ = damage;
  sprite_sheet_path_ = sprite_sheet_path;
  max_frames_ = max_frames;
  frame_life_ = frame_life;
}

void Attack::Setup(World &world) {
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

void Attack::Update(float time_scale, const World &world,
                    const InputController &controller) {
  ++frame_index_;
  if (frame_index_ >= max_frames_ * frame_skip_) {
    frame_index_ = 0;
  }
  //velocity_ = direction * vec2(speed_);

  position_ += velocity_ * time_scale;

  bool collision_occurred = false;
  for (const Actor *actor : world.GetActors()) {
    if (actor != this && IsCollidingWithHitBox(*actor)) {
      collision_occurred = true;
      break;
    }
  }
}
}