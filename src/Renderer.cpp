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

#include <SDL2_image/SDL_image.h>
#include "Renderer.h"
#include "Texture.h"
#include "Point.h"

cocosdl::Renderer::Renderer( SDL_Renderer *renderer ) : _renderer( renderer )
{
}

cocosdl::Renderer::~Renderer()
{
  if( _renderer )
  {
    SDL_DestroyRenderer( _renderer );
  }
}

void cocosdl::Renderer::getClipRect( cocosdl::Rect &rect ) const
{
  if( _renderer )
  {
    SDL_Rect r;
    SDL_RenderGetClipRect( _renderer, &r );
    rect.setOrigin( r.x, r.y );
    rect.setDimension( r.w, r.h );
  }
}

void cocosdl::Renderer::setClipRect( cocosdl::Rect const &rect )
{
  if( _renderer )
  {
    SDL_RenderSetClipRect( _renderer, &rect.get_SDL_Rect() );
  }
}

void cocosdl::Renderer::renderCopy( cocosdl::Texture    *texture,
                                    cocosdl::Rect const *source,
                                    cocosdl::Rect const *destination,
                                    const float         rotationAngle,
                                    cocosdl::Point      &center,
                                    const RendererFlip  flip
) const
{
  if( _renderer )
  {
    SDL_RenderCopyEx(
        _renderer,
        texture->getTexture(),
        source ? &source->get_SDL_Rect() : NULL,
        destination ? &destination->get_SDL_Rect() : NULL,
        rotationAngle,
        &center.get_SDL_Point(),
        flip
    );
  }
}

void cocosdl::Renderer::clear() const
{
  if( _renderer )
  {
    SDL_RenderClear( _renderer );
  }
}

void cocosdl::Renderer::present() const
{
  if( _renderer )
  {
    SDL_RenderPresent( _renderer );
  }
}
