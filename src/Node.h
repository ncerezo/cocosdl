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

#ifndef __Node_H_
#define __Node_H_

#include <vector>
#include <queue>
#include <string>
#include <map>
#include "Action.h"
#include "Point.h"
#include "Rect.h"
#include "NodeVector.h"

namespace cocosdl
{
  class Game;
  class Rect;
  class Point;

  /**
   * Node is the base class for all graphical objects. A node represents an item or layer in the game "scene". It
   * can contain other nodes, effectively creating a tree of nodes.<br/>
   * All actions and settings applied to a node are in turn applied to all its children.<br/>
   * Children are drawn in the order they are added to the parent, so last added nodes draw on top of earlier nodes.<br/>
   * Nodes are positioned relative to their parent.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Node
  {

    friend class Game;

  public:
    /**
     * Create a new empty node.
     */
    Node();

    /**
     * Create a new empty node.
     *
     * @param name node name
     */
    Node( std::string const &name );

    Node( const Node &other );

    virtual ~Node();

    Node &operator = ( const Node &other );

    /**
     * Draw the node on the screen. This method can be overridden by subclasses, but they must also call it first.
     * The preferred way to implement custom drawing is to override drawBeforeChildren or drawAfterChildren.
     */
    virtual void draw() const;

    /**
     * Determine if an absolute point is inside this node.
     *
     * @param absoluteX point absolute x position
     * @param absoluteY point absolute y position
     * @param true if it's inside, false otherwise
     */
    bool isPointInside( const int absoluteX, const int absoluteY ) const;

    /**
     * Determine if an absolute point is inside this node.
     *
     * @param point point with absolute x and y positions
     * @param true if it's inside, false otherwise
     */
    bool isPointInside( const Point& point ) const;

    /**
     * Get the node name.
     *
     * @return node name
     */
    const std::string &getName() const
    {
      return _name;
    }

    /**
     * Set the node name.
     *
     * @param name node name
     */
    void setName( const std::string &name )
    {
      _name = name;
    }

    /**
     * Add a child node. Nodes are managed by their parents, so when a node is destroyed it automatically destroys all
     * its children in turn. So if you add a node to another node, you just have to take care of the parent.
     *
     * @parent node child node
     */
    void addChild( Node *node );

    /**
     * Insert a node into the given position.
     *
     * @param position position to add the node to, moving the resto of the nodes (if any) forward (top)
     * @param node child to add
     */
    void insertChild( const unsigned position, Node *node );

    /**
     * Remove a given child node.
     *
     * @param node node to remove
     * @param cleanUp if true the node is also deleted, if false it's up to you to free it.
     */
    void removeChild( Node *node, const bool cleanUp = true );

    /**
     * Get the node X position (parent-relative)
     *
     * @return x position
     */
    int getX() const
    {
      return _x;
    }

    /**
     * Set the node X position (parent-relative).
     *
     * @param x x position
     */
    void setX( const int x )
    {
      _x = x;
    }

    /**
     * Get the node Y position (parent-relative)
     *
     * @return y position
     */
    int getY() const
    {
      return _y;
    }

    /**
     * Set the node Y position (parent-relative).
     *
     * @param y y position
     */
    void setY( const int y )
    {
      _y = y;
    }

    /**
     * Set the node position (parent-relative).
     *
     * @param x y position
     * @param y y position
     */
    void setPosition( const int x, const int y )
    {
      _x = x;
      _y = y;
    }

    /**
     * Set the node position (parent-relative).
     *
     * @param point position
     */
    void setPosition( const Point &point )
    {
      _x = point.getX();
      _y = point.getY();
    }

    /**
     * Get the node width.
     *
     * @return width
     */
    int getWidth() const
    {
      return _width;
    }

    /**
     * Set the node width.
     *
     * @param width width
     */
    void setWidth( const int width )
    {
      _width = width;
    }

    /**
     * Get the node height.
     *
     * @return height
     */
    int getHeight() const
    {
      return _height;
    }

    /**
     * Set the node height.
     *
     * @param height height
     */
    void setHeight( const int height )
    {
      _height = height;
    }

    /**
     * Set the node dimensions and position
     *
     * @param rect rectangle with origin point and dimensions
     */
    void setRect( const Rect& rect )
    {
      _x = rect.getX();
      _y = rect.getY();
      _width = rect.getWidth();
      _height = rect.getHeight();
    }

    /**
     * Set the node dimensions.
     *
     * @param width width
     * @param height height
     */
    void setDimension( const int width, const int height );

    /**
     * Get the node anchor x factor. Represents the relative position in the node width (from 0.0 to 1.0) to calculate
     * the actual x coordinate.
     *
     * @return anchor x factor
     */
    float getAnchorX() const
    {
      return _anchorX;
    }

    void setAnchorX( const float anchorX )
    {
      _anchorX = anchorX < 0.0f ? 0.0f : anchorX > 1.0f ? 1.0f : anchorX;
    }

    /**
     * Get the node anchor y factor. Represents the relative position in the node height (from 0.0 to 1.0) to calculate
     * the actual y coordinate.
     *
     * @return anchor y factor
     */
    float getAnchorY() const
    {
      return _anchorY;
    }

    void setAnchorY( const float anchorY )
    {
      _anchorY = anchorY < 0.0f ? 0.0f : anchorY > 1.0f ? 1.0f : anchorY;
    }

    /**
     * Set the anchor point (see getAnchorX).
     *
     * @return anchor x factor
     * @return anchor y factor
     */
    void setAnchor( const float x, const float y )
    {
      _anchorX = x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
      _anchorY = y < 0.0f ? 0.0f : y > 1.0f ? 1.0f : y;
    }

    /**
     * Get node opacity, from 0.0 (transparent) to 1.0.
     *
     * @return node opacity
     */
    float getOpacity() const
    {
      return _opacity;
    }

    void setOpacity( const float opacity );

    /**
     * Get the rotation angle in degrees.
     *
     * @return rotation angle in degrees
     */
    double getRotationAngle() const
    {
      return _rotationAngle;
    }

    void setRotationAngle( const double rotationAngle );

    /**
     * Check if the node is performing clipping to its rectangle when drawing.
     *
     * @return if the node is clipping.
     */
    bool getClipping() const
    {
      return _clipping;
    }

    void setClipping( const bool clipping )
    {
      _clipping = clipping;
    }

    /**
     * Get the parent node.
     *
     * @return parent node
     */
    Node *getParent() const
    {
      return _parent;
    }

    /**
     * Get the node children.
     *
     * @return node chilren
     */
    std::vector<Node *> const &getChildren() const
    {
      return _children;
    }

    /**
     * Get the topmost child at these absolute coordinates.
     *
     * @param x the x point in absolute screen coordinates
     * @param y the y point in absolute screen coordinates
     * @return topmost child at coordinates, NULL if none.
     */
    virtual Node *getChildAtPoint( const int x, const int y ) const;

    /**
     * Create a copy of the object with the same class and deep copied properties.
     *
     * @return a new node deep copied from this one with the same class
     */
    virtual Node *copy() const;

    /**
     * Get the rectangle representing this node area in actual screen coordinates.
     *
     * @param rectangle rectangle to fill
     */
    void getDestinationRect( Rect &rect ) const;

    /**
     * Get the center point in this node relative coordinates (half width and half height).
     *
     * @param point point to fill
     */
    void getCenter( Point &point ) const;

    /**
     * Get the node screen X position.
     *
     * @return x screen position
     */
    int getScreenX() const;

    /**
     * Get the node screen Y position.
     *
     * @return y screen position
     */
    int getScreenY() const;

    /**
     * Translate a point from a child into this node coordinates.
     *
     * @return x child x position
     */
    int translateX( const int x ) const;

    /**
     * Translate a point from a child into this node coordinates.
     *
     * @return y child x position
     */
    int translateY( const int y ) const;

    /**
     * Check if the node has actions running.
     *
     * @return true if so
     */
    bool hasActions() const;

    /**
     * Stop (and free) all current actions. If restoreInitialStatus is true, the node is restored to it's initial status.
     * That is dependent on the subclass implementation.
     *
     * @param restoreInitialStatus restore node initial status
     */
    virtual void stopAllActions( const bool restoreInitialStatus );

    /**
     * Add an action to the node. When the action is completed it is automatically freed, so you must not reuse it.<br/>
     * To reuse actions, define them and then add a copy of the action to a node, not the action itself.
     */
    void addAction( action::Action *action );

    /**
     * Add a node to the remove list. When the actions running on the node are finished, the child node is removed,
     * though it is not freed. You must take care of that.
     */
    void addNodeToRemove( Node *node );

    /**
     * Remove all child nodes (and delete them).
     */
    void removeAll();

    void resizeBy( int widthDelta, int heightDelta );

  protected:
    float     _anchorX;
    float     _anchorY;
    int       _x;
    int       _y;
    int       _width;
    int       _height;
    float     _opacity;
    double    _rotationAngle;
    bool      _clipping;
    Node      *_parent;

    /**
     * Perform custom drawing before the node draws its children, so they are drawn on top.
     *
     * @param destinationRect already calculated screen destination rect.
     */
    virtual void drawBeforeChildren( Rect &destinationRect ) const;

    /**
     * Perform custom drawing after the node draws its children, so they are drawn below.
     *
     * @param destinationRect already calculated screen destination rect.
     */
    void drawAfterChildren( Rect &destinationRect ) const;


  private:
    std::string                   _name;
    util::NodeVector              _children;
    std::queue<action::Action *>  _actions;
    std::queue<Node *>            _nodesToRemove;

    /**
     * Run this nodes actions. This is only invoked from Game.
     */
    void runActions();

    void blendOpacity( float const factor );
  };

}

#endif //__Node_H_
