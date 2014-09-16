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

#ifndef __ActionObserver_H_
#define __ActionObserver_H_

namespace cocosdl
{
  class Node;

  namespace action
  {
    class Action;

    /**
     * ActionObserver is an interface / protocol to allow objects to be notified when actions change status running on a
     * node.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class ActionObserver
    {

    public:
      /**
       * The action has just finished running on a node.
       *
       * @param action the action being run
       * @param node the node it has finished running on
       */
      virtual void actionFinished( Action const *action, Node const *node ) = 0;

    };

  }
}

#endif //__ActionObserver_H_
