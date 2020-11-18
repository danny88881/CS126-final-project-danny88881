//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_CINDER_APP_H_
#define FINAL_PROJECT_INCLUDE_CINDER_APP_H_

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "world.h"
#include "input_controller.h"

namespace final_project{

namespace graphics {

class CinderApp : public ci::app::App {
 public:
  CinderApp();

  void update() override;
  void draw() override;

  void keyUp(ci::app::KeyEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

 private:
  World world_;
  InputController controller_;
};

}

}

#endif  // FINAL_PROJECT_INCLUDE_CINDER_APP_H_
