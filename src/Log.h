//
// Created by Narciso Cerezo Jiménez on 15/09/14.
// Copyright (c) 2014 Narciso Cerezo. All rights reserved.
//

#ifndef __Log_H_
#define __Log_H_

#include <iostream>

namespace cocosdl
{
  class Log
  {
  public:
      static std::ostream& debug();
      static std::ostream& info();
      static std::ostream& warn();
      static std::ostream& error();
      static std::ostream& fatal();
  };
}

#endif //__Log_H_
