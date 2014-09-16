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
#include "ResizeToAction.h"

namespace cocosdl
{
  namespace action
  {
    static ResizeToActionFactory resizeToActionFactory;

    static char const *const CLASS_NAME = "ResizeToAction";

    ResizeToAction::ResizeToAction( long long durationMs, int x, int y ) :
    TimedAction( durationMs ), _width0( 0 ), _height0( 0 ), _width1( x ), _height1( y )
    {
      _className = CLASS_NAME;
    }

    ResizeToAction::~ResizeToAction()
    {

    }

    ResizeToAction::ResizeToAction( const ResizeToAction &other ) :
    TimedAction( other._durationMs ), _width0( 0 ), _height0( 0 ), _width1( other._width1 ), _height1( other._height1 )
    {
      _className = CLASS_NAME;
    }

    ResizeToAction &ResizeToAction::operator = ( const ResizeToAction &other )
    {
      TimedAction::operator=( other );
      _width0 = other._width0;
      _height0 = other._height0;
      _width1 = other._width1;
      _height1 = other._height1;
      return *this;
    }

    void ResizeToAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _width0 = node->getWidth();
        _height0 = node->getHeight();
      }
      int width = percent >= 1.0f ? _width1 : _width0 + (int) ( ( _width1 - _width0 ) * percent );
      int height = percent >= 1.0f ? _height1 : _height0 + (int) ( ( _height1 - _height0 ) * percent );
      node->resizeBy( width - node->getWidth(), height - node->getHeight() );
    }

    Action *ResizeToAction::copy()
    {
      return getFromPoolOrCreate( this, resizeToActionFactory );
    }

    Action *ResizeToActionFactory::createInstance() const
    {
      return new ResizeToAction( 0, 0, 0 );
    }
  }
}

