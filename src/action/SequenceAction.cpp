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
#include "SequenceAction.h"

namespace cocosdl
{
  namespace action
  {
    static SequenceActionFactory sequenceActionFactory;

    static char const *const CLASS_NAME = "SequenceAction";

    SequenceAction::SequenceAction() : _currentIndex( 0 )
    {
      _className = CLASS_NAME;
    }

    SequenceAction::SequenceAction( const SequenceAction &other ) : Action( other ), _currentIndex( 0 )
    {
      _className = CLASS_NAME;
      size_t count = other._actions.size();
      for( size_t i = 0; i < count; i++ )
      {
        addAction( other._actions.at( i )->copy() );
      }
    }

    SequenceAction &SequenceAction::operator = ( const SequenceAction &other )
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

    SequenceAction::~SequenceAction()
    {
      removeAll();
    }

    void SequenceAction::removeAll()
    {
      while( _actions.size() > 0 )
      {
        Action *action = _actions.back();
        _actions.pop_back();
        DESTROY_ACTION( action );
      }
    }


    SequenceAction *SequenceAction::addAction( Action *action )
    {
      if( action )
      {
        _actions.push_back( action );
      }
      return this;
    }

    void SequenceAction::run( Node *node )
    {
      assert( node != NULL );
      if( _actions.size() > 0 && _currentIndex < _actions.size() )
      {
        Action *action = _actions.at( _currentIndex );
        if( action->getActionStatus() != Finished )
        {
//          Log::debug() << "[Sequence] running action: " << _currentIndex << std::endl;
          action->run( node );
          if( action->getActionStatus() == Finished )
          {
            _currentIndex++;
          }
        }
        else
        {
          _currentIndex++;
        }
        setActionStatus( _currentIndex < _actions.size() ? Started : Finished, node );
      }
      else
      {
        setActionStatus( Finished, node );
      }
    }

    Action *SequenceAction::copy()
    {
      return getFromPoolOrCreate( this, sequenceActionFactory );
    }

    void SequenceAction::reset( const Node *node )
    {
      Action::reset( node );
      _currentIndex = 0;
      size_t count = _actions.size();
      for( size_t i = 0; i < count; i++ )
      {
        Action *action = _actions.at( i );
        action->reset( node );
      }
    }

    Action *SequenceActionFactory::createInstance() const
    {
      return new SequenceAction();
    }
  }
}
