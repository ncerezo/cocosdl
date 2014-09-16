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

#ifndef __Command_H_
#define __Command_H_

namespace cocosdl {

  class Node;

  namespace util
  {
    /**
     * A command to be run on a node, usually asynchronously from the RunCommandAction.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class Command
    {

    public:
      Command()
      {
      };

      virtual ~Command()
      {
      };

      /**
       * Run the command on the given node.
       *
       * @param node the node
       */
      virtual void run( Node *node ) = 0;

      /**
       * Create a deep copy of the command, with the same subclass, ready to be run.
       */
      virtual Command *copy() = 0;

    };

  }

}

#endif //__Command_H_
