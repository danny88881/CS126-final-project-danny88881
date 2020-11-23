//
// Created by Danny on 11/17/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_INPUT_CONTROLLER_H_
#define FINAL_PROJECT_INCLUDE_INPUT_CONTROLLER_H_

#include "cinder/app/KeyEvent.h"
#include <vector>

namespace final_project {

using std::vector;
using ci::app::KeyEvent;

// needs to be consecutive to be used in vector
enum Key {
  kUp = 0,
  kDown,
  kLeft,
  kRight,

  kLength = 4 // solution proposed on stack overflow - END MARKER
};

class InputController {
 public:
  InputController();

  /**
   * Updates the controller based on a key event
   * @param event the key event to update the controller with
   */
  void KeyPress(KeyEvent event);

  /**
   * Updates the controller based on a key event
   * @param event the key event to update the controller with
   */
  void KeyRelease(KeyEvent event);

  /**
   * Returns whether a key is pressed
   * @param key the key to check the state of
   * @return a boolean representing the state of the key
   */
  bool IsKeyPressed(Key key) const;

  void SetMouseState(bool mouse_state);
  bool GetMouseState() const;
 private:
  vector<bool> key_pressed_;
  vector<int> key_to_event_ {
      KeyEvent::KEY_w,
      KeyEvent::KEY_s,
      KeyEvent::KEY_a,
      KeyEvent::KEY_d,
  }; // not const so key remapping could be a feature
  bool mouse_down_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_INPUT_CONTROLLER_H_
