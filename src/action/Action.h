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

#ifndef __Action_H_
#define __Action_H_

#include "ActionObserver.h"
#include "ActionFactory.h"
#include <string>

#define DESTROY_ACTION(a) if( !(a)->release() ) { delete (a); } (a) = NULL;

namespace cocosdl
{
  class Node;

  namespace action
  {
    class ActionObserver;

    /**
     * ActionStatus marks the status of an action. Actions implement a simple finite state machine.
     */
    enum ActionStatus
    {
      Created, Started, Finished
    };

    /**
     * An action applies different modifications over a node, probably over time.<br/>
     * Action is an abstract class with pure virtual methods that must be implemented by subclasses.<br/>
     * Subclasses must implement the run method, and also the copy method.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class Action
    {

    public:
      Action();

      Action( const Action &other );

      virtual ~Action();

      Action &operator = ( const Action &other );

      ActionStatus const &getActionStatus() const
      {
        return _actionStatus;
      }

      void setActionStatus( ActionStatus const &actionStatus, const Node *node );

      ActionObserver *getObserver() const
      {
        return _observer;
      }

      void setObserver( ActionObserver *observer )
      {
        _observer = observer;
      }

      /**
       * Reset the action to the initial status so it can be applied to other nodes.
       *
       * @param node the node which the action has just been run on, to enable notification to obervers.
       */
      virtual void reset( const Node *node );

      /**
       * Run the action on a node. Must be implemented by subclases.
       */
      virtual void run( Node *node ) = 0;

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy() = 0;

      /**
       * Release the action to its pool, if possible.
       * @return true if the action was again accepted in the pool, false if it didn't belong there (must be deleted).
       */
      bool release();

    protected:
      std::string     _className;
      ActionStatus    _actionStatus;
      ActionObserver* _observer;

      static Action*getFromPoolOrCreate( const Action *source, const ActionFactory &factory );
    };

  }
}

#endif //__Action_H_
