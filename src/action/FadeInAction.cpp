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

#include "FadeInAction.h"
#include "Log.h"

#include <assert.h>

namespace cocosdl
{
  namespace action
  {
    static FadeInActionFactory fadeInActionFactory;

    static char const *const CLASS_NAME = "FadeInAction";

    FadeInAction::FadeInAction( long long durationMs ) : TimedAction( durationMs )
    {
      _className = CLASS_NAME;
    }

    FadeInAction::~FadeInAction()
    {

    }

    FadeInAction::FadeInAction( const FadeInAction &other ) : TimedAction( other )
    {
      _className = CLASS_NAME;
    }

    FadeInAction &FadeInAction::operator = ( const FadeInAction &other )
    {
      TimedAction::operator=( other );
      _initialOpacity = other._initialOpacity;
      return *this;
    }

    void FadeInAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _initialOpacity = node->getOpacity();
      }
      float opacity = percent >= 1.0f ? 1.0f : _initialOpacity + ( ( 1.0f - _initialOpacity ) * percent );
      node->setOpacity( opacity );
    }

    Action *FadeInAction::copy()
    {
      return getFromPoolOrCreate( this, fadeInActionFactory );
    }

    Action *FadeInActionFactory::createInstance() const
    {
      return new FadeInAction( 0 );
    }
  }
}
