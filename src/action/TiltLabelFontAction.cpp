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

#include "TiltLabelFontAction.h"
#include "Label.h"

namespace cocosdl
{
  namespace action
  {
    static TiltLabelFontActionFactory tiltLabelFontActionFactory;

    static char const *const CLASS_NAME = "TiltLabelFontAction";

    TiltLabelFontAction::TiltLabelFontAction( long long durationMs, int delta ) :
    TimedAction ( durationMs ), _delta( delta )
    {
      _className = CLASS_NAME;
    }

    TiltLabelFontAction::TiltLabelFontAction( const TiltLabelFontAction &other ) :
    TimedAction( other ), _delta( other._delta )
    {
      _className = CLASS_NAME;
    }

    TiltLabelFontAction::~TiltLabelFontAction()
    {
    }

    TiltLabelFontAction &TiltLabelFontAction::operator = ( const TiltLabelFontAction &other )
    {
      TimedAction::operator=( other );
      _delta = other._delta;
      return *this;
    }

    Action *TiltLabelFontAction::copy()
    {
      return getFromPoolOrCreate( this, tiltLabelFontActionFactory );
    }

    void TiltLabelFontAction::runStep( Node *node, float percent )
    {
      Label *label = dynamic_cast<Label *>( node );
      if( label )
      {
        label->setFontSize( label->getInitialFontSize() + (int) ( percent >= 1.0f ? _delta : _delta * percent ) );
      }
      else
      {
        setActionStatus( Finished, node );
      }
    }

    Action *TiltLabelFontActionFactory::createInstance() const
    {
      return new TiltLabelFontAction( 0, 0 );
    }
  }
}