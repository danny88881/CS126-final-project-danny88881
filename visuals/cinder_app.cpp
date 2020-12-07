//
// Created by Danny on 11/15/2020.
//

#include "cinder_app.h"

namespace final_project {

namespace graphics {

CinderApp::CinderApp() : world_(), controller_() {
  ci::app::setWindowSize(World::kWindowSize);
  world_.StartGame();
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

void CinderApp::mouseUp(ci::app::MouseEvent event) {
  if (event.isLeft()) {
    controller_.SetMouseState(false);
  }
}

void CinderApp::mouseDown(ci::app::MouseEvent event) {
  if (event.isLeft()) {
    controller_.SetMouseState(true);
  }
}

}

}