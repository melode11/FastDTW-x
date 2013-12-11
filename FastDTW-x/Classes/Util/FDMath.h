//
//  Math.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/2/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef FastDTW_x_Math_h
#define FastDTW_x_Math_h
#include "Foundation.h"
FD_NS_START

template <typename ValueType>
ValueType abs(ValueType value){return value>=0?value:-value;}

template <typename ValueType>
ValueType max(ValueType v1,ValueType v2){return v1>v2?v1:v2;}

template <typename ValueType>
ValueType min(ValueType v1,ValueType v2){return v1>v2?v2:v1;}

FD_NS_END
#endif
