//
// Created by Danny on 12/6/2020.
//

#include "catch2/catch.hpp"
#include "input_controller.h"

namespace final_project {

TEST_CASE("Input Controller Constructor") {
  REQUIRE_NOTHROW(InputController());
}

TEST_CASE("Input Controller Key") {
  InputController input_controller;
  SECTION("KeyPressed", "[pressed]") {
    REQUIRE_NOTHROW(input_controller.KeyPress(KeyEvent()));
  }
  SECTION("KeyReleased", "[release]") {
    REQUIRE_NOTHROW(input_controller.KeyRelease(KeyEvent()));
  }
  SECTION("IsKeyPressed", "[check]") {
    REQUIRE_FALSE(input_controller.IsKeyPressed(Key::kAttackLeft));
  }
}

// mouse is basically a setter and getter

}