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
#include "GroupAction.h"
#include "Node.h"

namespace cocosdl
{
  namespace action
  {
    static GroupActionFactory groupActionFactory;

    static char const *const CLASS_NAME = "GroupAction";

    GroupAction::GroupAction()
    {
      _className = CLASS_NAME;
    }

    GroupAction::GroupAction( const GroupAction &other ) : Action( other )
    {
      _className = CLASS_NAME;
      size_t count = other._actions.size();
      for( size_t i = 0; i < count; i++ )
      {
        addAction( other._actions.at( i )->copy() );
      }
    }

    GroupAction &GroupAction::operator = ( const GroupAction &other )
    {
      Action::operator=( other );
      removeAll();
      size_t count = other._actions.size();
      for( size_t i = 0; i < count; i++ )
      {
        addAction( other._actions.at( i )->copy() );
      }
      return *this;
    }

    GroupAction::~GroupAction()
    {
      removeAll();
    }

    void GroupAction::removeAll()
    {
      while( _actions.size() > 0 )
      {
        Action *action = _actions.back();
        _actions.pop_back();
        DESTROY_ACTION( action );
      }
    }

    GroupAction *GroupAction::addAction( Action *action )
    {
      if( action )
      {
        _actions.push_back( action );
      }
      return this;
    }

    void GroupAction::run( Node *node )
    {
      assert( node != NULL );
      ActionStatus status = Finished;
      size_t count = _actions.size();
      for( size_t i = 0; i < count; i++ )
      {
        Action *action = _actions.at( i );
        if( action->getActionStatus() != Finished )
        {
          status = Started;
//          Log::debug() << "[Group] running action: " << i << std::endl;
          action->run( node );
        }
      }
      setActionStatus( status, node );
    }

    Action *GroupAction::copy()
    {
      return getFromPoolOrCreate( this, groupActionFactory );
    }

    void GroupAction::reset( const Node *node )
    {
      Action::reset( node );
      size_t count = _actions.size();
      for( size_t i = 0; i < count; i++ )
      {
        Action *action = _actions.at( i );
        action->reset( node );
      }
    }

    Action *GroupActionFactory::createInstance() const
    {
      return new GroupAction();
    }
  }
}
