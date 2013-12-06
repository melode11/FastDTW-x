//
//  BinaryDistance.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/2/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__BinaryDistance__
#define __FastDTW_x__BinaryDistance__

#include "DistanceFunction.h"
#include "Assert.h"
FD_NS_START
template <typename ValueType>
class BinaryDistance : public DistanceFunction<ValueType>
{
public:
    BinaryDistance()
    {
        
    }
    
    ValueType calcDistance(const std::vector<ValueType>& v1, const std::vector<ValueType>& v2) const
    {
        FDASSERT0(v1.size()==v2.size(),"ERROR:  cannot calculate the distance between vectors of different sizes.");
        if (v1 == v2) {
            return (ValueType)0.0;
        }
        else
        {
            return (ValueType)1.0;
        }
    }
};

FD_NS_END
#endif /* defined(__FastDTW_x__BinaryDistance__) */
