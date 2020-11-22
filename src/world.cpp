//
// Created by Danny on 11/15/2020.
//

#include "actors/player.h"
#include "actors/mouse.h"
#include "world.h"

namespace final_project {

World::World() : time_scale_(1), texture_map_() {
  auto player = new Player(kWindowSize / vec2(2));
  actors_.emplace_back(player);
  auto mouse = new Mouse();
  actors_.emplace_back(mouse);
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

void World::Setup() {
  camera_.lookAt(glm::vec3( 0, 1, 0 ), glm::vec3( 0 ) );
  for (Actor* actor : actors_) {
    actor->Setup(*this);
  }
}

void World::Draw() {
  ci::gl::setMatrices(camera_);
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

int World::GetTextureIndex(const std::string &sprite_path) const {
  auto iter = texture_map_.find(sprite_path);
  if (iter != texture_map_.end()) {
    return iter->second.second;
  }
  return -1;
}

int World::LoadTexture(const std::string &sprite_path) {
  int existing_index = GetTextureIndex(sprite_path);
  if (existing_index != -1) {
    return texture_map_[sprite_path].second;
  }
  auto img = cinder::loadImage(ci::app::loadAsset(sprite_path));
  auto sprite = ci::gl::Texture2d::create(img);
  int index = texture_map_.size();
  texture_map_.emplace(sprite_path,
                       std::pair<ci::gl::TextureRef, int>(sprite, index));
  sprite->bind(index);
  sprite->setMagFilter(GL_NEAREST);
  sprite->setMinFilter(GL_NEAREST);
  return index;
}

}