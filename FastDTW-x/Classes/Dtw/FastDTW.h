//
//  FastDTW.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/9/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__FastDTW__
#define __FastDTW_x__FastDTW__

#include "Foundation.h"
#include "DTW.h"
#include "PAA.h"
#include "ExpandedResWindow.h"

//#include "TimeWarpInfo.h"
//#include "TimeSeries.h"

FD_NS_START
extern const JInt DEFAULT_SEARCH_RADIUS;

template <typename ValueType>
inline ValueType getWarpDistBetween(TimeSeries<ValueType> const& tsI,TimeSeries<ValueType> const& tsJ, DistanceFunction<ValueType> const& distFn)
{
    return getWarpInfoBetween(tsI, tsJ, DEFAULT_SEARCH_RADIUS, distFn).getDistance();
}

template <typename ValueType>
inline TimeWarpInfo<ValueType> getWarpInfoBetween(TimeSeries<ValueType> const& tsI,TimeSeries<ValueType> const& tsJ,DistanceFunction<ValueType> const& distFn)
{
    return getWarpInfoBetween(tsI, tsJ, DEFAULT_SEARCH_RADIUS, distFn);
}

template <typename ValueType>
inline ValueType getWarpDistBetween(TimeSeries<ValueType> const& tsI,TimeSeries<ValueType> const& tsJ,
                                     JInt searchRadius,DistanceFunction<ValueType> const& distFn)
{
    return getWarpInfoBetween(tsI, tsJ, searchRadius, distFn).getDistance();
}

template <typename ValueType>
TimeWarpInfo<ValueType> getWarpInfoBetween(TimeSeries<ValueType> const& tsI, TimeSeries<ValueType> const& tsJ, JInt searchRadius, DistanceFunction<ValueType> const& distFn)
{
    if (searchRadius < 0) {
        searchRadius = 0;
    }
    JInt minTSsize = searchRadius + 2;
    if (tsI.size() <= minTSsize || tsJ.size()<=minTSsize) {
        return DTW::getWarpInfoBetween(tsI, tsJ, distFn);
    }
    else
    {
        JDouble resolutionFactor = 2.0;
        PAA<ValueType> shrunkI(tsI,(JInt)(tsI.size()/resolutionFactor));
        PAA<ValueType> shrunkJ(tsJ,(JInt)(tsJ.size()/resolutionFactor));
        // Determine the search window that constrains the area of the cost matrix that will be evaluated based on
        //    the warp path found at the previous resolution (smaller time series).
        TimeWarpInfo<ValueType> warpInfo = getWarpInfoBetween(shrunkI, shrunkJ, searchRadius, distFn);
        ExpandedResWindow<ValueType> window(tsI, tsJ, shrunkI, shrunkJ,
                                                    *(warpInfo.getPath()),
                                                          searchRadius);
        return DTW::getWarpInfoBetween(tsI, tsJ, window, distFn);
    }
    
}

FD_NS_END
#endif /* defined(__FastDTW_x__FastDTW__) */
