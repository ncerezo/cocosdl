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

#ifndef __Rect_H_
#define __Rect_H_

#include <SDL2/SDL_rect.h>

namespace cocosdl {

  class Point;

  class Rect
  {
  public:
    Rect();
    Rect( const int x, const int y, const int width, const int height );
    Rect( const Point& origin, const int width, const int height );
    virtual ~Rect();

    Rect& operator=( const Rect& other );

    void setOrigin( const int x, const int y );
    void setOrigin( const Point& origin );
    void setDimension( const int width, const int height );
    void setX( const int x );
    void setY( const int y );
    void setWidth( const int width );
    void setHeight( const int height );

    int getWidth() const
    {
      return _rect.w;
    }

    int getHeight() const
    {
      return _rect.h;
    }

    int getX() const
    {
      return _rect.x;
    }

    int getY() const
    {
      return _rect.y;
    }

    bool isPointInside( const int x, const int y ) const;
    bool isPointInside( const Point &point ) const;

    const SDL_Rect &get_SDL_Rect() const
    {
      return _rect;
    }

  private:
    SDL_Rect  _rect;

  };

}


#endif //__Rect_H_
