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

#ifndef __GroupAction_H_
#define __GroupAction_H_

#include <vector>
#include "Action.h"

namespace cocosdl
{
  class Node;

  namespace action
  {
    class GroupActionFactory;

    /**
     * Run several actions in parallel.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class GroupAction : public Action
    {
      friend class GroupActionFactory;

    public:
      GroupAction();

      GroupAction( const GroupAction &other );

      virtual ~GroupAction();

      GroupAction &operator = ( const GroupAction &other );

      /**
       * Add an action to the group.
       */
      GroupAction *addAction( Action *action );

      /**
       * Run the action on a node. Must be implemented by subclases.
       */
      virtual void run( Node *node );

      /**
       * Remove all the actions in the group.
       */
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

    };

    class GroupActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };
  }
}

#endif //__GroupAction_H_
