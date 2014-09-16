//
// Created by Narciso Cerezo Jiménez on 15/09/14.
// Copyright (c) 2014 Narciso Cerezo. All rights reserved.
//


#include "Log.h"

namespace cocosdl
{
  std::ostream& Log::info()
  {
    return std::cout;
  }

  std::ostream &Log::debug()
  {
    return std::cout;
  }

  std::ostream &Log::warn()
  {
    return std::cout;
  }

  std::ostream &Log::error()
  {
    return std::cerr;
  }

  std::ostream &Log::fatal()
  {
    return std::cerr;
  }
}