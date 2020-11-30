//
// Created by Danny on 11/25/2020.
//

#include "attack.h"
#include "world.h"
#include "cinder/app/App.h"

namespace final_project {

Attack::Attack() : Actor(vec2(0,0), vec2(0,0), Rect(0,0,0,0),
                          Rect(-32,-32,32,32), -1, -1, 0,
                          {false, false, false, false}, ActorType::kPlayer),
      damage_(1), knockback_(3) ,sprite_sheet_path_("sprites/weapon/Slash.png"),
      dimension_(32,32), max_frames_(3), frame_skip_(2), frame_life_(3),
      frame_index_(0), rotation_(0), hit_actors_(), sprite_icon_index_(0),
      position_offset_(24), active_intervals_({vec2(0,3)}),
      rotate_sprite_(true) {
}

Attack::Attack(const Attack &attack, double rotation, vec2 position) {
  frame_index_ = 0;
  position_ = position;
  velocity_ = attack.velocity_;
  collision_ = attack.collision_;
  hit_box_ = attack.hit_box_;
  max_health_ = attack.max_health_;
  health_ = attack.health_;
  speed_ = attack.speed_;
  collision_layers_ = attack.collision_layers_;
  type_ = attack.type_;
  damage_ = attack.damage_;
  knockback_ = attack.knockback_;
  sprite_sheet_path_ = attack.sprite_sheet_path_;
  sprite_icon_path_ = attack.sprite_icon_path_;
  max_frames_ = attack.max_frames_;
  frame_skip_ = attack.frame_skip_;
  frame_life_ = attack.frame_life_;
  rotation_ = rotation;
  hit_actors_ = {};
  hit_box_ = RotateRect(hit_box_, rotation_);
  dimension_ = abs(glm::rotate(attack.dimension_, (float)rotation_));
  active_intervals_ = attack.active_intervals_;
  rotate_sprite_ = attack.rotate_sprite_;
}

Attack::Attack(Rect hit_box, float speed, ActorType type, float damage,
               float knockback, std::string sprite_sheet_path,
               std::string sprite_icon_path, int max_frames, int frame_skip,
               float frame_life, int position_offset, vec2 dimension,
               vector<vec2> active_intervals, bool rotate_sprite)
    : Actor(vec2(0,0), vec2(0,0), Rect(0,0,0,0),
            hit_box, -1, -1, speed,
            {false, false, false, false}, type), damage_(damage),
      knockback_(knockback), sprite_sheet_path_(sprite_sheet_path),
      sprite_icon_path_(sprite_icon_path), max_frames_(max_frames),
      frame_skip_(frame_skip), frame_life_(frame_life),
      position_offset_(position_offset), dimension_(dimension),
      active_intervals_(active_intervals), rotate_sprite_(rotate_sprite) {
}

void Attack::Setup(World &world) {
  sprite_icon_index_ = world.LoadTexture(sprite_icon_path_);
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

void Attack::Update(float time_scale, World &world,
                    const InputController &controller) {
  ++frame_index_;
  if (frame_index_ >= frame_life_ * frame_skip_) {
    world.RemoveActor(this);
    return;
  }
  vec2 direction = vec2(sin(rotation_), cos(rotation_));
  velocity_ = direction * vec2(speed_);

  position_ += velocity_ * time_scale;

  bool in_interval = false;
  for (const vec2 &interval : active_intervals_) {
    if (frame_index_ >= interval.x * frame_skip_
        && frame_index_ <= interval.y * frame_skip_) {
      in_interval = true;
      break;
    }
  }
  if (in_interval) {
    for (Actor *actor : world.GetActors()) {
      auto iter = std::find(hit_actors_.begin(), hit_actors_.end(), actor);
      if (iter != hit_actors_.end()) {
        continue;
      }
      if (actor != this && IsCollidingWithHitBox(*actor)) {
        actor->Damage(damage_);
        vec2 knockback = glm::normalize(actor->GetPosition() - position_)
            * vec2((float)knockback_);
        actor->SetKnockback(knockback);
        hit_actors_.push_back(actor);
      }
    }
  } else {
    hit_actors_.clear();
  }
}

void Attack::Draw() const {
  ci::gl::ScopedModelMatrix scpMtx;
  ci::gl::translate(2*(position_.x - ci::app::getWindowSize().x / 2)
                        /ci::app::getWindowSize().x,
                    0,
                    2*(position_.y - ci::app::getWindowSize().y / 2)
                        /ci::app::getWindowSize().y);

  int cur_frame = (int)std::floor((double)frame_index_ / frame_skip_);
  material_->uniform("frame", cur_frame % (max_frames_));

  ci::gl::scale(0.125f * dimension_.x / 32,1, -0.125f * dimension_.y / 32);
  if (rotate_sprite_) {
    ci::gl::rotate((float)rotation_, glm::vec3(0, 1, 0));
  }
  rect_->draw();
  /*ci::gl::setMatricesWindow(cinder::app::getWindowSize());
  ci::gl::color(1,0,0,1);
  ci::gl::drawLine(glm::vec2(hit_box_.x1_ + position_.x,
                             hit_box_.y1_ + position_.y),
                   glm::vec2(hit_box_.x2_ + position_.x,
                             hit_box_.y2_ + position_.y));*/
}

int Attack::GetSpriteIconIndex() const {
  return sprite_icon_index_;
}

int Attack::GetPositionOffset() const {
  return position_offset_;
}

Rect Attack::RotateRect(Rect rect, double angle) const {
  vec2 point1 = vec2(rect.x1_, rect.y1_);
  point1 = glm::rotate(point1, (float)angle);
  vec2 point2 = vec2(rect.x2_, rect.y2_);
  point2 = glm::rotate(point2, (float)angle);
  float min_x = std::min(point1.x, point2.x);
  float min_y = std::min(point1.y, point2.y);
  float max_x = std::max(point1.x, point2.x);
  float max_y = std::max(point1.y, point2.y);
  return Rect((int)min_x, (int)min_y, (int)max_x, (int)max_y);
}

Attack* Attack::GetInstance(double rotation, vec2 position) {
  return new Attack(*this, rotation, position);
}

}