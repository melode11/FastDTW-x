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
#include <vector>
FD_NS_START
using namespace std;

//Add Traits for further optimize;
template <typename ValueType, JInt dimension>
struct PointTraits
{
    typedef vector<ValueType> point_type;
};

template <typename ValueType>
struct PointTraits<ValueType,1>
{
    typedef ValueType point_type;
};

template <typename ValueType>
class TimeSeriesPoint {
    vector<ValueType> _measurements;
    ValueType _sum;
    bool _sumValid;
    
public:
    TimeSeriesPoint(const vector<ValueType> meas):_measurements(meas), _sumValid(false),_sum(0)
    {

    }
    
    ValueType get(JInt dimension) const
    {
        return _measurements[dimension];
    }
    
    void set(JInt dimension,ValueType newValue)
    {
        if(_sumValid)
        {
            _sum -= _measurements[dimension];
            _sum += newValue;
        }
        _measurements[dimension] = newValue;
    }
    
    JInt size() const
    {
        return _measurements.size();
    }
    
    JInt toArray(ValueType* buff,JInt maxNum) const
    {
        JInt len = maxNum > size()? size():maxNum;
        memcpy(buff, _measurements.data(), len* sizeof(ValueType));
        return len;
    }
    
    const vector<ValueType>* toArray()
    {
        return &_measurements;
    }
    
    ValueType getSum()
    {
        if(!_sumValid)
        {
            _sumValid = true;
            ValueType tmp = 0;
            for (JInt i = 0 ; i<_measurements.size(); ++i) {
                tmp += _measurements[i];
            }
            _sum=tmp;
        }
        return _sum;
    }

    bool operator==(const TimeSeriesPoint& p) const
    {
        return _measurements == p._measurements;
    }
    
    bool operator<(TimeSeriesPoint& p)
    {
        return getSum()< p.getSum();
    }
    
    ~TimeSeriesPoint()
    {
    }
};

FD_NS_END
#endif /* defined(__FastDTW_x__TimeSeriesPoint__) */
