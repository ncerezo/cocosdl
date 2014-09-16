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

#include <mutex>
#include "ActionPool.h"

namespace cocosdl
{
  namespace action
  {
    static std::mutex _mutex;

    ActionPool::ActionPool():  _size( 30 )
    {
      _usedInstances.reserve( _size );
      _freeInstances.reserve( _size );
    }

    ActionPool::ActionPool( const unsigned size ): _size( size )
    {
      _usedInstances.reserve( size );
      _freeInstances.reserve( size );
    }

    ActionPool::~ActionPool()
    {

    }

    bool ActionPool::fetch( Action *&action )
    {
      _mutex.lock();
      if( _freeInstances.size() > 0 )
      {
        action = _freeInstances.back();
        _freeInstances.pop_back();
        _usedInstances.push_back( action );
        _mutex.unlock();
        return true;
      }
      else
      {
        _mutex.unlock();
        return false;
      }
    }

    bool ActionPool::release( Action *action )
    {
      _mutex.lock();
      for( size_t i = 0; i < _usedInstances.size(); i++ )
      {
        Action* element = _usedInstances.at( i );
        if( action == element )
        {
          std::vector<Action*>::iterator pos = _usedInstances.begin();
          pos += i + 1;
          _usedInstances.erase( pos );
          _freeInstances.push_back( action );
          _mutex.unlock();
          return true;
        }
      }
      _mutex.unlock();
      return false;
    }

    void ActionPool::insert( Action *action )
    {
      _mutex.lock();
      if( _usedInstances.size() + _freeInstances.size() < _size ) {
        _freeInstances.push_back( action );
      }
      _mutex.unlock();
    }
  }
}
