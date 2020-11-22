//
// Created by Danny on 11/15/2020.
//

#include "cinder_app.h"

namespace final_project {

namespace graphics {

CinderApp::CinderApp() : world_(), controller_() {
  ci::app::setWindowSize(World::kWindowSize);
  //hideCursor();
}

void CinderApp::setup() {
  world_.Setup();
}

void CinderApp::update() {
  world_.Update(controller_);
}

void CinderApp::draw() {
  world_.Draw();
}

void CinderApp::keyUp(ci::app::KeyEvent event) {
  controller_.KeyRelease(event);
}

void CinderApp::keyDown(ci::app::KeyEvent event) {
  controller_.KeyPress(event);
}

}

}