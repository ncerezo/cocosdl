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

#ifndef __Sprite_H_
#define __Sprite_H_

#include "Node.h"
#include <string>

namespace cocosdl {

  class Texture;

  /**
   * A Sprite is the basic subclass of Node that provides texture (image) drawing.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Sprite : public Node
  {

  public:
    Sprite();

    Sprite( Texture *texture );

    Sprite( const std::string &textureFilePath );

    Sprite( const Sprite &other );

    virtual ~Sprite();

    Sprite &operator = ( const Sprite &other );

    void setTexture( const std::string &textureFilePath );

    void setTexture( Texture *texture );

    /**
     * Create a copy of the object with the same class and deep copied properties.
     *
     * @return a new node deep copied from this one with the same class
     */
    virtual Node *copy() const;

    /**
     * Stop (and free) all current actions. If restoreInitialStatus is true, the node is restored to it's initial status.
     * That is dependent on the subclass implementation.
     *
     * @param restoreInitialStatus restore node initial status
     */
    virtual void stopAllActions( const bool restoreInitialStatus );

  protected:
    Texture   *_texture;
    bool      _cleanTexture;

    virtual void drawBeforeChildren( Rect &destinationRect ) const;
  };

}

#endif //__Sprite_H_
