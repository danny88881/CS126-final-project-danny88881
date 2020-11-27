//
// Created by Danny on 11/25/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ATTACK_H_
#define FINAL_PROJECT_INCLUDE_ATTACK_H_

#include "actor.h"

namespace final_project {

class World;

enum AttackDirection {
  kUpAttack = 0,
  kDownAttack,
  kLeftAttack,
  kRightAttack,
  kNone
};

class Attack : public Actor {
 public:
  Attack();
  Attack(const Attack &attack, double rotation, vec2 position);
  Attack(Rect hit_box, float speed, ActorType type, float damage,
         std::string sprite_sheet_path, std::string sprite_icon_path,
         int max_frames, int frame_skip, float frame_life, int position_offset,
         vec2 dimension, vector<vec2> active_intervals, bool rotate_sprite);

  virtual void Setup(World &world) override;
  virtual void Update(float time_scale, World &world,
                      const InputController &controller) override;
  virtual void Draw() const override;

  int GetSpriteIconIndex() const;
  int GetPositionOffset() const;

  /**
   * Returns a new instance of this attack class
   * @param rotation the rotation of the instanced class
   * @param position the position of the instanced class
   * @return the new instance
   */
  Attack* GetInstance(double rotation, vec2 position);
 protected:
  double rotation_;
  float damage_;
  std::string sprite_sheet_path_
      = "sprites/weapon/Slash.png";
  std::string sprite_icon_path_
      = "sprites/ui/Sword.png";
  int sprite_icon_index_;
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
  int max_frames_;
  int frame_skip_;
  int frame_index_;
  int position_offset_;
  float frame_life_;
  vec2 dimension_;
  vector<Actor*> hit_actors_;
  vector<vec2> active_intervals_;
  bool rotate_sprite_;

  Rect RotateRect(Rect rect, double angle) const;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ATTACK_H_
