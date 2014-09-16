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

#include "WaitAction.h"

namespace cocosdl
{
  namespace action
  {
    static WaitActionFactory waitActionFactory;

    static char const *const CLASS_NAME = "WaitAction";

    WaitAction::WaitAction( long long durationMs ) : TimedAction( durationMs )
    {
      _className = CLASS_NAME;
    }

    WaitAction::~WaitAction()
    {
    }

    WaitAction::WaitAction( const WaitAction &other ) : TimedAction( other )
    {
      _className = CLASS_NAME;
    }

    WaitAction &WaitAction::operator = ( const WaitAction &other )
    {
      TimedAction::operator=( other );
      return *this;
    }

    void WaitAction::runStep( Node *node, float percent )
    {
    }

    Action *WaitAction::copy()
    {
      return getFromPoolOrCreate( this, waitActionFactory );
    }

    Action *WaitActionFactory::createInstance() const
    {
      return new WaitAction( 0 );
    }
  }
}
