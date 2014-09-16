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

#ifndef __Button_H_
#define __Button_H_

#include "Sprite.h"

namespace cocosdl
{

  class Label;
  class Texture;
  class ButtonListener;
  class Scene;

  namespace action
  {
    class RepeatForeverAction;
    class Action;
  }

  enum ButtonType
  {
    ButtonTypeNormal, // Normal animated button
    ButtonTypeStatic, // Normal button with no animation
    ButtonTypeToggle  // Toggle button, changes status between pressed and released
  };

  /**
   * A button that can be pushed and trigger an action.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Button : public Sprite
  {

    friend class Scene; // Scene needs access to press and release

  public:

    /**
     * Get the sound effect to play when button is clicked.
     *
     * @return name of sound effect, by default an empty string meaning no sound effect.
     */
    static const std::string &getSoundEffect()
    {
      return _soundEffect;
    }

    /**
     * Set the sound effect to play when button is clicked.
     *
     * @param soundEffect a string with the sound effect name, blank means no sound effect.
     */
    static void setSoundEffect( const std::string &soundEffect )
    {
      _soundEffect = soundEffect;
    }

    /**
     * Create a new button.
     *
     * @param texture the texture to use for the button
     * @param label the label to draw over the texture
     * @param buttonType one of the ButtonType options
     */
    Button( Texture *texture, Label *label, ButtonType buttonType = ButtonTypeNormal );

    /**
     * Create a new button.
     *
     * @param textureFilePath the file path of the texture to use for the button
     * @param label the label to draw over the texture
     * @param buttonType one of the ButtonType options
     */
    Button( const std::string &textureFilePath, Label *label, ButtonType buttonType = ButtonTypeNormal );

    /**
     * Create a new button.
     *
     * @param textureFilePath the file path of the texture to use for the button released status
     * @param pressedTextureFilePath the file path of the texture to use for the button pressed status
     * @param label the label to draw over the texture
     * @param buttonType one of the ButtonType options
     */
    Button(
        const std::string &textureFilePath,
        const std::string &pressedTextureFilePath,
        Label *label,
        ButtonType buttonType = ButtonTypeNormal
    );

    /**
     * Copy constructor.
     *
     * @param other the other object to copy from
     */
    Button( const Button &other );

    virtual ~Button();

    Button &operator = ( const Button &other );

    /**
     * Create a copy of the object with the same class and deep copied properties.
     *
     * @return a new node deep copied from this one with the same class
     */
    virtual Node *copy();

    /**
     * Get the button listener. A button listener is notified when events occur in the button.
     *
     * @return the button listener, NULL by default
     */
    ButtonListener *getButtonListener() const
    {
      return _buttonListener;
    }

    /**
     * Set the button listener.
     *
     * @param buttonListener the button listener. Set to NULL to remove.
     */
    void setButtonListener( ButtonListener *buttonListener )
    {
      _buttonListener = buttonListener;
    }

    /**
     * Restart button animation.
     */
    void restartAnimation();

    /**
     * Overrides the default getChildAtPoint to return always NULL, so no inner child will ever get the focus, just the
     * button.
     *
     * @param x the x point in absolute screen coordinates
     * @param y the y point in absolute screen coordinates
     * @return NULL
     */
    virtual Node *getChildAtPoint( int x, int y );

    /**
     * Change the button to the pressed status (only for ButtonTypeToggle).
     */
    void press();

    /**
     * Change the button to the released status (only for ButtonTypeToggle).
     */
    void release();


    Label *getLabel() const
    {
      return _label;
    }

    /**
     * Set the label for the normal status. Takes ownership of the label, and will free it when needed.
     * @param label the label
     */
    void setLabel( Label *label );

    Label *getPressedLabel() const
    {
      return _pressedLabel;
    }

    /**
     * Set the label for the pressed status. Takes ownership of the label, and will free it when needed.
     * @param pressedLabel the label
     */
    void setPressedLabel( Label *pressedLabel );


    ButtonType const &getButtonType() const
    {
      return _buttonType;
    }

    bool isPressed() const
    {
      return _pressed;
    }

  private:
    static std::string _soundEffect;

    Label *_label;
    Label *_pressedLabel;
    action::RepeatForeverAction *_animation;
    action::Action *_pressAction;
    action::Action *_releaseAction;
    bool _pressed;
    ButtonListener *_buttonListener;
    ButtonType _buttonType;
    Texture *_texture;
    Texture *_pressedTexture;

    void init();

    void release( bool click );

    void toggle();
  };

  /**
   * A ButtonListener receives notifications about button status changes.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class ButtonListener
  {

  public:
    /**
     * The button has been clicked.
     *
     * @param button the button being clicked.
     */
    virtual void OnClick( const Button &button ) = 0;
  };

}

#endif //__Button_H_
