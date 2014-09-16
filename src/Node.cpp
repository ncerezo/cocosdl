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

#include "Node.h"
#include "Game.h"
#include "Rect.h"
#include "Renderer.h"

using namespace std;
using namespace cocosdl::action;

namespace cocosdl {

  Node::Node() :
  _anchorX( 0.5f ),
  _anchorY( 0.5f ),
  _x( 0 ),
  _y( 0 ),
  _width( 0 ),
  _height( 0 ),
  _opacity( 1.0f ),
  _rotationAngle( 0.0 ),
  _clipping( false ),
  _parent( NULL ),
  _name( "" )
  {
  }

  Node::Node( const string &name ) :
  _anchorX( 0.5f ),
  _anchorY( 0.5f ),
  _x( 0 ),
  _y( 0 ),
  _width( 0 ),
  _height( 0 ),
  _opacity( 1.0f ),
  _rotationAngle( 0.0 ),
  _clipping( false ),
  _parent( NULL ),
  _name( name )
  {

  }


  Node::Node( const Node &other ) :
  _anchorX( other._anchorX ),
  _anchorY( other._anchorY ),
  _x( other._x ),
  _y( other._y ),
  _width( other._width ),
  _height( other._height ),
  _opacity( other._opacity ),
  _rotationAngle( other._rotationAngle ),
  _clipping( other._clipping ),
  _parent( NULL ),
  _name( std::string( other._name ) )
  {
    size_t count = other._children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = other._children.at( i );
      addChild( child->copy() );
    }
  }

  Node &Node::operator = ( const Node &other )
  {
    removeAll();
    _name = std::string( other._name );
    _anchorX = other._anchorX;
    _anchorY = other._anchorY;
    _x = other._x;
    _y = other._y;
    _width = other._width;
    _height = other._height;
    _opacity = other._opacity;
    _rotationAngle = other._rotationAngle;
    _clipping = other._clipping;
    if( _parent )
    {
      _parent->removeChild( this, false );
    }
    _parent = NULL;
    size_t count = other._children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = other._children.at( i );
      addChild( child->copy() );
    }
    return *this;
  }

  Node::~Node()
  {
    removeAll();
  }

  void Node::removeAll()
  {
    while( _children.size() > 0 )
    {
      Node *child = _children.back();
      _children.pop_back();
      delete child;
    }
  }

  void Node::addChild( Node *node )
  {
    if( node )
    {
      _children.push( node );
      node->_parent = this;
    }
  }

  void Node::insertChild( const unsigned position, Node *node )
  {
    if( !node )
    {
      return;
    }

    if( position >= _children.size() )
    {
      addChild( node );
    }
    else
    {
      vector<Node *>::iterator pos = _children.begin();
      if( position > 0 )
      {
        advance( pos, position );
      }
      _children.insert( pos, node );
      node->_parent = this;
    }
  }

  void Node::removeChild( Node *node, const bool cleanUp )
  {
    if( !node )
    {
      return;
    }

    _children.remove( node );
    if( cleanUp )
    {
      delete node;
    }
  }

  void Node::getDestinationRect( Rect &rect ) const
  {
    rect.setOrigin( getScreenX(), getScreenY() );
    rect.setDimension( _width, _height );
  }

  void Node::draw() const
  {

    Rect destinationRect;
    Rect currentClippingRect;

    getDestinationRect( destinationRect );

    Renderer *renderer = Game::getInstance()->getRenderer();
    if( _clipping )
    {
      renderer->getClipRect( currentClippingRect );
      renderer->setClipRect( destinationRect );
    }

    drawBeforeChildren( destinationRect );

    size_t count = _children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = _children.at( i );
      child->draw();
    }

    drawAfterChildren( destinationRect );

    if( _clipping )
    {
      renderer->setClipRect( currentClippingRect );
    }
  }

  void Node::setOpacity( const float opacity )
  {
    float correctedOpacity = opacity < 0.0f ? 0.0f : opacity > 1.0f ? 1.0f : opacity;
    blendOpacity( _opacity != 0 ? correctedOpacity / _opacity : correctedOpacity );
  }

  void Node::blendOpacity( const float factor )
  {
    if( _opacity != 0 )
    {
      _opacity *= factor;
    }
    else
    {
      _opacity = factor;
    }
    size_t count = _children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = _children.at( i );
      child->blendOpacity( factor );
    }
  }

  void Node::setRotationAngle( const double rotationAngle )
  {
    _rotationAngle = rotationAngle;
    size_t count = _children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = _children.at( i );
      child->setRotationAngle( rotationAngle );
    }
  }

  void Node::addAction( Action *action )
  {
    _actions.push( action );
  }

  void Node::runActions()
  {
    if( _actions.size() > 0 )
    {
      Action *action = _actions.front();
      if( action->getActionStatus() != Finished )
      {
        action->run( this );
        if( action->getActionStatus() == Finished )
        {
          _actions.pop();
          DESTROY_ACTION( action );
        }
      }
      else
      {
        _actions.pop();
        DESTROY_ACTION( action );
      }
    }
    size_t count = _children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = _children.at( i );
      child->runActions();
    }
    // the RemoveFromParentAction adds the nodes to remove to the _nodesToRemove queue, we have to remove them here
    // (we can't remove them on the previous loop or it will crash because contents of children will have changed)
    while( _nodesToRemove.size() > 0 )
    {
      Node *node = _nodesToRemove.front();
      _nodesToRemove.pop();
      removeChild( node, false );
    }
  }

  bool Node::hasActions() const
  {
    bool actions = _actions.size() > 0;
    size_t count = _children.size();
    for( size_t i = 0; !actions && i < count; i++ )
    {
      Node *child = _children.at( i );
      actions |= child->hasActions();
    }
    return actions;
  }

  void Node::stopAllActions( const bool restoreInitialStatus )
  {
    while( _actions.size() > 0 )
    {
      Action *action = _actions.front();
      _actions.pop();
      DESTROY_ACTION( action );
    }
    size_t count = _children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = _children.at( i );
      child->stopAllActions( restoreInitialStatus );
    }
  }

  void Node::getCenter( Point &point ) const
  {
    point.setLocation( _width / 2, _height / 2 );
  }

  bool Node::isPointInside( const int absoluteX, const int absoluteY ) const
  {
    Rect absoluteRect;
    getDestinationRect( absoluteRect );
    return absoluteRect.isPointInside( absoluteX, absoluteY );
  }

  bool Node::isPointInside( const Point &point ) const
  {
    Rect absoluteRect;
    getDestinationRect( absoluteRect );
    return absoluteRect.isPointInside( point );
  }

  Node *Node::copy() const
  {
    return new Node( *this );
  }

  Node *Node::getChildAtPoint( const int x, const int y ) const
  {
    Rect rect;
    getDestinationRect( rect );
    if( rect.isPointInside( x, y ) )
    {
      size_t count = _children.size();
      for( long i = count - 1; i >= 0; i-- )
      {
        Node *child = _children.at( (size_t) i );
        if( child->isPointInside( x, y ) )
        {
          Node *result = child->getChildAtPoint( x, y );
          if( result )
          {
            return result;
          }
          else
          {
            return child;
          }
        }
      }
      return NULL; // should never get this far
    }
    else
    {
      return NULL;
    }
  }

  void Node::drawBeforeChildren( Rect &destinationRect ) const
  {

  }

  void Node::drawAfterChildren( Rect &destinationRect ) const
  {

  }

  int Node::getScreenX() const
  {
    return ( _parent ? _parent->getScreenX() : 0 ) + _x - (int) ( _anchorX * _width );
  }

  int Node::getScreenY() const
  {
    return ( _parent ? _parent->getScreenY() : 0 ) + _y - (int) ( _anchorY * _height );
  }

  void Node::addNodeToRemove( Node *node )
  {
    _nodesToRemove.push( node );
  }

  int Node::translateX( const int x ) const
  {
    return _x - (int) ( _anchorX * _width ) + x;
  }

  int Node::translateY( const int y ) const
  {
    return _y - (int) ( _anchorY * _height ) + y;
  }

  void Node::setDimension( const int width, const int height )
  {
    _width = width;
    _height = height;

  }

  void Node::resizeBy( int widthDelta, int heightDelta )
  {
    _width += widthDelta;
    _height += heightDelta;
    size_t count = _children.size();
    for( size_t i = 0; i < count; i++ )
    {
      Node *child = _children.at( i );
      child->resizeBy( widthDelta, heightDelta );
    }
  }
}
