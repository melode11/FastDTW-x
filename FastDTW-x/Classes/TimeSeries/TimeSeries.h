//
//  TimeSeries.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/3/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__TimeSeries__
#define __FastDTW_x__TimeSeries__

#include "Foundation.h"
#include <vector>
#include <string>
#include "TimeSeriesPoint.h"
#include "Assert.h"

FD_NS_START
using namespace std;
template <typename ValueType>
class TimeSeries
{
private:
    static const JInt ZERO_ARRAY[0];
    static const JBool DEFAULT_IS_TIME_1ST_COL = true;
    static const JChar DEFAULT_DELIMITER = ',';
    static const JBool DEFAULT_IS_LABELED = true;
    
public:
    vector<string> labels;
    vector<JDouble> timeReadings;
    vector<TimeSeriesPoint<ValueType>> tsArray;
    
    TimeSeries():labels(),timeReadings(),tsArray()
    {
        
    }
    
    TimeSeries(JInt numOfDimensions):labels(numOfDimensions+1),timeReadings(),tsArray()
    {
        labels.push_back(string("time"));
        char buf[8];
        for (JInt i = 0; i<numOfDimensions; ++i) {
            snprintf(buf, 8, "%d",i);
            labels.push_back(string(buf));
        }
    }
    
    TimeSeries(TimeSeries& timeseries):labels(timeseries.lables),timeReadings(timeseries.timeReadings),tsArray(timeseries.tsArray)
    {
        
    }
    
    //ignored file io interfaces
    
    void clear()
    {
        labels.clear();
        timeReadings.clear();
        tsArray.clear();
    }
    
    JInt size() const
    {
        return timeReadings.size();
    }
    
    JInt numOfPts() const
    {
        return this->size();
    }
    
    JInt numOfDimensions() const
    {
        return labels.size() - 1;//potential bug when use default constructor
    }
    
    JDouble getTimeAtNthPoint(JInt n) const
    {
        return timeReadings[n];
    }
    
    string& getLabel(JInt n) const
    {
        return labels[n];
    }
    
    JInt getLabelsArr(string* strArr,JInt maxNum)
    {
        JInt len = maxNum>labels.size()?labels.size():maxNum;
        memcpy(strArr, labels.data(), len*sizeof(string));
        return len;
    }
    
    void setLabels(const vector<string> lbs)
    {
        labels = lbs;
    }
    
    void setLabels(const string* strArr,JInt num)
    {
        labels.clear();
        labels.reserve(num);
        copy(strArr, strArr+num, labels.begin());
    }
    
    ValueType getMeasurement(JInt pointIndex, string& valueLabel) const
    {
        JInt idx = find(labels.begin(), labels.end(), valueLabel) - labels.begin();
        FDASSERT(idx>0, "ERROR:  the label %s was not one of labels",valueLabel.data());
        return tsArray[pointIndex].get(idx - 1);
    }
    
    ValueType getMeasurement(JInt pointIndex, JInt valueIndex) const
    {
        return tsArray[pointIndex].get(valueIndex);
    }
    
    JInt getMeasurementVector(JInt pointIndex, ValueType* buf, JInt maxNum) const
    {
        return tsArray[pointIndex].toArray(buf,maxNum);
    }
    
    void setMeasurement(JInt pointIndex,JInt valueIndex,ValueType value)
    {
        tsArray[pointIndex].set(valueIndex,value);
    }
    
    void addFirst(JDouble time, TimeSeriesPoint<ValueType> const& values)
    {
        FDASSERT(values.size()+1 == labels.size(), "ERROR:  The TimeSeriesPoint contains the wrong number of values. expected:%d,found:%d",labels.size()-1,values.size());
        FDASSERT0(time<timeReadings[0], "ERROR:  The point being inserted into the beginning of the time series does not have the correct time sequence.");
        timeReadings.insert(timeReadings.begin(), time);
        tsArray.insert(timeReadings.begin(),values);
    }
    
    void addLast(JDouble time, TimeSeriesPoint<ValueType> const& values)
    {
        FDASSERT(values.size()+1 == labels.size(), "ERROR:  The TimeSeriesPoint contains the wrong number of values. expected:%d,found:%d",labels.size()-1,values.size());
        FDASSERT0(timeReadings.size()==0 || time>timeReadings[timeReadings.size() - 1], "ERROR:  The point being inserted into the beginning of the time series does not have the correct time sequence.");
        timeReadings.push_back(time);
        tsArray.push_back(values);
    }
};

FD_NS_END
#endif /* defined(__FastDTW_x__TimeSeries__) */
