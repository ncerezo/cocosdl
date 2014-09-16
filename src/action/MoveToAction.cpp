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
#include "MoveToAction.h"

namespace cocosdl
{
  namespace action
  {
    static MoveToActionFactory moveToActionFactory;

    static char const *const CLASS_NAME = "MoveToAction";

    MoveToAction::MoveToAction( long long durationMs, int x, int y ) :
    TimedAction( durationMs ), _x0( 0 ), _y0( 0 ), _x1( x ), _y1( y )
    {
      _className = CLASS_NAME;
    }

    MoveToAction::~MoveToAction()
    {

    }

    MoveToAction::MoveToAction( const MoveToAction &other ) :
    TimedAction( other._durationMs ), _x0( 0 ), _y0( 0 ), _x1( other._x1 ), _y1( other._y1 )
    {
      _className = CLASS_NAME;
    }

    MoveToAction &MoveToAction::operator = ( const MoveToAction &other )
    {
      TimedAction::operator=( other );
      _x0 = other._x0;
      _y0 = other._y0;
      _x1 = other._x1;
      _y1 = other._y1;
      return *this;
    }

    void MoveToAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _x0 = node->getX();
        _y0 = node->getY();
        setActionStatus( Started, node );
      }
      if( _actionStatus != Finished )
      {
        int x = percent >= 1.0f ? _x1 : _x0 + (int) ( ( _x1 - _x0 ) * percent );
        int y = percent >= 1.0f ? _y1 : _y0 + (int) ( ( _y1 - _y0 ) * percent );
        node->setPosition( x, y );
        if( x == _x1 && y == _y1 )
        {
          setActionStatus( Finished, node );
        }
      }
    }

    Action *MoveToAction::copy()
    {
      return getFromPoolOrCreate( this, moveToActionFactory );
    }

    Action *MoveToActionFactory::createInstance() const
    {
      return new MoveToAction( 0, 0, 0 );
    }
  }
}
