//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_

#include "cinder/app/App.h"
#include "input_controller.h"
#include "actor.h"

namespace final_project {

class World;

class Player : public Actor {
 public:
  Player();

  /**
   * Updates the actor based on the passed timescale and a controller
   * @param time_scale the timescale of the world
   * @param controller the player's controller
   */
  virtual void Update(double time_scale, const World &world,
                      const InputController &controller);
  virtual void Draw() const override;

 private:

};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_
