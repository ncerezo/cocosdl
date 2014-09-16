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

#ifndef __PlayEffectAction_H_
#define __PlayEffectAction_H_

#include "Action.h"
#include "Node.h"
#include <string>

namespace cocosdl
{
  namespace action
  {
    // ToDo: implement threaded sound queue
    class PlayEffectActionFactory;

    /**
     * Play a sound effect.
     *
     * @author narciso.cerezo@gmail.com
     * @version 1.0
     */
    class PlayEffectAction : public Action
    {
      friend class PlayEffectActionFactory;

    public:
      /**
       * Play an effect.
       *
       * @param name the effect name
       */
      PlayEffectAction( std::string name );

      PlayEffectAction( const PlayEffectAction &other );

      ~PlayEffectAction();

      PlayEffectAction &operator = ( const PlayEffectAction &other );

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
      std::string _name;

    };

    class PlayEffectActionFactory : public ActionFactory
    {

    public:
      virtual Action *createInstance() const;
    };
  }
}

#endif //__PlayEffectAction_H_
