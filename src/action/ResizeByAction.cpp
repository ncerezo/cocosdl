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
#include "ResizeByAction.h"

namespace cocosdl
{
  namespace action
  {
    static ResizeByActionFactory resizeByActionFactory;

    static char const *const CLASS_NAME = "ResizeByAction";

    ResizeByAction::ResizeByAction( long long durationMs, int widthDelta, int heightDelta ) :
    TimedAction( durationMs ), _width0( 0 ), _height0( 0 ), _widthDelta( widthDelta ), _heightDelta( heightDelta )
    {
      _className = CLASS_NAME;
    }

    ResizeByAction::~ResizeByAction()
    {
    }

    ResizeByAction::ResizeByAction( const ResizeByAction &other ) :
    TimedAction( other._durationMs ),
    _width0( 0 ),
    _height0( 0 ),
    _widthDelta( other._widthDelta ),
    _heightDelta( other._heightDelta )
    {
      _className = CLASS_NAME;
    }

    ResizeByAction &ResizeByAction::operator = ( const ResizeByAction &other )
    {
      TimedAction::operator=( other );
      _width0 = other._width0;
      _height0 = other._height0;
      _widthDelta = other._widthDelta;
      _heightDelta = other._heightDelta;
      return *this;
    }

    void ResizeByAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _width0 = node->getWidth();
        _height0 = node->getHeight();
      }
      int width = _width0 + ( percent >= 1.0f ? _widthDelta : (int) ceil( _widthDelta * percent ) );
      int height = _height0 + ( percent >= 1.0f ? _heightDelta : (int) ceil( _heightDelta * percent ) );
      node->resizeBy( width - node->getWidth(), height - node->getHeight() );
    }

    Action *ResizeByAction::copy()
    {
      return getFromPoolOrCreate( this, resizeByActionFactory );
    }

    Action *ResizeByActionFactory::createInstance() const
    {
      return new ResizeByAction( 0, 0, 0 );
    }
  }
}
