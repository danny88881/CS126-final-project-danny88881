//
// Created by Danny on 12/6/2020.
//

#include "catch2/catch.hpp"
#include "cinder/gl/gl.h"
#include "attack.h"

using final_project::Attack;
using glm::vec2;

TEST_CASE("Attack Constructor") {
  SECTION("Default constructor", "[default]") {
    REQUIRE_NOTHROW(Attack());
  }

  SECTION("Parameterized constructors") {
    SECTION("Copy", "[copy]") {
      REQUIRE_NOTHROW(Attack(Attack(), 0, vec2(0)));
    }

    SECTION("All parameters", "[param]") {

    }
  }
}