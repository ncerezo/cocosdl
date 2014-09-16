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

#ifndef __WaitAction_H_
#define __WaitAction_H_

#include "TimedAction.h"
#include "ObjectPool.h"

namespace cocosdl
{
  namespace action
  {
    class WaitActionFactory;

    /**
     * Waits for a given time.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class WaitAction : public TimedAction
    {
      friend class WaitActionFactory;

    public:
      WaitAction( long long durationMs );

      WaitAction( const WaitAction &other );

      virtual ~WaitAction();

      WaitAction &operator = ( const WaitAction &other );

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy();

    protected:
      /**
       * Run the action.<br/>
       * This method must be implemented by subclasses to provide their function.
       *
       * @param node the node to run the action on
       * @param percent percentage of time elapsed since starting the action (percentage of the action to apply).
       */
      virtual void runStep( Node *node, float percent );
    };

    class WaitActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };
  }
}

#endif //__WaitAction_H_
