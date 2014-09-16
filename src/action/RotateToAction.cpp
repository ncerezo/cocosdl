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
#include "RotateToAction.h"

namespace cocosdl
{
  namespace action
  {
    static RotateToActionFactory rotateToActionFactory;

    static char const *const CLASS_NAME = "ResizeToAction";

    RotateToAction::RotateToAction( long long durationMs, double angle ) :
    TimedAction( durationMs ), _angle0( 0.0 ), _angle1( angle )
    {
      _className = CLASS_NAME;
    }

    RotateToAction::~RotateToAction()
    {

    }

    RotateToAction::RotateToAction( const RotateToAction &other ) :
    TimedAction( other._durationMs ), _angle0( 0.0 ), _angle1( other._angle1 )
    {
      _className = CLASS_NAME;
    }

    RotateToAction &RotateToAction::operator = ( const RotateToAction &other )
    {
      TimedAction::operator=( other );
      _angle0 = other._angle0;
      _angle1 = other._angle1;
      return *this;
    }

    void RotateToAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _angle0 = node->getRotationAngle();
      }
      double angle = percent >= 1.0f ? _angle1 : _angle0 + ( _angle1 * percent );
      int rotations = ( (int) angle ) / 360;
      angle -= rotations * 360.0;
      node->setRotationAngle( angle );
    }

    Action *RotateToAction::copy()
    {
      return getFromPoolOrCreate( this, rotateToActionFactory );
    }

    Action *RotateToActionFactory::createInstance() const
    {
      return new RotateToAction( 0, 0.0 );
    }
  }
}

