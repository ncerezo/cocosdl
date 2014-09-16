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

#include <assert.h>
#include "FadeOutAction.h"

namespace cocosdl
{
  namespace action
  {
    static FadeOutActionFactory fadeOutActionFactory;

    static char const *const CLASS_NAME = "FadeOutAction";

    FadeOutAction::FadeOutAction( long long durationMs ) : TimedAction( durationMs )
    {
      _className = CLASS_NAME;
    }

    FadeOutAction::~FadeOutAction()
    {

    }

    FadeOutAction::FadeOutAction( const FadeOutAction &other ) : TimedAction( other )
    {
      _className = CLASS_NAME;
    }

    FadeOutAction &FadeOutAction::operator = ( const FadeOutAction &other )
    {
      TimedAction::operator=( other );
      _initialOpacity = other._initialOpacity;
      return *this;
    }

    void FadeOutAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _initialOpacity = node->getOpacity();
      }
      float opacity = percent >= 1.0f ? 0.0f : _initialOpacity - ( _initialOpacity * percent );
      node->setOpacity( opacity );
    }

    Action *FadeOutAction::copy()
    {
      return getFromPoolOrCreate( this, fadeOutActionFactory );
    }

    Action *FadeOutActionFactory::createInstance() const
    {
      return new FadeOutAction( 0 );
    }
  }
}
