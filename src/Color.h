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

#ifndef __Color_H_
#define __Color_H_

#include <SDL2/SDL.h>

namespace cocosdl
{
  class Color
  {

  public:

    static Color const &black();
    static Color const &white();
    static Color const &red();
    static Color const &green();
    static Color const &blue();
    static Color const &yellow();

    Color();

    Color( const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha );

    Color( const float red, const float green, const float blue, const float alpha );

    Color( const Uint32 argb );

    Color( const Color &other );

    virtual ~Color();

    const SDL_Color &getSDL_Color() const
    {
      return _color;
    }

    Color &operator = ( const Color &color );

    Color &operator += ( const Color &color );

    Color &operator -= ( const Color &color );

    void setComponents( const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha );

    void setComponents( const float red, const float green, const float blue, const float alpha );

    void setComponents( const Uint32 argb );

    void setRed( const Uint8 red );

    void setGreen( const Uint8 red );

    void setBlue( const Uint8 red );

    void setAlpha( const Uint8 red );

    void setRed( const float red );

    void setGreen( const float red );

    void setBlue( const float red );

    void setAlpha( const float red );

    const Uint8 getRed() const
    {
      return _color.r;
    }

    const Uint8 getGreen() const
    {
      return _color.g;
    }

    const Uint8 getBlue() const
    {
      return _color.b;
    }

    const Uint8 getAlpha() const
    {
      return _color.a;
    }

    const float getRedF() const
    {
      return (float) _color.r / (float) 0xFF;
    }

    const float getGreenF() const
    {
      return (float) _color.g / (float) 0xFF;
    }

    const float getBlueF() const
    {
      return (float) _color.b / (float) 0xFF;
    }

    const float getAlphaF() const
    {
      return (float) _color.a / (float) 0xFF;
    }

  private:
    SDL_Color _color;
  };
}

#endif //__Color_H_
