//
// Created by Danny on 12/6/2020.
//

#include "catch2/catch.hpp"
#include "cinder/gl/gl.h"
#include "attack.h"
#include "world.h"

namespace final_project {

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
      REQUIRE_NOTHROW(Attack(Rect(-24, -96, 24, 64), 0, ActorType::kPlayer,
                             1.5f, 7, "sprites/weapon/Spear.png",
                             "sprites/ui/Spear.png", 3, 3, 3, 64, vec2(32, 64),
                             {vec2(0, 3)}, true));
    }
  }
}

TEST_CASE("Attack GetInstance") {
  Attack attack1;
  Attack* attack2 = attack1.GetInstance(0, vec2(0));
  REQUIRE(attack2 != nullptr);
  delete attack2;
}

// error when trying to test setup, update, or draw due to texture opengl
// texture loading. Same error for other classes that use textures

}