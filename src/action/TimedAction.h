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

#ifndef __TimedAction_H_
#define __TimedAction_H_

#include "Action.h"
#include "Node.h"

namespace cocosdl
{
  namespace action
  {

    /**
     * This subclass of action provides the means of measuring time and calculating how much time has elapsed from one
     * game engine call to other. Cannot be used directly, it is a pure virtual class that must be subclassed.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class TimedAction : public Action
    {

    public:
      virtual void run( Node *node );

      virtual void reset( const Node *node );

      long long int getDurationMs() const
      {
        return _durationMs;
      }

    protected:
      TimedAction( long long durationMs );

      TimedAction( const TimedAction &other );

      virtual ~TimedAction();

      TimedAction &operator = ( const TimedAction &other );

      long long _durationMs;
      long long _lastExecution;

      /**
       * Run the action.<br/>
       * This method must be implemented by subclasses to provide their function.
       *
       * @param node the node to run the action on
       * @param percent percentage of time elapsed since starting the action (percentage of the action to apply).
       */
      virtual void runStep( Node *node, float percent ) = 0;

    };

  }
}

#endif //__TimedAction_H_
