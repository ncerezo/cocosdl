//
// Created by Narciso Cerezo Jiménez on 15/09/14.
// Copyright (c) 2014 Narciso Cerezo. All rights reserved.
//



#include "Action.h"

#ifndef __ActionFactoryProtocol_H_
#define __ActionFactoryProtocol_H_

namespace cocosdl
{
  namespace action
  {
    class Action;

    class ActionFactory
    {
    public:
      virtual Action *createInstance() const = 0;
    };
  }
}



#endif //__ActionFactoryProtocol_H_
