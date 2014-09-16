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

#include "Label.h"
#include "Game.h"
#include "Texture.h"
#include "Renderer.h"

using namespace std;

namespace cocosdl {

  string Label::_defaultFont = "";
  int Label::_defaultFontSize = 30;
  Color Label::_defaultColor = Color::white();

  Label::Label( const string &text ) :
  _text( text ),
  _font( NULL ),
  _color( _defaultColor ),
  _fontName( _defaultFont ),
  _fontSize( _defaultFontSize ),
  _initialFontSize( _defaultFontSize )
  {
    setText( text );
    setFont( _defaultFont, _defaultFontSize );
  }

  Label::Label( const string &fontName, const int fontSize, const string &text ) :
  _text( text ),
  _font( NULL ),
  _color( _defaultColor ),
  _fontName( fontName ),
  _fontSize( fontSize ),
  _initialFontSize( fontSize )
  {
    _color = _defaultColor;
    setText( text );
    setFont( fontName, fontSize );
  }

  Label::Label( const Label &other ) :
  Sprite( other ),
  _text( other._text ),
  _font( other._font ),
  _color( other._color ),
  _fontName( other._fontName ),
  _fontSize( other._fontSize ),
  _initialFontSize( other._initialFontSize )
  {
    updateTexture();
  }

  Label::~Label()
  {
  }

  Label &Label::operator = ( const Label &other )
  {
    Sprite::operator=( other );
    _text = other._text;
    _font = other._font;
    _color = other._color;
    _fontSize = other._fontSize;
    _initialFontSize = other._initialFontSize;
    _fontName = other._fontName;
    updateTexture();
    return *this;
  }

  void Label::setText( const std::string &text )
  {
    _text = text;
    updateTexture();
  }

  void Label::setFont( const string &fontName, const int fontSize )
  {
    _fontName = fontName;
    _fontSize = fontSize;
    Game *game = Game::getInstance();
    game->loadFont( fontName, fontSize );
    _font = game->getFont( fontName, fontSize );
    updateTexture();
  }

  void Label::setColor( const Color &color )
  {
    _color = color;
    updateTexture();
  }

  void Label::updateTexture()
  {
    if( _font )
    {
      SDL_Surface *surface = TTF_RenderText_Blended( _font, _text.c_str(), _color.getSDL_Color() );
      if( surface )
      {
        setTexture( new Texture( SDL_CreateTextureFromSurface( Game::getInstance()->getRenderer()->getSDL_Renderer(), surface ) ) );
        _cleanTexture = true;
        SDL_FreeSurface( surface );
      }
    }
  }


  void Label::setFontName( const std::string &fontName )
  {
    _fontName = fontName;
    setFont( _fontName, _fontSize );
  }

  void Label::setFontSize( const int fontSize )
  {
    _fontSize = fontSize;
    setFont( _fontName, _fontSize );
  }

  Node *Label::copy() const
  {
    return new Label( *this );
  }

  void Label::stopAllActions( const bool restoreInitialStatus )
  {
    Sprite::stopAllActions( restoreInitialStatus );
    if( restoreInitialStatus )
    {
      _fontSize = _initialFontSize;
      setFont( _fontName, _fontSize );
    }
  }

}
