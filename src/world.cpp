//
// Created by Danny on 11/15/2020.
//

#include "actors/player.h"
#include "actors/mouse.h"
#include "world.h"

namespace final_project {

World::World() : time_scale_(1), texture_map_() {
  auto player = new Player(kWindowSize / vec2(2) + vec2(0, 100));
  AddActor(player);
  auto border1 = new Actor(vec2(-50, (int)kWindowSize.y / 2),
                           vec2(0), Rect(-50,
                                         -(int)kWindowSize.y/2 - 50,
                                         50, (int)kWindowSize.y/2 + 50),
                           Rect(0,0,0,0),
                           -1, -1, 0, {true, false, false, false}, kNeutral);
  auto border2 = new Actor(vec2((int)kWindowSize.x + 50,
                                (int)kWindowSize.y / 2),
                           vec2(0), Rect(-50,
                                         -(int)kWindowSize.y/2 - 50,
                                         50, (int)kWindowSize.y/2 + 50),
                           Rect(0,0,0,0),
                           -1, -1, 0, {true, false, false, false}, kNeutral);
  auto border3 = new Actor(vec2((int)kWindowSize.x / 2, -50),
                           vec2(0), Rect(-(int)kWindowSize.x - 50,
                                         -50,(int)kWindowSize.x + 50,50),
                           Rect(0,0,0,0),
                           -1, -1, 0, {true, false, false, false}, kNeutral);
  auto border4 = new Actor(vec2((int)kWindowSize.x / 2,
                                (int)kWindowSize.y + 50),
                           vec2(0), Rect(-(int)kWindowSize.x - 50,
                                         -50,(int)kWindowSize.x + 50,50),
                           Rect(0,0,0,0),
                           -1, -1, 0, {true, false, false, false}, kNeutral);
  AddActor(border1);
  AddActor(border2);
  AddActor(border3);
  AddActor(border4);
}

void World::Setup() {
  camera_.lookAt(glm::vec3( 0, 100, 0 ), glm::vec3( 0 ) );
  for (Actor* actor : actors_) {
    actor->Setup(*this);
  }

  int index = LoadTexture(kFloorSpritePath);
  floor_material_ = ci::gl::GlslProg::create(
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
                              vec4 color = texture2D(uTex0, TexCoord0)
                                  * uColor;
                              oColor = color;
                            }))
  );
  floor_rect_ = ci::gl::Batch::create(ci::geom::Plane(), floor_material_);
  ci::ColorAf color( 1,1,1,1 );
  floor_material_->uniform("uTex0", index);
  floor_material_->uniform( "uColor", color );
}

void World::Draw() {
  ci::gl::setMatrices(camera_);
  ci::Color8u background_color(100, 100, 100);
  ci::gl::clear(background_color);

  ci::gl::pushModelMatrix();
  ci::gl::translate(0, -10.0f, 0);
  ci::gl::scale(1, 1, -1);
  floor_rect_->draw();
  ci::gl::popModelMatrix();

  for (const Actor* actor : actors_) {
    actor->Draw();
  }
}

void World::Update(const InputController &controller) {
  for (size_t index = 0; index < actors_.size(); ++index) {
    actors_[index]->Update(time_scale_, *this, controller);
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

void World::AddActor(Actor *actor) {
  actor->Setup(*this);
  actors_.push_back(actor);
}

void World::QueueRemoval(Actor *actor) {

}

void World::RemoveActor(Actor *actor) {
  for (size_t index = 0; index < actors_.size(); ++index) {
    if (actors_[index] == actor) {
      delete actor;
      actors_.erase(actors_.begin() + index);
      break;
    }
  }
}

vector<Actor*> World::GetActors() const {
  return vector<Actor*>(actors_);
}

}