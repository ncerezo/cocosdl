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

#ifndef __Point_H_
#define __Point_H_

#include <SDL2/SDL_rect.h>

namespace cocosdl {

  class Point
  {
  public:
    Point();
    Point( const int x, const int y );
    virtual ~Point();

    const int getX() const {
      return _point.x;
    }

    const int getY() const {
      return _point.y;
    }

    const SDL_Point &get_SDL_Point() const
    {
      return _point;
    }

    void setLocation( const int x, const int y )
    {
      _point.x = x;
      _point.y = y;
    }

    void setX( const int x ) {
      _point.x = x;
    }

    void setY( const int y ) {
      _point.y = y;
    }

  private:
    SDL_Point _point;

  };
}

#endif //__Point_H_
