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

#include <assert.h>
#include "MoveByAction.h"

namespace cocosdl
{
  namespace action
  {
    static MoveByActionFactory moveByActionFactory;

    static char const *const CLASS_NAME = "MoveByAction";

    MoveByAction::MoveByAction( long long durationMs, int xDelta, int yDelta ) :
    TimedAction( durationMs ), _x0( 0 ), _y0( 0 ), _xDelta( xDelta ), _yDelta( yDelta )
    {
      _className = CLASS_NAME;
    }

    MoveByAction::~MoveByAction()
    {
    }

    Action *MoveByAction::copy()
    {
      return getFromPoolOrCreate( this, moveByActionFactory );
    }

    MoveByAction::MoveByAction( const MoveByAction &other ) :
    TimedAction( other._durationMs ), _x0( 0 ), _y0( 0 ), _xDelta( other._xDelta ), _yDelta( other._yDelta )
    {
      _className = CLASS_NAME;
    }

    MoveByAction &MoveByAction::operator = ( const MoveByAction &other )
    {
      TimedAction::operator=( other );
      _x0 = other._x0;
      _y0 = other._y0;
      _xDelta = other._xDelta;
      _yDelta = other._yDelta;
      return *this;
    }

    void MoveByAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _x0 = node->getX();
        _y0 = node->getY();
      }
      int x = _x0 + ( percent >= 1.0f ? _xDelta : (int) ( _xDelta * percent ) );
      int y = _y0 + ( percent >= 1.0f ? _yDelta : (int) ( _yDelta * percent ) );
      node->setPosition( x, y );
    }

    Action *MoveByActionFactory::createInstance() const
    {
      return new MoveByAction( 0, 0, 0 );
    }
  }
}
