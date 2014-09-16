/*
   Copyright (c) 2014 Narciso Cerezo. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <CocosDL/Game.h>
#include <CocosDL/Button.h>
#include <CocosDL/Log.h>
#include <CocosDL/Label.h>
#include "settings.h"
#include "MainScene.h"

using namespace cocosdl;

int main(int argc, const char * argv[])
{
  if( Game::init( "CocosDLTest", 100, 100, 640, 1136 ) ) {
    Game *game = Game::getInstance();
    bool initOk = true;
    if( !game->loadMusic( "menu" ) ) {
      Log::error() << "Can't load menu music";
      initOk = false;
    }
    if( !game->loadSound( "hit" ) ) {
      Log::error() << "Can't load sound effect (hit)";
      initOk = false;
    }
    if( !game->loadSound( "blop" ) ) {
      Log::error() << "Can't load sound effect (blop)";
      initOk = false;
    }
    if( !game->loadSound( "bomb" ) ) {
      Log::error() << "Can't load sound effect (bomb)";
      initOk = false;
    }
    if( !game->loadSound( "click" ) ) {
      Log::error() << "Can't load sound effect (click)";
      initOk = false;
    }

    if( initOk ) {
      Button::setSoundEffect( "click" );

      Label::setDefaultFont( DEFAULT_FONT );
      Label::setDefaultFontSize( DEFAULT_FONT_SIZE );
      Label::setDefaultColor( DEFAULT_LABEL_COLOR );

      game->playBackgroundMusic( "menu" );

      MainScene mainScene;
      game->setScene( &mainScene );
      game->run();
    }
  }

  Game::quit();

  return 0;}

