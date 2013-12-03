//
//  ManhattanDistance.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/2/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__ManhattanDistance__
#define __FastDTW_x__ManhattanDistance__

#include "DistanceFunction.h"
#include "Assert.h"
#include "Math.h"
class ManhattanDistance
{
public:
    ManhattanDistance()
    {
        
    }
    
    template <typename ValueType>
    ValueType calcDistance(const std::vector<ValueType>& v1, const std::vector<ValueType>& v2)
    {
        FDASSERT0(v1.size()==v2.size(),"ERROR:  cannot calculate the distance between vectors of different sizes.");
        ValueType diffSum = 0;
        size_t size = v1.size();
        for (size_t i = 0; i<size; ++i)
        {
            diffSum += abs(v1[i] - v2[i]);
        }
        return diffSum;
    }
};

#endif /* defined(__FastDTW_x__ManhattanDistance__) */
