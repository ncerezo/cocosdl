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

#ifndef __ResizeByAction_H_
#define __ResizeByAction_H_

#include "TimedAction.h"

namespace cocosdl
{
  namespace action
  {
    class ResizeByActionFactory;

    /**
     * Resize an object given the width and height delta.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class ResizeByAction : public TimedAction
    {
      friend class ResizeByActionFactory;

    public:
      /**
       * Constructor.
       *
       * @param durationMs duration in milliseconds
       * @param widthDelta amount of width to add (can be negative)
       * @param heightDelta amount of height to add (can be negative)
       */
      ResizeByAction( long long durationMs, int widthDelta, int heightDelta );

      ResizeByAction( const ResizeByAction &other );

      virtual ~ResizeByAction();

      ResizeByAction &operator = ( const ResizeByAction &other );

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy();

    protected:
      int _width0;
      int _height0;
      int _widthDelta;
      int _heightDelta;

      /**
       * Run the action.<br/>
       * This method must be implemented by subclasses to provide their function.
       *
       * @param node the node to run the action on
       * @param percent percentage of time elapsed since starting the action (percentage of the action to apply).
       */
      virtual void runStep( Node *node, float percent );

    };

    class ResizeByActionFactory : public ActionFactory
    {

      virtual Action *createInstance() const;
    };
  }
}

#endif //__ResizeByAction_H_
