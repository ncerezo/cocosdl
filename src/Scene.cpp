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

#include "Scene.h"
#include "Game.h"
#include "Button.h"

namespace cocosdl {

  const double SWIPE_MIN_SPEED = 0.015;
  const unsigned SWIPE_MAX_AXIS_DELTA = 20;

  Scene::Scene() : Node(), _xDelta( 0 ), _yDelta( 0 ), _swipeStart( 0 ), _button( NULL ), _swipeStatus( SceneSwipeNone )
  {
    Rect rect = Game::getInstance()->getWindowRect();
    setClipping( true );
    setDimension( rect.getWidth(), rect.getHeight() );
    setPosition( rect.getWidth() / 2, rect.getHeight() / 2 );
  }

  Scene::Scene( const Scene &other ) :
  Node( other ),
  _xDelta( other._xDelta ),
  _yDelta( other._yDelta ),
  _swipeStart( 0 ),
  _button( NULL ),
  _swipeStatus( SceneSwipeNone )
  {
    setDimension( other.getWidth(), other.getHeight() );
    setPosition( other.getX(), other.getY() );
    setClipping( true );
  }

  Scene::~Scene()
  {
  }


  Scene &Scene::operator = ( const Scene &other )
  {
    Node::operator=( other );
    _xDelta = other._xDelta;
    _yDelta = other._yDelta;
    _swipeStart = 0;
    _swipeStatus = SceneSwipeNone;
    _button = NULL;
    return *this;
  }


  Node *Scene::copy() const
  {
    return new Scene( *this );
  }

  void Scene::handleEvent( const SDL_Event &event )
  {
    switch( event.type )
    {
      case SDL_MOUSEBUTTONDOWN:
        mouseDown( event );
        break;

      case SDL_MOUSEBUTTONUP:
        mouseUp( event );
        break;

      case SDL_MOUSEMOTION:
        mouseMotion( event );
        break;

        // ToDo: implement finger motion

  //        case SDL_FINGERDOWN:
  //            break;
  //
  //        case SDL_FINGERUP:
  //            break;
  //
  //        case SDL_FINGERMOTION:
  //            break;

      default:
        break;
    }
  }

  void Scene::update( long long currentTimeMillis )
  {

  }

  void Scene::mouseDown( const SDL_Event &event )
  {
    Rect destinationRect;
    getDestinationRect( destinationRect );
    _button = dynamic_cast<Button *>( getChildAtPoint( event.button.x, event.button.y ) );
    if( _button )
    {
      _button->toggle();
      if( _button->getButtonType() == ButtonTypeToggle )
      {
        // toggle buttons do not get trapped
        _button = NULL;
      }
    }
    else
    {
      _swipeStart = Game::getInstance()->currentTimeMillis();
      _swipeStatus = SceneSwipeDetecting;
      _xDelta = _yDelta = 0;
      _downEvent = event;
      OnMouseDown( event );
    }
  }

  void Scene::mouseUp( const SDL_Event &event )
  {
    if( _button )
    {
      _button->release( _button->isPointInside( event.button.x, event.button.y ) );
      _button = NULL;
    }
    else
    {
      if( _swipeStatus == SceneSwipeDetecting )
      {
        detectSwipe( event );
        OnMouseUp( event, _swipeStatus > SceneSwipeDetecting );
      }
      else
      {
        OnMouseUp( event, false );
      }
      _swipeStatus = SceneSwipeNone;
    }
  }

  void Scene::mouseMotion( const SDL_Event &event )
  {
    if( _button )
    {
      if( _button->isPointInside( event.motion.x, event.motion.y ) )
      {
        _button->press();
      }
      else
      {
        _button->release( false );
      }
    }
    else
    {
      if( _swipeStart != 0 )
      {
        _xDelta += event.motion.xrel;
        _yDelta += event.motion.yrel;
      }
      detectSwipe( event );
      OnMouseMotion( event );
    }
  }


  void Scene::detectSwipe( const SDL_Event &event )
  {
    if( _swipeStatus == SceneSwipeDetecting )
    {
      long long elapsed = Game::getInstance()->currentTimeMillis() - _swipeStart;
      if( elapsed > 0 )
      {
        double xSpeed = fabs( (double) _xDelta / (double) elapsed );
        double ySpeed = fabs( (double) _yDelta / (double) elapsed );
        _swipeStart = 0;
        if( xSpeed > SWIPE_MIN_SPEED && abs( _yDelta ) < SWIPE_MAX_AXIS_DELTA )
        {
          if( _xDelta > 0 )
          {
            _swipeStatus = SceneSwipeRight;
            OnSwipeRight( _downEvent, event, xSpeed, _xDelta );
          }
          else
          {
            _swipeStatus = SceneSwipeLeft;
            OnSwipeLeft( _downEvent, event, xSpeed, _xDelta );
          }
        }
        else
        {
                if( ySpeed > SWIPE_MIN_SPEED && abs( _xDelta ) < SWIPE_MAX_AXIS_DELTA )
                {
                  if( _yDelta > 0 )
                  {
                    _swipeStatus = SceneSwipeDown;
                    OnSwipeDown( _downEvent, event, ySpeed, _yDelta );
                  }
                  else
                  {
                    _swipeStatus = SceneSwipeUp;
                    OnSwipeUp( _downEvent, event, ySpeed, _yDelta );
                  }
                }
        }
      }
    }
  }

  void Scene::OnMouseDown( const SDL_Event &event )
  {
  }

  void Scene::OnMouseUp( const SDL_Event &event, const bool swipe )
  {
  }

  void Scene::OnMouseMotion( const SDL_Event &event )
  {
  }

  void Scene::OnSwipeRight( const SDL_Event downEvent, const SDL_Event &upEvent, const double speed, const int delta )
  {
  }

  void Scene::OnSwipeLeft( const SDL_Event downEvent, const SDL_Event &upEvent, const double speed, const int delta )
  {
  }

  void Scene::OnSwipeUp( const SDL_Event downEvent, const SDL_Event &upEvent, const double speed, const int delta )
  {
  }

  void Scene::OnSwipeDown( const SDL_Event downEvent, const SDL_Event &upEvent, const double speed, const int delta )
  {
  }

}
