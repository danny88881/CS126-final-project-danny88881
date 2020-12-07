//
// Created by Danny on 11/25/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_USER_INTERFACE_H_
#define FINAL_PROJECT_INCLUDE_USER_INTERFACE_H_

#include "actors/player.h"
#include "cinder/gl/gl.h"

namespace final_project {

class UserInterface {
 public:
  UserInterface();

  virtual void Setup(World &world);
  virtual void Update(World &world);
  virtual void Draw();

 private:
  static const std::string kBoxSpritePath;
  static const std::string kNoAttackSpritePath;
  int box_index_;
  int cross_index_;
  cinder::Font font_;
  ci::gl::BatchRef box_rect_;
  ci::gl::GlslProgRef box_material_;
  vector<Attack*> player_attacks_;
  vector<int> player_attack_count_;
  int points_;
  bool player_dead_;

  void DrawKeyBox(Attack* attack);
};

}

#endif  // FINAL_PROJECT_INCLUDE_USER_INTERFACE_H_
