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

#include "Action.h"
#include "Node.h"
#include "ActionPool.h"
#include <mutex>

using namespace cocosdl::util;

static std::mutex _mutex;
static std::map< std::string, cocosdl::action::ActionPool* > _poolMap;

namespace cocosdl
{
  namespace action
  {

    Action::Action() : _actionStatus( Created ), _observer( NULL ), _className( "Action" )
    {
    }

    Action::~Action()
    {
    }

    Action::Action( const Action &other ) : _actionStatus( Created ), _observer( NULL ), _className( "Action" )
    {

    }

    Action &Action::operator = ( const Action &other )
    {
      _actionStatus = Created;
      _observer = other._observer;
      _className = other._className;
      return *this;
    }

    void Action::reset( const Node *node )
    {
      setActionStatus( Created, node );
    }


    void Action::setActionStatus( ActionStatus const &actionStatus, const Node *node )
    {
      _actionStatus = actionStatus;
      if( _observer )
      {
        switch( _actionStatus )
        {
          case Finished:
            _observer->actionFinished( this, node );
            break;

          default:
            break;
        }
      }
    }

    bool Action::release()
    {
      ActionPool *pool = NULL;
      if( _poolMap.find( _className ) != _poolMap.end() )
      {
        pool = _poolMap.at( _className );
        return pool->release( this );
      }
      else
      {
        return false;
      }
    }

    Action *Action::getFromPoolOrCreate( const Action *source, const ActionFactory &factory )
    {
      ActionPool *pool = NULL;
      _mutex.lock();
      if( _poolMap.find( source->_className ) != _poolMap.end() )
      {
        pool = _poolMap.at( source->_className );
      }
      else
      {
        pool = new ActionPool( 30 ); // ToDo: make this configurable per action type
        _poolMap.insert( std::make_pair( source->_className, pool ) );
      }
      _mutex.unlock();

      Action* action = NULL;
      if( pool->fetch( action ) )
      {
        action->reset( NULL );
      }
      else
      {
        action = factory.createInstance();
        pool->insert( action );
      }
      *action = *source;
      return action;
    }
  }
}
