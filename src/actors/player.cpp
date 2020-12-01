//
// Created by Danny on 11/15/2020.
//

#include "cinder/gl/gl.h"
#include "world.h"
#include "actors/player.h"

namespace final_project {

using glm::vec2;

Player::Player() : Actor(vec2(0,0), vec2(0,0), Rect(-20,-20,20,20),
                         Rect(-20,-20,20,20), 3, 3, 2,
            {true, false, false, false}, ActorType::kPlayer),
      frame_index_(0), x_scale_(1),
      attack_direction_(AttackDirection::kNone),
      attack_frame_length_(12), attack_frame_(12),
      can_attack_(true), attack_frame_delay_(12) {
  attacks_ = {nullptr, nullptr, nullptr, nullptr};
  auto attack = new Attack();
  attacks_[AttackDirection::kUpAttack] = attack;
  auto attack2 = new Attack(Rect(-16, -64, 16, 48), 0, ActorType::kPlayer, 1.5f,
                            4,
                            "sprites/weapon/Spear.png", "sprites/ui/Spear.png",
                            3, 3, 3, 64, vec2(32, 64), {vec2(0, 3)}, true);
  attacks_[AttackDirection::kRightAttack] = attack2;
  auto attack3 = new Attack(Rect(-64, -64, 64, 64), 0, ActorType::kPlayer, 0.6f,
                            7,
                            "sprites/weapon/Magic.png", "sprites/ui/Magic.png",
                            6, 3, 6, 84, vec2(64, 64), {vec2(3,5)}, false);
  attacks_[AttackDirection::kDownAttack] = attack3;
  auto attack4 = new Attack(Rect(-16, -16, 16, 16), 12, ActorType::kPlayer, 2.0f,
                            2,
                            "sprites/weapon/Arrow.png", "sprites/ui/Arrow.png",
                            4, 2, 24, 24, vec2(16, 16), {vec2(0,100)}, true);
  attacks_[AttackDirection::kLeftAttack] = attack4;
}

Player::Player(vec2 position) : Player() {
  position_ = position;
}

Player::~Player() {
  for (Attack* attack : attacks_) {
    delete attack;
  }
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

  for (Attack* attack : attacks_) {
    if (attack != nullptr) {
      attack->Setup(world);
    }
  }
}

void Player::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    (position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y,
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
  //ci::gl::setMatricesWindow(cinder::app::getWindowSize());
  //ci::gl::color(1,0,0,1);
  //ci::gl::drawLine(glm::vec2(hit_box_.x1_ + position_.x,hit_box_.y1_ + position_.y),
  //                 glm::vec2(hit_box_.x2_ + position_.x,hit_box_.y2_ + position_.y));
}

void Player::Update(float time_scale, World &world,
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
  if (glm::length(knockback_velocity_) >= 1) {
    velocity_ = knockback_velocity_;
    knockback_velocity_ *= 0.8;
  }

  if (controller.IsKeyPressed(Key::kAttackUp)) {
    AttackAtDirection(AttackDirection::kUpAttack, world);
  } else if (controller.IsKeyPressed(Key::kAttackDown)) {
    AttackAtDirection(AttackDirection::kDownAttack, world);
  } else if (controller.IsKeyPressed(Key::kAttackLeft)) {
    AttackAtDirection(AttackDirection::kLeftAttack, world);
  } else if (controller.IsKeyPressed(Key::kAttackRight)) {
    AttackAtDirection(AttackDirection::kRightAttack, world);
  }
  if (attack_direction_ != AttackDirection::kNone) {
    ++attack_frame_;
  }
  if (attack_frame_ > attack_frame_length_ + attack_frame_delay_) {
    attack_direction_ = AttackDirection::kNone;
    can_attack_ = true;
  }

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

void Player::Damage(double damage) {
  health_ -= damage;
}

void Player::AttackAtDirection(AttackDirection attack_direction, World &world) {
  if (attack_direction == kNone || attacks_[attack_direction] == nullptr) {
    return;
  }
  if (can_attack_) {
    attack_direction_ = attack_direction;
    can_attack_ = false;
    attack_frame_ = 0;
    vec2 dir = vec2(0,0);
    double rotation = 0;
    switch (attack_direction) {
      case AttackDirection::kUpAttack:
        dir = vec2(0, -1);
        rotation = 0;
        break;
      case AttackDirection::kDownAttack:
        dir = vec2(0, 1);
        rotation = M_PI;
        break;
      case AttackDirection::kLeftAttack:
        dir = vec2(-1, 0);
        rotation = -M_PI/2.0;
        break;
      case AttackDirection::kRightAttack:
        dir = vec2(1, 0);
        rotation = M_PI/2.0;
        break;
    }
    Attack* attack = attacks_[attack_direction]->GetInstance(rotation,
                                position_ + dir
    * vec2((float)attacks_[attack_direction]->GetPositionOffset()));
    world.AddActor(attack);
  }
}

vector<Attack*> Player::GetAttacks() const {
  return vector<Attack*>(attacks_);
}

}  // namespace final_project