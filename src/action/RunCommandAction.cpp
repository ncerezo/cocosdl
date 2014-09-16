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

#include "RunCommandAction.h"
#include "Command.h"

using namespace cocosdl::util;

namespace cocosdl
{
  namespace action
  {
    static RunCommandActionFactory runCommandActionFactory;

    static char const *const CLASS_NAME = "RunCommandAction";

    RunCommandAction::RunCommandAction( Command *command ) : _command( command )
    {
      _className = CLASS_NAME;
    }

    RunCommandAction::RunCommandAction( const RunCommandAction &other ) : Action( other )
    {
      _className = CLASS_NAME;
      if( _command )
      {
        delete _command;
      }
      _command = other._command ? other._command->copy() : NULL;
    }

    RunCommandAction::~RunCommandAction()
    {
      if( _command )
      {
        delete _command;
      }
    }

    RunCommandAction &RunCommandAction::operator = ( const RunCommandAction &other )
    {
      Action::operator=( other );
      if( _command )
      {
        delete _command;
      }
      _command = other._command ? other._command->copy() : NULL;
      return *this;
    }

    void RunCommandAction::run( Node *node )
    {
      if( _command )
      {
        _command->run( node );
      }
      setActionStatus( Finished, node );
    }

    Action *RunCommandAction::copy()
    {
      return getFromPoolOrCreate( this, runCommandActionFactory );
    }

    Action *RunCommandActionFactory::createInstance() const
    {
      return new RunCommandAction( NULL );
    }
  }
}