//
// Created by Danny on 11/15/2020.
//

#include "cinder_app.h"

using final_project::graphics::CinderApp;

void prepareSettings(CinderApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(CinderApp, ci::app::RendererGl, prepareSettings);