//
// Created by Danny on 11/25/2020.
//

#include "catch2/catch.hpp"
#include "actor.h"
#include "world.h"
#include "input_controller.h"
#include "cinder/gl/gl.h"

using final_project::World;
using final_project::Actor;
using final_project::Rect;
using final_project::InputController;
using glm::vec2;

TEST_CASE("Actor Constructor") {
  SECTION("In specification", "[inspec]") {
    SECTION("Default constructor", "[default]") {
      REQUIRE_NOTHROW(Actor());
    }

    SECTION("Parameterized Constructor", "[param]") {
      REQUIRE_NOTHROW(Actor(vec2(0), vec2(0),
                            Rect(-50, -50, 50, 50), Rect(0,0,0,0),
                            -1, -1, 0, {false, false, false, false}));
    }
  }

  SECTION("Out of specification", "[outspec]") {
    REQUIRE_NOTHROW(Actor(vec2(0), vec2(0),
                          Rect(50, 50, -50, -50), Rect(0,0,0,0),
                          -1, -1, 0, {false, false, false, false}));
  }
}

TEST_CASE("Actor Setup") {
  World world;
  Actor actor(vec2(0), vec2(0),
        Rect(-50, -50, 50, 50), Rect(0,0,0,0),
        -1, -1, 0, {false, false, false, false});
  REQUIRE_NOTHROW(actor.Setup(world));
}

TEST_CASE("Actor Update") {
  World world;
  InputController input_controller;
  SECTION("Time Scale Normal", "[normal time scale]") {
    SECTION("Velocity length zero", "[zero velocity]") {
      Actor actor(vec2(0), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                  -1, -1, 0, {false, false, false, false});
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(0));
      actor.Update(1.0f, world, input_controller);
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(0));
    }

    SECTION("Velocity length nonzero", "[nonzero velocity]") {
      Actor actor(vec2(0), vec2(1, -5), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                  -1, -1, 0, {false, false, false, false});
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(1, -5));
      actor.Update(1.0f, world, input_controller);
      REQUIRE(actor.GetPosition() == vec2(1, -5));
      REQUIRE(actor.GetVelocity() == vec2(1, -5));
    }
  }

  SECTION("Time Scale Not Normal", "[non-normal time scale]") {
    SECTION("Velocity length zero", "[zero velocity]") {
      Actor actor(vec2(0), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                  -1, -1, 0, {false, false, false, false});
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(0));
      actor.Update(0.0f, world, input_controller);
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(0));
    }

    SECTION("Velocity length nonzero", "[nonzero velocity]") {
      Actor actor(vec2(0), vec2(1, -5), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                  -1, -1, 0, {false, false, false, false});
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(1, -5));
      actor.Update(0.0f, world, input_controller);
      REQUIRE(actor.GetPosition() == vec2(0));
      REQUIRE(actor.GetVelocity() == vec2(1, -5));
    }
  }
}

TEST_CASE("Actor Draw") {
  Actor actor(vec2(0), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
              -1, -1, 0, {false, false, false, false});
  REQUIRE_NOTHROW(actor.Draw());
}

TEST_CASE("Actor IsColliding") {
  Actor actor(vec2(0), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
              -1, -1, 0, {true, false, false, false});
  SECTION("No Collision", "[no collision]") {
    Actor actor2(vec2(101), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                 -1, -1, 0, {true, false, false, false});
    REQUIRE_FALSE(actor.IsColliding(actor2));
    REQUIRE_FALSE(actor2.IsColliding(actor));
  }

  SECTION("Collision", "[collision]") {
    Actor actor2(vec2(10), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                 -1, -1, 0, {true, false, false, false});
    REQUIRE(actor.IsColliding(actor2));
    REQUIRE(actor2.IsColliding(actor));
  }

  SECTION("Collision not same layer", "[collision][not same layer]") {
    Actor actor2(vec2(10), vec2(0), Rect(-50, -50, 50, 50), Rect(0, 0, 0, 0),
                 -1, -1, 0, {false, true, false, false});
    REQUIRE_FALSE(actor.IsColliding(actor2));
    REQUIRE_FALSE(actor2.IsColliding(actor));
  }

  SECTION("Collision one inside other", "[collision][inside]") {
    Actor actor2(vec2(0), vec2(0), Rect(-100, -100, 100, 100), Rect(0, 0, 0, 0),
                 -1, -1, 0, {true, false, false, false});
    REQUIRE(actor.IsColliding(actor2));
    REQUIRE(actor2.IsColliding(actor));
  }

  SECTION("Collision edge case", "[collision][edge case][corner misaligned]") {
    Actor actor2(vec2(0), vec2(0), Rect(-100, -10, 100, 10), Rect(0, 0, 0, 0),
                 -1, -1, 0, {true, false, false, false});
    REQUIRE(actor.IsColliding(actor2));
    REQUIRE(actor2.IsColliding(actor));
  }
}