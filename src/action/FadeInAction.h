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

#ifndef __FadeInAction_H_
#define __FadeInAction_H_

#include "TimedAction.h"
#include "ActionFactory.h"

namespace cocosdl
{
  namespace action
  {
    class FadeInActionFactory;

    /**
     * This action fades in the given node by incrementing the initial node opacity to 1.0 in the given time.<br/>
     * See TimedAction.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class FadeInAction : public TimedAction
    {
      friend class FadeInActionFactory;

    public:
      /**
       * Create a new action to run in the given duration (milliseconds).
       *
       * @param durationMs duration in milliseconds
       */
      FadeInAction( long long durationMs );

      FadeInAction( const FadeInAction &other );

      virtual ~FadeInAction();

      FadeInAction &operator = ( const FadeInAction &other );

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

      float _initialOpacity;

    };

    class FadeInActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };

  }
}

#endif //__FadeInAction_H_
