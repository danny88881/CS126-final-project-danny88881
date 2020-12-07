//
// Created by Danny on 12/6/2020.
//

#include "catch2/catch.hpp"
#include "user_interface.h"

namespace final_project {

TEST_CASE("User Interface Constructor") {
  REQUIRE_NOTHROW(UserInterface());
}

}