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

FD_NS_END
#endif
