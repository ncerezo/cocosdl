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
#include "RemoveFromParentAction.h"
#include "Node.h"

namespace cocosdl
{
  namespace action
  {
    static RemoveFromParentActionFactory removeFromParentActionFactory;

    static char const *const CLASS_NAME = "RemoveFromParentAction";

    RemoveFromParentAction::RemoveFromParentAction()
    {
      _className = CLASS_NAME;
    }

    RemoveFromParentAction::RemoveFromParentAction( const RemoveFromParentAction &other ) : Action( other )
    {
      _className = CLASS_NAME;
    }

    RemoveFromParentAction::~RemoveFromParentAction()
    {
    }

    RemoveFromParentAction &RemoveFromParentAction::operator = ( const RemoveFromParentAction &other )
    {
      Action::operator=( other );
      return *this;
    }

    void RemoveFromParentAction::run( Node *node )
    {
      assert( node != NULL );
      if( node->getParent() )
      {
        node->getParent()->addNodeToRemove( node );
      }
      setActionStatus( Finished, node );
    }

    Action *RemoveFromParentAction::copy()
    {
      return getFromPoolOrCreate( this, removeFromParentActionFactory );
    }

    Action *RemoveFromParentActionFactory::createInstance() const
    {
      return new RemoveFromParentAction();
    }
  }
}
