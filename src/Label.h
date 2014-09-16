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

#ifndef __Label_H_
#define __Label_H_

#include "Sprite.h"
#include "Color.h"
#include <string>
#include <SDL2_ttf/SDL_ttf.h>

namespace cocosdl {

  /**
   * A text label.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Label : public Sprite
  {

  public:

    /**
     * Get the default font used for new labels.
     *
     * @return font name, blank by default. You must first set it to use the simple constructor.
     */
    static const std::string &getDefaultFont()
    {
      return _defaultFont;
    }

    /**
     * Set the default font for new labels.
     *
     * @param defaultFont default font name
     */
    static void setDefaultFont( const std::string &defaultFont )
    {
      _defaultFont = defaultFont;
    }

    /**
     * Get the default font size, in points.
     *
     * @return default font size
     */
    static int getDefaultFontSize()
    {
      return _defaultFontSize;
    }

    /**
     * Set the default font size, in points.
     *
     * @param defaultFontSize default font size in points
     */
    static void setDefaultFontSize( int defaultFontSize )
    {
      _defaultFontSize = defaultFontSize;
    }

    /**
     * Get the default font color.
     *
     * @return default font color
     */
    static const Color &getDefaultColor()
    {
      return _defaultColor;
    }

    /**
     * Set the default font color.
     *
     * @param defaultColor defaunt font color
     */
    static void setDefaultColor( const Color &defaultColor )
    {
      _defaultColor = defaultColor;
    }

    /**
     * Create a new label using the default font name, size and color. You must first set the font name at least.
     *
     * @param text text for the label
     */
    Label( const std::string &text );

    /**
     * Create a new label with the given font, and font size (using the default font color).
     *
     * @param fontName font name
     * @param fontSize font size in points
     * @param text text
     */
    Label( const std::string &fontName, const int fontSize, const std::string &text );

    Label( const Label &other );

    virtual ~Label();

    Label &operator = ( const Label &other );

    /**
     * Get the label text.
     *
     * @return label text
     */
    const std::string &getText() const
    {
      return _text;
    }

    /**
     * Get the label color.
     *
     * @return label color
     */
    const Color &getColor() const
    {
      return _color;
    }

    /**
     * Set the label color.
     *
     * @param color label color
     */
    void setColor( const Color &color );

    /**
     * Set the label text.
     *
     * @text text
     */
    void setText( const std::string &text );

    /**
     * Set the label font.
     *
     * @param fontName font name
     * @param fontSize font size in points
     */
    void setFont( const std::string &fontName, const int fontSize );

    /**
     * Get the font name.
     *
     * @return font name
     */
    const std::string &getFontName() const
    {
      return _fontName;
    }

    /**
     * Set the font name.
     *
     * @param fontName font name
     */
    void setFontName( const std::string &fontName );

    /**
     * Get the font size.
     *
     * @return font size in points.
     */
    const int getFontSize() const
    {
      return _fontSize;
    }

    /**
     * Set the font size.
     *
     * @param fontSize font size in points.
     */
    void setFontSize( const int fontSize );

    /**
     * Get the initial font size. The initial font size is established when the label is created, and it's used to
     * restore the label to the initial font size when restoring the label state after running actions.
     *
     * @return initial font size in points
     */
    const int getInitialFontSize() const
    {
      return _initialFontSize;
    }

    /**
     * Set the initial font size. See getInitialFontSize.
     *
     * @param initialFontSize initial font size in points.
     */
    void setInitialFontSize( const int initialFontSize )
    {
      _initialFontSize = initialFontSize;
    }

    /**
     * Create a copy of the object with the same class and deep copied properties.
     *
     * @return a new node deep copied from this one with the same class
     */
    virtual Node *copy() const;

    /**
     * Stop (and free) all current actions. If restoreInitialStatus is true, the node is restored to it's initial status.
     * That is dependent on the subclass implementation.
     *
     * @param restoreInitialStatus restore node initial status
     */
    virtual void stopAllActions( const bool restoreInitialStatus );

  private:
    static std::string  _defaultFont;
    static int          _defaultFontSize;
    static Color        _defaultColor;

    std::string         _text;
    TTF_Font            *_font;
    Color               _color;
    std::string         _fontName;
    int                 _fontSize;
    int                 _initialFontSize;

    void updateTexture();

    // ToDo: alignment
  };

}

#endif //__Label_H_
