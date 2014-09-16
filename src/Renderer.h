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

#ifndef __Renderer_H_
#define __Renderer_H_

#include <SDL2/SDL.h>
#include <string>
#include "Rect.h"

namespace cocosdl
{
  class Rect;
  class Texture;

  typedef SDL_RendererFlip RendererFlip;

  class Renderer
  {
  public:
    Renderer( SDL_Renderer *renderer );
    virtual ~Renderer();

    void getClipRect( Rect &rect ) const;
    void setClipRect( const Rect &rect );

    void renderCopy( Texture* texture,
                     const Rect* source,
                     const Rect* destination,
                     const float rotationAngle,
                     Point &center,
                     const RendererFlip flip
    ) const;

    void clear() const;
    void present() const;

    SDL_Renderer *getSDL_Renderer() const
    {
      return _renderer;
    }

  private:
    SDL_Renderer *_renderer;
  };
}

#endif //__Renderer_H_
