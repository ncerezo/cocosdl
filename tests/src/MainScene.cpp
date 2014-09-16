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


#include "MainScene.h"

using namespace cocosdl;
using namespace cocosdl::action;

MainScene::MainScene()
{
  Point center;
  getCenter( center );

  Sprite* background = new Sprite( "background.jpg" );
  background->setPosition( center );
  addChild( background );

  Sprite *piece1 = new Sprite( "piece.png" );
  piece1->setPosition( center );
  addChild( piece1 );

  Sprite *piece2 = (Sprite *) piece1->copy();
  addChild( piece2 );

  Sprite *piece3 = (Sprite *) piece1->copy();
  addChild( piece3 );

  piece1->addAction( new RepeatForeverAction( new RotateByAction( 100, 10.0 ) ) );

  piece2->addAction( new MoveByAction( 500, 0, -100 ) );

  SequenceAction* sequenceAction = new SequenceAction();
  sequenceAction->addAction( new MoveByAction( 500, -100, 0 ) );
  sequenceAction->addAction( new MoveByAction( 1000, 0, 200 ) );
  sequenceAction->addAction( new MoveByAction( 1000, 200, 0 ) );
  sequenceAction->addAction( new MoveByAction( 1000, 0, -200 ) );
  sequenceAction->addAction( new MoveByAction( 500, -100, 0 ) );

  SequenceAction* sequenceAction2 = new SequenceAction();
  sequenceAction2->addAction( new FadeOutAction( 1000 ) );
  sequenceAction2->addAction( new FadeInAction( 1000 ) );

  GroupAction* groupAction = new GroupAction();
  groupAction->addAction( new RepeatForeverAction( sequenceAction ) );
  groupAction->addAction( new RepeatForeverAction( sequenceAction2 ) );
  groupAction->addAction( new RepeatForeverAction( new RotateByAction( 5, 10.0 ) ) );

  piece2->addAction( new RepeatForeverAction( groupAction ) );

  SequenceAction* sequenceAction3 = new SequenceAction();
  sequenceAction3->addAction( new ResizeByAction( 1000, 60, 60 ) );
  sequenceAction3->addAction( new ResizeByAction( 1000, -60, -60 ) );

  SequenceAction* sequenceAction4 = new SequenceAction();
  sequenceAction4->addAction( new MoveByAction( 666, 200, 0 ) );
  sequenceAction4->addAction( new MoveByAction( 668, -400, 0 ) );
  sequenceAction4->addAction( new MoveByAction( 666, 200, 0 ) );

  GroupAction* groupAction1 = new GroupAction();
  groupAction1->addAction( sequenceAction3 );
  groupAction1->addAction( sequenceAction4 );
  piece3->addAction( new RepeatForeverAction( groupAction1 ) );
}

MainScene::~MainScene()
{

}

void MainScene::update( long long currentTimeMillis )
{
  Scene::update( currentTimeMillis );
}
