//
// Created by Danny on 11/15/2020.
//

#include "actors/player.h"
#include "world.h"

namespace final_project {

World::World() : time_scale_(1) {
  auto player = new Player(kWindowSize / vec2(2));
  actors_.emplace_back(player);
  auto border1 = new Actor(vec2(-50, (int)kWindowSize.y / 2),
                           vec2(0), Rect(-50,
                                         -(int)kWindowSize.y/2 - 50,
                                         50, (int)kWindowSize.y/2 + 50),
                           Rect(0,0,0,0),
                           -1, -1, 0);
  auto border2 = new Actor(vec2((int)kWindowSize.x + 50,
                                (int)kWindowSize.y / 2),
                           vec2(0), Rect(-50,
                                         -(int)kWindowSize.y/2 - 50,
                                         50, (int)kWindowSize.y/2 + 50),
                           Rect(0,0,0,0),
                           -1, -1, 0);
  auto border3 = new Actor(vec2((int)kWindowSize.x / 2, -50),
                           vec2(0), Rect(-(int)kWindowSize.x - 50,
                                         -50,(int)kWindowSize.x + 50,50),
                           Rect(0,0,0,0),
                           -1, -1, 0);
  auto border4 = new Actor(vec2((int)kWindowSize.x / 2,
                                (int)kWindowSize.y + 50),
                           vec2(0), Rect(-(int)kWindowSize.x - 50,
                                         -50,(int)kWindowSize.x + 50,50),
                           Rect(0,0,0,0),
                           -1, -1, 0);
  actors_.emplace_back(border1);
  actors_.emplace_back(border2);
  actors_.emplace_back(border3);
  actors_.emplace_back(border4);
}

void World::Draw() {
  ci::Color8u background_color(100, 100, 100);
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