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

#ifndef __RunCommandAction_H_
#define __RunCommandAction_H_

#include "Action.h"
namespace cocosdl
{
  namespace util
  {
    class Command;
  }

  namespace action
  {
    class RunCommandActionFactory;

    /**
     * Run a command on a node.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class RunCommandAction : public Action
    {
      friend class RunCommandActionFactory;

    public:
      /**
       * Constructor.
       *
       * @param command command to run.
       */
      RunCommandAction( util::Command *command );

      RunCommandAction( const RunCommandAction &other );

      ~RunCommandAction();

      RunCommandAction &operator = ( const RunCommandAction &other );

      virtual void run( Node *node );

      /**
       * Allows reuse of the action by creating disposable copies.<br/>
       * Must return a new action of the same subtype, deep copied, ready to be used on a node.
       */
      virtual Action *copy();

    private:
      util::Command *_command;
    };

    class RunCommandActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };
  }
}

#endif //__RunCommandAction_H_
