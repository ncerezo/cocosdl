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

#include "Sprite.h"
#include "Game.h"
#include "Texture.h"
#include "Renderer.h"

namespace cocosdl {

  Sprite::Sprite() : _texture( NULL ), _cleanTexture( true )
  {

  }

  Sprite::Sprite( Texture *texture ) : _texture( NULL ), _cleanTexture( false )
  {
    setTexture( texture );
  }

  Sprite::Sprite( const std::string &fileName ) : _texture( NULL ), _cleanTexture( true )
  {
    setTexture( fileName );
  }

  Sprite::Sprite( const Sprite &other ) : Node( other ), _texture( NULL ), _cleanTexture( other._cleanTexture )
  {
    if( other._texture )
    {
      if( other._cleanTexture )
      {
        _texture = new Texture( *other._texture );
      }
      else
      {
        _texture = other._texture;
        _cleanTexture = false;
      }
    }
  }

  Sprite::~Sprite()
  {
    if( _texture && _cleanTexture )
    {
      delete _texture;
    }
  }


  Sprite &Sprite::operator = ( const Sprite &other )
  {
    Node::operator=( other );

    if( _texture && _cleanTexture )
    {
      delete _texture;
      _texture = NULL;
    }

    if( other._texture )
    {
      if( other._cleanTexture )
      {
        _texture = new Texture( *other._texture );
      }
      else
      {
        _texture = other._texture;
        _cleanTexture = false;
      }
    }
    return *this;
  }

  void Sprite::setTexture( const std::string &fileName )
  {
    if( _texture && _cleanTexture )
    {
      delete _texture;
      _texture = NULL;
    }
    _texture = new Texture( fileName );
    if( _texture )
    {
      _cleanTexture = true;
      _width = _texture->getWidth();
      _height = _texture->getHeight();
    }
  }

  void Sprite::setTexture( Texture *texture )
  {
    if( _texture && _cleanTexture )
    {
      delete _texture;
      _texture = NULL;
    }
    _texture = texture;
    if( _texture )
    {
      _cleanTexture = false;
      _width = _texture->getWidth();
      _height = _texture->getHeight();
    }
  }

  void Sprite::drawBeforeChildren( Rect &destinationRect ) const
  {
    Node::drawBeforeChildren( destinationRect );

    if( _texture )
    {
      Point center( (int) ( _anchorX * destinationRect.getWidth() ), (int) ( _anchorY * destinationRect.getHeight()) );
      _texture->setOpacity( _opacity );
      Game::getInstance()->getRenderer()->renderCopy(
          _texture,
          NULL,
          &destinationRect,
          (float const) _rotationAngle,
          center,
          SDL_FLIP_NONE
      );
    }
  }

  Node *Sprite::copy() const
  {
    return new Sprite( *this );
  }

  void Sprite::stopAllActions( const bool restoreInitialStatus )
  {
    Node::stopAllActions( restoreInitialStatus );
    if( restoreInitialStatus && _texture != NULL )
    {
      _width = _texture->getWidth();
      _height = _texture->getHeight();
    }
  }

}
