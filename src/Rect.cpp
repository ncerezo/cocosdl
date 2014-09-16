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

#include "Rect.h"
#include "Point.h"

namespace cocosdl {

  Rect::Rect()
  {
    _rect.x = _rect.y = _rect.w = _rect.h = 0;
  }

  Rect::Rect( const int x, const int y, const int width, const int height )
  {
    _rect.x = x;
    _rect.y = y;
    _rect.w = width;
    _rect.h = height;
  }

  Rect::Rect( const Point &origin, const int width, const int height )
  {
    _rect.x = origin.getX();
    _rect.y = origin.getY();
    _rect.w = width;
    _rect.h = height;
  }

  Rect::~Rect()
  {
  }

  bool Rect::isPointInside( const int x, const int y ) const
  {
    SDL_Point p = { x, y };
    return SDL_PointInRect( &p, &_rect );
  }

  bool Rect::isPointInside( const Point &point ) const
  {
    return SDL_PointInRect( &point.get_SDL_Point(), &_rect );
  }

  Rect &Rect::operator = ( const Rect &other )
  {
    _rect = other._rect;
    return *this;
  }


  void Rect::setOrigin( const int x, const int y )
  {
    _rect.x = x;
    _rect.y = y;
  }

  void Rect::setOrigin( const Point &origin )
  {
    _rect.x = origin.getX();
    _rect.y = origin.getY();
  }

  void Rect::setX( const int x )
  {
    _rect.x = x;
  }

  void Rect::setY( const int y )
  {
    _rect.y = y;
  }

  void Rect::setWidth( const int width )
  {
    _rect.w = width;
  }

  void Rect::setHeight( const int height )
  {
    _rect.h = height;
  }

  void Rect::setDimension( const int width, const int height )
  {
    _rect.w = width;
    _rect.h = height;
  }
}
