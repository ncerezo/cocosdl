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

#include "Texture.h"
#include "Game.h"
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "Renderer.h"

namespace cocosdl {

  Texture::Texture() : _texture( NULL ), _width( 0 ), _height( 0 ), _fileName( "" )
  {
  }

  Texture::Texture( const std::string &fileName )
  {
    loadTexture( fileName );
  }


  Texture::Texture( SDL_Texture *_texture ) : _texture( _texture )
  {
    if( _texture != NULL )
    {
      SDL_QueryTexture( _texture, NULL, NULL, &_width, &_height );
    }
  }

  Texture::Texture( const Texture &other ) : _width( other._width ), _height( other._height ), _fileName( other._fileName )
  {
    if( other._texture != NULL )
    {
      loadTexture( _fileName );
    }
    else
    {
      _texture = NULL;
    }
  }

  Texture::~Texture()
  {
    if( _texture )
    {
      SDL_DestroyTexture( _texture );
    }
  }


  Texture &Texture::operator = ( const Texture &other )
  {
    if( _texture )
    {
      SDL_DestroyTexture( _texture );
    }
    _fileName = other._fileName;
    if( other._texture != NULL )
    {
      loadTexture( _fileName );
    }
    else
    {
      _texture = NULL;
      _width = 0;
      _height = 0;
    }
    return *this;
  }

  bool Texture::loadTexture( const std::string &fileName )
  {
    Game *game = Game::getInstance();
    const std::string resPath = game->getResourcePath() + fileName;
    _texture = IMG_LoadTexture( game->getRenderer()->getSDL_Renderer(), resPath.c_str() );
    if( _texture != NULL )
    {
      SDL_QueryTexture( _texture, NULL, NULL, &_width, &_height );
      _fileName = fileName;
    }
    return _texture != NULL;
  }


  void Texture::setOpacity( const float opacity )
  {
    SDL_SetTextureAlphaMod( _texture, (Uint8) ( opacity * 255 ) );
  }

  void Texture::setTexture( SDL_Texture* texture )
  {
    if( _texture != texture )
    {
      if( _texture )
      {
        SDL_DestroyTexture( _texture );
      }
      _texture = texture;
      if( _texture != NULL )
      {
        SDL_QueryTexture( _texture, NULL, NULL, &_width, &_height );
      }
    }
  }
}