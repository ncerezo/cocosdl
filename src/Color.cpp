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

#include "Color.h"
#include "Framework.h"

namespace cocosdl
{
  static Color _black( (Uint8) 0, 0, 0, 0xff );
  static Color _white( (Uint8)0xff, 0xff, 0xff, 0xff );
  static Color _red( (Uint8) 0xff, 0x00, 0x00, 0xff );
  static Color _green( (Uint8) 0x00, 0xff, 0x00, 0xff );
  static Color _blue( (Uint8) 0x00, 0x00, 0xff, 0xff );
  static Color _yellow( (Uint8) 0xff, 0xff, 0x00, 0xff );

  Color::Color() : _color( { 0, 0, 0, 0xff } )
  {
  }

  Color::Color( const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha ) :
  _color( { red, green, blue, alpha } )
  {
  }

  Color::Color( const float red, const float green, const float blue, const float alpha ) :
  _color( { (Uint8) ( red * 0xff ), (Uint8) ( green * 0xff ), (Uint8) ( blue * 0xff ), (Uint8) ( alpha * 0xff ) } )
  {
  }

  Color::Color( const Uint32 argb ) :
  _color( { (Uint8) ( ( argb & 0xFF0000 ) >> 16 ),
              (Uint8) ( ( argb & 0xFF00 ) >> 8 ),
              (Uint8) ( argb & 0xFF ),
              (Uint8) ( ( argb & 0xFF000000 ) >> 24 )
          }
  )
  {
  }

  Color::Color( const Color &other )
  {
    _color.r = other._color.r;
    _color.g = other._color.g;
    _color.b = other._color.b;
    _color.a = other._color.a;
  }

  Color &Color::operator = ( const Color &color )
  {
    _color.r = color._color.r;
    _color.g = color._color.g;
    _color.b = color._color.b;
    _color.a = color._color.a;
    return *this;
  }

  Color::~Color()
  {

  }

  Color &Color::operator += ( const Color &color )
  {
    _color.r = (Uint8) MIN( 0xff, (int) _color.r + (int) color._color.r );
    _color.g = (Uint8) MIN( 0xff, (int) _color.g + (int) color._color.g );
    _color.b = (Uint8) MIN( 0xff, (int) _color.b + (int) color._color.b );
    _color.a = (Uint8) MIN( 0xff, (int) _color.a + (int) color._color.a );
    return *this;
  }

  Color &Color::operator -= ( const Color &color )
  {
    _color.r = (Uint8) MAX( 0x00, (int) _color.r - (int) color._color.r );
    _color.g = (Uint8) MAX( 0x00, (int) _color.g - (int) color._color.g );
    _color.b = (Uint8) MAX( 0x00, (int) _color.b - (int) color._color.b );
    _color.a = (Uint8) MAX( 0x00, (int) _color.a - (int) color._color.a );
    return *this;
  }

  void Color::setComponents( const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha )
  {
    _color.r = red;
    _color.g = green;
    _color.b = blue;
    _color.a = alpha;
  }

  void Color::setComponents( const float red, const float green, const float blue, const float alpha )
  {
    _color.r = (Uint8) ( red * 0xff );
    _color.g = (Uint8) ( green * 0xff );
    _color.b = (Uint8) ( blue * 0xff );
    _color.a = (Uint8) ( alpha * 0xff );
  }

  void Color::setComponents( const Uint32 argb )
  {
    _color.r = (Uint8) ( ( argb & 0xFF0000 ) >> 16 );
    _color.g = (Uint8) ( ( argb & 0xFF00 ) >> 8 );
    _color.b = (Uint8) ( argb & 0xFF );
    _color.a = (Uint8) ( ( argb & 0xFF000000 ) >> 24 );
  }

  void Color::setRed( const Uint8 red )
  {
    _color.r = red;
  }

  void Color::setGreen( const Uint8 green )
  {
    _color.g = green;
  }

  void Color::setBlue( const Uint8 blue )
  {
    _color.b = blue;
  }

  void Color::setAlpha( const Uint8 alpha )
  {
    _color.a = alpha;
  }

  void Color::setRed( const float red )
  {
    _color.r = (Uint8) ( red * 0xff );
  }

  void Color::setGreen( const float green )
  {
    _color.g = (Uint8) ( green * 0xff );
  }

  void Color::setBlue( const float blue )
  {
    _color.b = (Uint8) ( blue * 0xff );
  }

  void Color::setAlpha( const float alpha )
  {
    _color.a = (Uint8) ( alpha * 0xff );
  }

  Color const &Color::black()
  {
    return _black;
  }

  Color const &Color::white()
  {
    return _white;
  }

  Color const &Color::red()
  {
    return _red;
  }

  Color const &Color::green()
  {
    return _green;
  }

  Color const &Color::blue()
  {
    return _blue;
  }

  Color const &Color::yellow()
  {
    return _yellow;
  }

}
