//
// Created by Danny on 11/15/2020.
//

#include "actors/player.h"
#include "world.h"

namespace final_project {

World::World() {
  auto player = new Player();
  actors_.emplace_back(player);
}

void World::Draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  for (const Actor* actor : actors_) {
    actor->Draw();
  }
}

void World::Update(const InputController &controller) {
  for (Actor* actor : actors_) {
    actor->Update(time_scale_, actors_, controller);
  }
}

}