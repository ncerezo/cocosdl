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

#ifndef __RepeatForeverAction_H_
#define __RepeatForeverAction_H_

#include "Action.h"
#include "Node.h"

namespace cocosdl
{
  namespace action
  {
    class RepeatForeverActionFactory;

    /**
     * Repeat an action for ever (until manually stopped).
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class RepeatForeverAction : public Action
    {
      friend class RepeatForeverActionFactory;

    public:
      /**
       * Repeat the given action forever, or until stopped.
       *
       * @param action action to repeat
       */
      RepeatForeverAction( Action *action );

      RepeatForeverAction( const RepeatForeverAction &other );

      ~RepeatForeverAction();

      RepeatForeverAction &operator = ( const RepeatForeverAction &other );

      /**
       * Run the action on a node. Must be implemented by subclases.
       */
      virtual void run( Node *node );

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy();

    protected:
      Action *_child;

    private:
      void releaseChild();
    };

    class RepeatForeverActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };
  }
}

#endif //__RepeatForeverAction_H_
