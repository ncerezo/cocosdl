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
#include "RotateByAction.h"

namespace cocosdl
{
  namespace action
  {
    static RotateByActionFactory rotateByActionFactory;

    static char const *const CLASS_NAME = "RotateByAction";

    RotateByAction::RotateByAction( long long durationMs, double angleDelta ) :
    TimedAction( durationMs ), _angle0( 0.0 ), _angleDelta( angleDelta )
    {
      _className = CLASS_NAME;
    }

    RotateByAction::~RotateByAction()
    {

    }

    RotateByAction::RotateByAction( const RotateByAction &other ) :
    TimedAction( other._durationMs ), _angle0( 0.0 ), _angleDelta( other._angleDelta )
    {
      _className = CLASS_NAME;
    }

    RotateByAction &RotateByAction::operator = ( const RotateByAction &other )
    {
      TimedAction::operator=( other );
      _angle0 = other._angle0;
      _angleDelta = other._angleDelta;
      return *this;
    }

    void RotateByAction::runStep( Node *node, float percent )
    {
      assert( node != NULL );
      if( _actionStatus == Created )
      {
        _angle0 = node->getRotationAngle();
      }
      double delta = percent >= 1.0f ? _angleDelta : _angleDelta * percent;
      double angle = _angle0 + delta;
      int rotations = ( (int) fabs( angle ) ) / 360;
      if( angle >= 0.0 )
      {
        angle -= rotations * 360.0;
      }
      else
      {
        angle += ( rotations + 1 ) * 360.0;
      }
      node->setRotationAngle( angle );
    }

    Action *RotateByAction::copy()
    {
      return getFromPoolOrCreate( this, rotateByActionFactory );
    }

    Action *RotateByActionFactory::createInstance() const
    {
      return new RotateByAction( 0, 0.0 );
    }
  }
}