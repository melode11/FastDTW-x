//
//  DistanceFunction.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/2/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef FastDTW_x_DistanceFunction_h
#define FastDTW_x_DistanceFunction_h
#include "Foundation.h"
#include <vector>
FD_NS_START
template <typename ValueType>
class DistanceFunction
{
public:
    DistanceFunction()
    {
        
    }
    
    virtual ValueType calcDistance(const std::vector<ValueType>& v1, const std::vector<ValueType>& v2) const = 0;
};

FD_NS_END
#endif
