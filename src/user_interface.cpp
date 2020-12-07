//
// Created by Danny on 11/25/2020.
//

#include "user_interface.h"
#include "world.h"
#include "attack.h"

namespace final_project {

const std::string UserInterface::kBoxSpritePath = "sprites/ui/Keybox.png";
const std::string UserInterface::kNoAttackSpritePath = "sprites/ui/Cross.png";

UserInterface::UserInterface() : player_attacks_(), player_attack_count_(),
      box_index_(0), cross_index_(0), points_(0) {
}

void UserInterface::Setup(World &world) {
  font_ = cinder::Font(ci::app::loadAsset("ARCADECLASSIC.TTF"), 24);
  cross_index_ = world.LoadTexture(kNoAttackSpritePath);
  box_index_ = world.LoadTexture(kBoxSpritePath);
  box_material_ = ci::gl::GlslProg::create(
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
                            in vec2 TexCoord0;
                            out vec4 oColor;
                            void main(void) {
                              vec4 color = texture2D(uTex0, TexCoord0) * uColor;
                              oColor = color;
                            }))
  );
  box_rect_ = ci::gl::Batch::create(ci::geom::Plane(), box_material_);
  ci::ColorAf color( 1,1,1,1 );
  box_material_->uniform("uTex0", box_index_);
  box_material_->uniform( "uColor", color );
}

void UserInterface::Draw() {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::scale(0.0625f,1,-0.0625f);
  if (player_attacks_.size() <= 0) {
    return;
  }

  ci::gl::translate(0, 0,-0.75f * 16);
  DrawKeyBox(player_attacks_[AttackDirection::kUpAttack]);
  ci::gl::translate(0, 0,-0.125f * 16);
  DrawKeyBox(player_attacks_[AttackDirection::kDownAttack]);
  ci::gl::translate(-0.125f * 16, 0,0);
  DrawKeyBox(player_attacks_[AttackDirection::kLeftAttack]);
  ci::gl::translate(0.25f * 16, 0,0);
  DrawKeyBox(player_attacks_[AttackDirection::kRightAttack]);

  ci::gl::setMatricesWindow(cinder::app::getWindowSize());
  ci::gl::drawString(std::to_string(points_),
                     vec2(10,10), glm::vec4(1,1,1,1), font_);
  glm::vec4 color = glm::vec4(1,1,1,(float)(0.4 + 0.6 *
      ((player_attack_count_[AttackDirection::kUpAttack]
                       > 0) ? 1 : 0)));
  ci::gl::drawString(std::to_string(
                         player_attack_count_[AttackDirection::kUpAttack]),
                     vec2(245,415), color, font_);
  color.a = (float)(0.4 + 0.6 *
      ((player_attack_count_[AttackDirection::kDownAttack]
                > 0) ? 1 : 0));
  ci::gl::drawString(std::to_string(
                         player_attack_count_[AttackDirection::kDownAttack]),
                     vec2(245,496), color, font_);
  color.a = (float)(0.4 + 0.6 *
      ((player_attack_count_[AttackDirection::kLeftAttack]
                > 0) ? 1 : 0));
  ci::gl::drawString(std::to_string(
                         player_attack_count_[AttackDirection::kLeftAttack]),
                     vec2(190,475), color, font_);
  color.a = (float)(0.4 + 0.6 *
      ((player_attack_count_[AttackDirection::kRightAttack]
                > 0) ? 1 : 0));
  ci::gl::drawString(std::to_string(
                         player_attack_count_[AttackDirection::kRightAttack]),
                     vec2(300,475), color, font_);
}

void UserInterface::DrawKeyBox(Attack *attack) {
  int icon_index = cross_index_;
  ci::ColorAf color(1,1,1,1);
  if (attack == nullptr) {
    color = ci::ColorAf(1,1,1,0.4f);
    icon_index = cross_index_;
  } else {
    color = ci::ColorAf(1,1,1,1);
    icon_index = attack->GetSpriteIconIndex();
  }
  box_material_->uniform("uColor", color);
  box_material_->uniform("uTex0", box_index_);
  box_rect_->draw();
  box_material_->uniform("uTex0", icon_index);
  box_rect_->draw();
}

void UserInterface::Update(World &world) {
  if (world.GetPlayer() != nullptr) {
    player_attacks_ = world.GetPlayer()->GetAttacks();
    player_attack_count_ = world.GetPlayer()->GetAttackCount();
  }
  points_ = world.GetPoints();
}

}