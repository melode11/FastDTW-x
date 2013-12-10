//
//  PAA.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/5/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__PAA__
#define __FastDTW_x__PAA__

#include "Foundation.h"
#include <vector>
#include "TimeSeries.h"
#include "Assert.h"
#include <cmath>
FD_NS_START
template <typename  ValueType,JInt nDimension>
class PAA : public TimeSeries<ValueType, nDimension>
{
    vector<JInt> _aggPtSize;
    JInt _originalLength;
public:
    
    PAA(const TimeSeries<ValueType,nDimension>& ts, JInt shrunkSize):_originalLength(ts.size()),_aggPtSize(shrunkSize)
    {
        FDASSERT(shrunkSize>0 && shrunkSize <= ts.size(),"ERROR:  The size of an aggregate representation must be greater than zero and \nno larger than the original time series. (shrunkSize=%d , origSize=%d).",shrunkSize,ts.size());
        // Ensures that the data structure storing the time series will not need
        //    to be expanded more than once.  (not necessary, for optimization)
        TimeSeries<ValueType,nDimension>::setMaxCapacity(shrunkSize);
        TimeSeries<ValueType,nDimension>::setLabels(*ts.getLabels());
        JDouble reducedPtSize = ts.size()/(JDouble)shrunkSize;
        JInt ptToReadFrom(0);
        JInt ptToReadTo;
        while (ptToReadFrom < ts.size()) {
            ptToReadTo = (JInt)round(reducedPtSize*(TimeSeries<ValueType,nDimension>::size()+1)) -1;
            JInt ptsToRead = ptToReadTo - ptToReadFrom + 1;
            JDouble timeSum(0.0);
            vector<ValueType> measurementSums(ts.numOfDimensions());
            for (JInt pt = ptToReadFrom; pt<ptToReadTo; ++pt) {
                const vector<ValueType> *currentPoint = ts.getMeasurementVector(pt);
                timeSum += ts.getTimeAtNthPoint(pt);
                for (JInt dim = 0; dim<ts.numOfDimensions(); ++dim) {
                    measurementSums[dim] += currentPoint[dim];
                }
            }
            // Determine the average value over the range ptToReadFrom...ptToReadFrom.
            timeSum = timeSum / ptsToRead;
            for (JInt dim = 0; dim<ts.numOfDimensions(); dim++) {
                measurementSums[dim] = measurementSums[dim] / ptsToRead;
            }
            
            _aggPtSize[TimeSeries<ValueType,nDimension>::size()] = ptsToRead;
            TimeSeries<ValueType,nDimension>::addLast(timeSum,TimeSeriesPoint<ValueType,nDimension>(measurementSums));
            ptToReadFrom = ptToReadTo + 1;
        }
    }
    
    JInt originalSize() const
    {
        return _originalLength;
    }
    
    JInt aggregatePtSize(JInt ptIndex)
    {
        return _aggPtSize[ptIndex];
    }
};

FD_NS_END
#endif /* defined(__FastDTW_x__PAA__) */
