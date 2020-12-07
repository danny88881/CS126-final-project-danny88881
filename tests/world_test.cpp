//
// Created by Danny on 12/6/2020.
//

#include "catch2/catch.hpp"
#include "world.h"

namespace final_project {

TEST_CASE("World Constructor") {
  REQUIRE_NOTHROW(World());
}

// TEST_CASE("World Setup") {
//   World world;
//   world.StartGame();
// }

// Similar segmentation error as attack test case might have something to do
// with opengl. Can't test other methods due to this error.

}