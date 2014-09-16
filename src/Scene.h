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

#ifndef __Scene_H_
#define __Scene_H_

#include "Node.h"
#include <SDL2/SDL.h>

namespace cocosdl {

  class Button;

  enum SceneSwipeStatus
  {
    SceneSwipeNone, SceneSwipeDetecting, SceneSwipeUp, SceneSwipeDown, SceneSwipeLeft, SceneSwipeRight
  };

  /**
   * The scene is a special subclass of node, it is the root node for a given scene containing other nodes.<br/>
   * The scene also takes care of handling the basic events from the underlying framework, performing button touch/mouse
   * capture and swipe detection.<br/>
   * A scene has a special method called update, which is called from the Game main loop, so it can update it's status
   * responding to user input and game mechanics.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Scene : public Node
  {

  public:
    Scene();

    Scene( const Scene &other );

    virtual ~Scene();

    Scene &operator = ( const Scene &other );

    /**
     * Handles an event from the underlying framework.
     */
    virtual void handleEvent( const SDL_Event &event );

    /**
     * Update the scene.
     *
     * @param currentTimeMillis the system current time in milliseconds
     */
    virtual void update( long long currentTimeMillis );

    /**
     * Create a copy of the object with the same class and deep copied properties.
     *
     * @return a new node deep copied from this one with the same class
     */
    virtual Node *copy() const;

  protected:
    /**
     * Called when the mouse is pressed.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param event the mouse event
     */
    virtual void OnMouseDown( const SDL_Event &event );

    /**
     * Called when the mouse is released.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param event the mouse event
     * @param event if a swipe has been detected between the mouse being pressed and it being released
     */
    virtual void OnMouseUp( const SDL_Event &event, const bool swipe );

    /**
     * Called when the mouse is moved.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param event the mouse event
     */
    virtual void OnMouseMotion( const SDL_Event &event );

    /**
     * Called when a right swipe movement is detected.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param downEvent the mouse down event
     * @param event the mouse motion/up event
     * @param speed the speed (pixels per millisecond)
     * @param delta amount of space in pixels from the mouse down to the swipe detection
     */
    virtual void OnSwipeRight( const SDL_Event downEvent, const SDL_Event &event, const double speed, const int delta );

    /**
     * Called when a left swipe movement is detected.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param downEvent the mouse down event
     * @param event the mouse motion/up event
     * @param speed the speed (pixels per millisecond)
     * @param delta amount of space in pixels from the mouse down to the swipe detection
     */
    virtual void OnSwipeLeft( const SDL_Event downEvent, const SDL_Event &event, const double speed, const int delta );

    /**
     * Called when a up swipe movement is detected.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param downEvent the mouse down event
     * @param event the mouse motion/up event
     * @param speed the speed (pixels per millisecond)
     * @param delta amount of space in pixels from the mouse down to the swipe detection
     */
    virtual void OnSwipeUp( const SDL_Event downEvent, const SDL_Event &event, const double speed, const int delta );

    /**
     * Called when a down swipe movement is detected.<br/>
     * To be overridden by subclasses when needed. Empty implementation.
     *
     * @param downEvent the mouse down event
     * @param event the mouse motion/up event
     * @param speed the speed (pixels per millisecond)
     * @param delta amount of space in pixels from the mouse down to the swipe detection
     */
    virtual void OnSwipeDown( const SDL_Event downEvent, const SDL_Event &event, const double speed, const int delta );

  private:
    int               _xDelta;
    int               _yDelta;
    long long         _swipeStart;
    SDL_Event         _downEvent;
    Button            *_button;
    SceneSwipeStatus  _swipeStatus;

    void mouseDown( const SDL_Event &event );

    void mouseUp( const SDL_Event &event );

    void mouseMotion( const SDL_Event &event );

    void detectSwipe( const SDL_Event &event );
  };

}

#endif //__Scene_H_
