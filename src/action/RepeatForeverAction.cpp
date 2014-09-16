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

#include "RepeatForeverAction.h"

namespace cocosdl
{
  namespace action
  {
    static RepeatForeverActionFactory repeatForeverActionFactory;

    static char const *const CLASS_NAME = "RepeatForeverAction";

    RepeatForeverAction::RepeatForeverAction( Action *action ) : _child( action )
    {
      _className = CLASS_NAME;
    }

    RepeatForeverAction::RepeatForeverAction( const RepeatForeverAction &other ) : Action( other ), _child( NULL )
    {
      _className = CLASS_NAME;
      releaseChild();
      if( other._child )
      {
        _child = other._child->copy();
      }
    }

    RepeatForeverAction::~RepeatForeverAction()
    {
      releaseChild();
    }

    void RepeatForeverAction::releaseChild()
    {
      if( _child && !_child->release() )
      {
        DESTROY_ACTION( _child );
      }
      _child = NULL;
    }

    RepeatForeverAction &RepeatForeverAction::operator = ( const RepeatForeverAction &other )
    {
      Action::operator=( other );
      releaseChild();
      if( other._child )
      {
        _child = other._child->copy();
      }
      return *this;
    }

    void RepeatForeverAction::run( Node *node )
    {
      setActionStatus( Started, node );
      if( _child )
      {
        if( _child->getActionStatus() == Finished )
        {
          _child->reset( node );
        }
        _child->run( node );
      }
    }

    Action *RepeatForeverAction::copy()
    {
      return getFromPoolOrCreate( this, repeatForeverActionFactory );
    }

    Action *RepeatForeverActionFactory::createInstance() const
    {
      return new RepeatForeverAction( NULL );
    }
  }
}

