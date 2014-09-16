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

#include "ObjectPool.h"

#include <mutex>

static std::mutex _mutex;

namespace cocosdl
{
  namespace util
  {
    template <class T>
    ObjectPool<T>::ObjectPool() : _size( 10 )
    {
    }

    template <class T>
    ObjectPool<T>::ObjectPool( const unsigned size ) : _size( size )
    {
      _usedInstances.reserve( size );
      _freeInstances.reserve( size );
    }

    template <class T>
    ObjectPool<T>::~ObjectPool()
    {
    }

    template <class T>
    bool ObjectPool<T>::fetch( T& t )
    {
      _mutex.lock();
      if( _freeInstances.size() > 0 )
      {
        t = _freeInstances.back();
        _freeInstances.pop_back();
        _usedInstances.push_back( t );
        _mutex.unlock();
        return true;
      }
      else
      {
        _mutex.unlock();
        return false;
      }
    }

    template <class T>
    bool ObjectPool<T>::release( T t )
    {
      _mutex.lock();
      for( size_t i = 0; i < _usedInstances.size(); i++ )
      {
        T element = _usedInstances.at( i );
        if( t == element )
        {
          _usedInstances.erase( _usedInstances.begin().advance( i ) );
          _freeInstances.push_back( t );
          _mutex.unlock();
          return true;
        }
      }
      _mutex.unlock();
      return false;
    }

    template <class T>
    void ObjectPool<T>::insert( T t )
    {
      _mutex.lock();
      if( _usedInstances.size() + _freeInstances.size() < _size ) {
        _freeInstances.push_back( t );
      }
      _mutex.unlock();
    }
  }

}
