//
//  TimeSeriesPoint.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/3/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__TimeSeriesPoint__
#define __FastDTW_x__TimeSeriesPoint__
#include "Foundation.h"
#include <algorithm>

FD_NS_START
template <typename ValueType>
class TimeSeriesPoint {
    ValueType* measurements;
    JInt numMeasurement;
    ValueType sum;
    bool sumValid;
    
public:
    TimeSeriesPoint(const ValueType* meas,JInt num):sumValid(false),numMeasurement(num),sum(0)
    {
        measurements = new ValueType[num];
        memcpy(measurements, meas, num*sizeof(ValueType));

    }
    
    ValueType get(JInt dimension) const
    {
        return measurements[dimension];
    }
    
    void set(JInt dimension,ValueType newValue)
    {
        if(sumValid)
        {
            sum -= measurements[dimension];
            sum += newValue;
        }
        measurements[dimension] = newValue;
    }
    
    JInt size() const
    {
        return numMeasurement;
    }
    
    JInt toArray(ValueType* buff,JInt maxNum) const
    {
        JInt len = maxNum > numMeasurement? numMeasurement:maxNum;
        memcpy(buff, measurements, len* sizeof(ValueType));
        return len;
    }
    
    ValueType getSum()
    {
        if(!sumValid)
        {
            sumValid = true;
            ValueType tmp = 0;
            for (JInt i = 0 ; i<numMeasurement; ++i) {
                tmp += measurements[i];
            }
            sum=tmp;
        }
        return sum;
    }

    bool operator==(const TimeSeriesPoint& p) const
    {
        if (p.numMeasurement == numMeasurement) {
            return std::equal(measurements, measurements+numMeasurement, p.measurements);
        }
        return false;
    }
    
    bool operator<(TimeSeriesPoint& p)
    {
        return getSum()< p.getSum();
    }
    
    ~TimeSeriesPoint()
    {
        if (measurements) {
             delete [] measurements;
        }
    }
};

FD_NS_END
#endif /* defined(__FastDTW_x__TimeSeriesPoint__) */
