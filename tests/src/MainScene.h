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

#ifndef __MainScene_H_
#define __MainScene_H_

#include <CocosDL/CocosDL.h>

class MainScene : public cocosdl::Scene
{

public:
  MainScene();
  virtual ~MainScene();

  virtual void update( long long currentTimeMillis ) override;
};


#endif //__MainScene_H_
