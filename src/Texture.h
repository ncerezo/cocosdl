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

#ifndef __Texture_H_
#define __Texture_H_

#include <SDL2/SDL.h>
#include <string>

namespace cocosdl {

  /**
   * Represents a texture (image).
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Texture
  {

  public:
    /**
     * Create an empty texture. To use it you must first call loadTexture.
     */
    Texture();

    /**
     * Create a texture from the given resource file name.
     *
     * @param fileName resource file name (including extension, png or jpg).
     */
    Texture( const std::string &fileName );

    Texture( const Texture &other );

    Texture( SDL_Texture *_texture );

    Texture &operator = ( const Texture &other );

    virtual ~Texture();

    /**
     * Get the underlying texture object.
     */
    SDL_Texture *getTexture() const
    {
      return _texture;
    }

    /**
     * Load a texture from a resource file image.
     *
     * @param fileName resource file name (including extension, png or jpg).
     */
    bool loadTexture( const std::string &fileName );

    /**
     * Get the texture width.
     */
    int getWidth() const
    {
      return _width;
    }

    /**
     * Get the texture height.
     */
    int getHeight() const
    {
      return _height;
    }

    void setOpacity( const float opacity );

  private:
    SDL_Texture*  _texture;
    int           _width;
    int           _height;
    std::string   _fileName;


    void setTexture( SDL_Texture *texture );
  };

}
#endif //__Texture_H_
