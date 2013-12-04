//
//  MemoryResidentMatrix.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/4/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__MemoryResidentMatrix__
#define __FastDTW_x__MemoryResidentMatrix__

#include "CostMatrix.h"
#include <vector>
FD_NS_START

using namespace std;

template <typename ValueType>
class MemoryResidentMatrix : public CostMatrix<ValueType>
{
    vector<ValueType> cellValues;
    vector<JInt> colOffsets;
public:
    void put(JInt col, JInt row, ValueType value)
    {
        
    }
    
    ValueType get(JInt col, JInt row) const
    {
        
    }
};
FD_NS_END
#endif /* defined(__FastDTW_x__MemoryResidentMatrix__) */
