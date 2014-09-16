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

#include "Button.h"
#include "Texture.h"
#include "Label.h"
#include "SequenceAction.h"
#include "ResizeByAction.h"
#include "RepeatForeverAction.h"
#include "WaitAction.h"
#include "ResizeToAction.h"
#include "PlayEffectAction.h"

using namespace cocosdl::action;

namespace cocosdl {

  static long long PRESS_TIME = 200;
  static int PRESS_SIZE_DELTA = 8;
  static long long RELEASE_TIME = 200;
  static int ANIMATION_SIZE_DELTA = 4;
  static long long ANIMATION_RESIZE_TIME = 200;
  static long long ANIMATION_WAIT_TIME = 800;

  std::string Button::_soundEffect = "";

  Button::Button( Texture *texture, Label *label, ButtonType buttonType ) :
  Sprite( texture ),
  _label( label ),
  _pressedLabel( label ),
  _animation( NULL ),
  _pressAction( NULL ),
  _releaseAction( NULL ),
  _pressed( false ),
  _buttonListener( NULL ),
  _buttonType( buttonType ),
  _texture( texture ),
  _pressedTexture( texture )
  {
    init();
  }

  Button::Button( const std::string &textureFilePath, Label *label, ButtonType buttonType ) :
  Sprite(),
  _label( label ),
  _pressedLabel( label ),
  _animation( NULL ),
  _pressAction( NULL ),
  _releaseAction( NULL ),
  _pressed( false ),
  _buttonListener( NULL ),
  _buttonType( buttonType ),
  _texture( NULL ),
  _pressedTexture( NULL )
  {
    _texture = new Texture( textureFilePath );
    _pressedTexture = _texture;
    init();
  }

  Button::Button(
      const std::string &textureFilePath,
      const std::string &pressedTextureFilePath,
      Label *label,
      ButtonType buttonType
  ) :
  Sprite(),
  _label( label ),
  _pressedLabel( label ),
  _animation( NULL ),
  _pressAction( NULL ),
  _releaseAction( NULL ),
  _pressed( false ),
  _buttonListener( NULL ),
  _buttonType( buttonType ),
  _texture( NULL ),
  _pressedTexture( NULL )
  {
    _texture = new Texture( textureFilePath );
    _pressedTexture = new Texture( pressedTextureFilePath );
    init();
  }

  Button::Button( const Button &other ) : Sprite( other ), _pressed( false )
  {
    _label = other._label ? (Label *) other._label->copy() : NULL;
    if( other._pressedLabel )
    {
      if( other._label != other._pressedLabel )
      {
        _pressedLabel = (Label *) other._pressedLabel->copy();
      }
      else
      {
        _pressedLabel = _label;
      }
    }
    else
    {
      _pressedLabel = NULL;
    }
    addChild( _label );
    _animation = (RepeatForeverAction *) other._animation->copy();
    _pressAction = other._pressAction->copy();
    _releaseAction = other._releaseAction->copy();
    _buttonListener = other._buttonListener;
    if( other._texture )
    {
      _texture = new Texture( *other._texture );
    }
    else
    {
      _texture = NULL;
    }
    if( other._pressedTexture )
    {
      _pressedTexture = new Texture( *other._pressedTexture );
    }
    else
    {
      _pressedTexture = NULL;
    }
    if( _buttonType == ButtonTypeNormal )
    {
      addAction( _animation->copy() );
    }
  }

  Button::~Button()
  {
    DESTROY_ACTION( _animation );
    DESTROY_ACTION( _pressAction );
    DESTROY_ACTION( _releaseAction );
    if( _pressedTexture && _pressedTexture != _texture )
    {
      delete _pressedTexture;
    }
    if( _texture )
    {
      delete _texture;
    }
    if( _pressedLabel && _pressedLabel != _label )
    {
      removeChild( _pressedLabel, false );
      delete _pressedLabel;
    }
    if( _label )
    {
      removeChild( _label, false );
      delete _label;
    }
  }

  void Button::init()
  {
    setTexture( _texture );
    Point center;
    getCenter( center );
    _label->setPosition( center );
    addChild( _label );

    if( _pressedLabel && _pressedLabel != _label )
    {
      _pressedLabel->setPosition( center );
    }

    SequenceAction *sequence = new SequenceAction();
    sequence->addAction( new ResizeByAction( ANIMATION_RESIZE_TIME, ANIMATION_SIZE_DELTA, ANIMATION_SIZE_DELTA ) );
    sequence->addAction( new ResizeByAction( ANIMATION_RESIZE_TIME, -ANIMATION_SIZE_DELTA, -ANIMATION_SIZE_DELTA ) );
    sequence->addAction( new WaitAction( ANIMATION_WAIT_TIME ) );
    _animation = new RepeatForeverAction( sequence );

    _pressAction = new ResizeToAction( PRESS_TIME, _width - PRESS_SIZE_DELTA, _height - PRESS_SIZE_DELTA );
    _releaseAction = new ResizeToAction( RELEASE_TIME, _width, _height );

    if( _buttonType == ButtonTypeNormal )
    {
      addAction( _animation->copy() );
    }
  }

  Button &Button::operator = ( const Button &other )
  {
    Sprite::operator=( other );

    if( _pressedLabel && _pressedLabel != _label )
    {
      removeChild( _pressedLabel, false );
      delete _pressedLabel;
    }
    if( _label )
    {
      removeChild( _label, false );
      delete _label;
    }

    _label = other._label ? (Label *) other._label->copy() : NULL;
    if( other._pressedLabel )
    {
      if( other._label != other._pressedLabel )
      {
        _pressedLabel = (Label *) other._pressedLabel->copy();
      }
      else
      {
        _pressedLabel = _label;
      }
    }
    else
    {
      _pressedLabel = NULL;
    }

    // Animations are the same, so no need to remove and copy, we just keep them
    _buttonListener = other._buttonListener;
    if( other._texture )
    {
      _texture = new Texture( *other._texture );
    }
    else
    {
      _texture = NULL;
    }
    if( other._pressedTexture )
    {
      _pressedTexture = new Texture( *other._pressedTexture );
    }
    else
    {
      _pressedTexture = NULL;
    }
    return *this;
  }


  void Button::setLabel( Label *label )
  {
    if( _label )
    {
      removeChild( _label, false );
      delete _label;
    }
    _label = label;
    Point center;
    getCenter( center );
    _label->setPosition( center );
    if( !_pressed )
    {
      addChild( _label );
    }
  }

  void Button::setPressedLabel( Label *pressedLabel )
  {
    if( _pressedLabel && _pressedLabel != _label )
    {
      removeChild( _pressedLabel, false );
      delete _pressedLabel;
    }
    _pressedLabel = pressedLabel;
    Point center;
    getCenter( center );
    _pressedLabel->setPosition( center );
    if( _pressed )
    {
      addChild( _pressedLabel );
    }
  }

  Node *Button::copy()
  {
    return new Button( *this );
  }

  Node *Button::getChildAtPoint( int x, int y )
  {
    // We don't want to give access to the inner label
    return NULL;
  }

  void Button::press()
  {
    if( !_pressed )
    {
      _pressed = true;
      setTexture( _pressedTexture );
      removeChild( _label, false );
      addChild( _pressedLabel );
      stopAllActions( true );
      if( _buttonType != ButtonTypeToggle )
      {
        addAction( _pressAction->copy() );
      }
      if( _buttonType == ButtonTypeToggle && _buttonListener )
      {
        _buttonListener->OnClick( *this );
      }
    }
  }

  void Button::release()
  {
    release( false );
  }

  void Button::release( bool click )
  {
    if( _pressed )
    {
      _pressed = false;
      stopAllActions( true );
      setTexture( _texture );
      removeChild( _pressedLabel, false );
      addChild( _label );
      if( _buttonType != ButtonTypeToggle )
      {
        addAction( _releaseAction->copy() );
      }
      if( _buttonType == ButtonTypeNormal )
      {
        addAction( new WaitAction( 100 ) );
        addAction( _animation->copy() );
      }
      if( click || _buttonType == ButtonTypeToggle )
      {
        if( _soundEffect.length() > 0 )
        {
          addAction( new PlayEffectAction( _soundEffect ) );
        }
        if( _buttonListener )
        {
          _buttonListener->OnClick( *this );
        }
      }
    }
  }

  void Button::restartAnimation()
  {
    if( _buttonType == ButtonTypeNormal )
    {
      addAction( _animation->copy() );
    }
  }

  void Button::toggle()
  {
    if( _pressed )
    {
      release();
    }
    else
    {
      press();
    }
  }

}
