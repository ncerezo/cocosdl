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

#ifndef __ActionPool_H_
#define __ActionPool_H_

#include <vector>

namespace cocosdl
{
  namespace action
  {
    class Action;

    class ActionPool
    {

    public:
      ActionPool();

      ActionPool( const unsigned size );

      virtual ~ActionPool();

      bool fetch( Action* &action );
      bool release( Action* action );

      void insert( Action* action );

      /**
       * Get the size (maximum of objects) of the pool.
       * @return maximum size
       */
      unsigned int getSize() const
      {
        return _size;
      }

      /**
       * Get the number of instances currently in use.
       * @return instances in use
       */
      const size_t getUsedSize() const
      {
        return _usedInstances.size();
      }

      const size_t getFreeInstances() const
      {
        return _freeInstances.size();
      }

    private:
      unsigned _size;
      std::vector<Action*> _usedInstances;
      std::vector<Action*> _freeInstances;

    };
  }

}

#endif //__ActionPool_H_
