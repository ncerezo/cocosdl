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

#ifndef __SequenceAction_H_
#define __SequenceAction_H_

#include <vector>
#include "Action.h"
#include "Node.h"

namespace cocosdl
{
  namespace action
  {
    class SequenceActionFactory;

    /**
     * Run several actions in sequence. By default nodes run actions in sequences, so you just need to add them, but
     * you need to use this action when you want a sequence to be run inside another grouping action like GroupAction
     * or RepeatForeverAction.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class SequenceAction : public Action
    {
      friend class SequenceActionFactory;

    public:
      SequenceAction();

      SequenceAction( const SequenceAction &other );

      virtual ~SequenceAction();

      SequenceAction &operator = ( const SequenceAction &other );

      SequenceAction *addAction( Action *action );

      virtual void run( Node *node );

      void removeAll();

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy();

      /**
       * Reset the action to the initial status so it can be applied to other nodes.
       *
       * @param node the node which the action has just been run on, to enable notification to obervers.
       */
      virtual void reset( const Node *node );

    protected:
      std::vector<Action *> _actions;
      size_t _currentIndex;

    };

    class SequenceActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };
  }
}

#endif //__SequenceAction_H_
