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

#include "PlayEffectAction.h"
#include "Node.h"
#include "Game.h"

namespace cocosdl
{
  namespace action
  {
    static PlayEffectActionFactory playEffectActionFactory;

    static char const *const CLASS_NAME = "PlayEffectAction";

    PlayEffectAction::PlayEffectAction( std::string name ) : _name( name )
    {
      _className = CLASS_NAME;
    }

    PlayEffectAction::PlayEffectAction( const PlayEffectAction &other ) : Action( other ), _name( other._name )
    {
      _className = CLASS_NAME;
    }

    PlayEffectAction::~PlayEffectAction()
    {
    }

    PlayEffectAction &PlayEffectAction::operator = ( const PlayEffectAction &other )
    {
      _name = other._name;
      return *this;
    }

    void PlayEffectAction::run( Node *node )
    {
      Game::getInstance()->playSound( _name );
      setActionStatus( Finished, node );
    }

    Action *PlayEffectAction::copy()
    {
      return getFromPoolOrCreate( this, playEffectActionFactory );
    }

    Action *PlayEffectActionFactory::createInstance() const
    {
      return new PlayEffectAction( "" );
    }
  }
}
