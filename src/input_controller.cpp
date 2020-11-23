//
// Created by Danny on 11/17/2020.
//

#include "input_controller.h"

namespace final_project {

InputController::InputController() : key_pressed_((int)Key::kLength,false),
      mouse_down_(false) {}

void InputController::KeyPress(KeyEvent event) {
  // not using switch case since key_to_event_ is dynamic
  for (int index = 0; index < Key::kLength; ++index) {
    if (key_to_event_[index] == event.getCode()) {
      key_pressed_[index] = true;
      return;
    }
  }
}

void InputController::KeyRelease(KeyEvent event) {
  // not using switch case since key_to_event_ is dynamic
  for (int index = 0; index < Key::kLength; ++index) {
    if (key_to_event_[index] == event.getCode()) {
      key_pressed_[index] = false;
      return;
    }
  }
}

bool InputController::IsKeyPressed(Key key) const {
  return key_pressed_[key];
}

void InputController::SetMouseState(bool mouse_state) {
  mouse_down_ = mouse_state;
}

bool InputController::GetMouseState() const {
  return mouse_down_;
}

}