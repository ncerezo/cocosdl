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

#include "TimedAction.h"
#include "Game.h"

namespace cocosdl
{
  namespace action
  {

    static const long long NEVER_RUN = -1L;

    TimedAction::TimedAction( long long durationMs ) : _durationMs( durationMs ), _lastExecution( NEVER_RUN )
    {
    }

    TimedAction::~TimedAction()
    {
    }

    TimedAction::TimedAction( const TimedAction &other ) :
    Action( other ), _durationMs( other._durationMs ), _lastExecution( NEVER_RUN )
    {

    }

    TimedAction &TimedAction::operator = ( const TimedAction &other )
    {
      Action::operator=( other );
      _lastExecution = NEVER_RUN;
      _durationMs = other._durationMs;
      return *this;
    }

    void TimedAction::run( Node *node )
    {
      long long currentTimeMillis = Game::getInstance()->currentTimeMillis();
      if( _actionStatus == Created )
      {
        if( _durationMs > 0 )
        {
          runStep( node, 0.0f );
          _lastExecution = currentTimeMillis;
          setActionStatus( Started, node );
        }
        else
        {
          runStep( node, 1.0f );
          _lastExecution = currentTimeMillis;
          setActionStatus( Finished, node );
        }
      }
      else
      {
          if( _actionStatus == Started )
          {
            long long elapsed = currentTimeMillis - _lastExecution;
            float percent = (float) elapsed / (float) _durationMs;
            if( percent > 1.0f )
            {
              percent = 1.0f;
            }
            runStep( node, percent );
            if( percent == 1.0f )
            {
              setActionStatus( Finished, node );
            }
          }
      }
    }

    void TimedAction::reset( const Node *node )
    {
      Action::reset( node );
      _lastExecution = NEVER_RUN;
    }

  }
}
