//
// Created by Danny on 11/30/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_ENEMY_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_ENEMY_H_

#include "actor.h"

namespace final_project {

class Enemy : public Actor {
 public:
  Enemy(std::string sprite_sheet_path, int max_frames, int frame_skip,
        vec2 position, vec2 velocity, Rect collision, Rect hit_box,
        double max_health, double health, float speed, glm::vec4 modulate);

  virtual void Setup(World &world) override;
  virtual void Draw() const override;

 protected:
  std::string sprite_sheet_path_;
  int max_frames_;
  int frame_skip_;
  int frame_index_;
  int x_scale_;
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
  glm::vec4 modulate_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_ENEMY_H_
