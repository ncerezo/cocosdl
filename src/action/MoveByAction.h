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

#ifndef __MoveByAction_H_
#define __MoveByAction_H_

#include "TimedAction.h"

namespace cocosdl
{
  namespace action
  {
    class MoveByActionFactory;

    /**
     * Move a node to a different place given the distance.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class MoveByAction : public TimedAction
    {
      friend class MoveByActionFactory;

    public:
      /**
       * Constructor.
       * @param durationMs duration in milliseconds
       * @param xDelta pixels to move in the X axis, can be negative.
       * @param yDelta pixels to move in the Y axis, can be negative.
       */
      MoveByAction( long long durationMs, int xDelta, int yDelta );

      MoveByAction( const MoveByAction &other );

      virtual ~MoveByAction();

      MoveByAction &operator = ( const MoveByAction &other );

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy();

    protected:
      int _x0;
      int _y0;
      int _xDelta;
      int _yDelta;

      /**
       * Run the action.<br/>
       * This method must be implemented by subclasses to provide their function.
       *
       * @param node the node to run the action on
       * @param percent percentage of time elapsed since starting the action (percentage of the action to apply).
       */
      virtual void runStep( Node *node, float percent );

    };

    class MoveByActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };

  }
}

#endif //__MoveByAction_H_
