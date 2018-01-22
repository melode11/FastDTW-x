//
//  WrapPath.cpp
//  FastDTW-x
//
//  Created by Melo Yao on 12/5/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#include "WarpPath.h"
#include <algorithm>
#include "FDAssert.h"

FD_NS_START

WarpPath::WarpPath(JInt initialCapacity) : _tsIindexes(),_tsJindexes()
{
    _tsIindexes.reserve(initialCapacity);
    _tsJindexes.reserve(initialCapacity);
}


JInt WarpPath::size() const
{
    return _tsIindexes.size();
}

JInt WarpPath::minI() const
{
    return _tsIindexes[0];
}

JInt WarpPath::minJ() const
{
    return _tsJindexes[0];
}

JInt WarpPath::maxI() const
{
    return _tsIindexes[_tsIindexes.size() - 1];
}

JInt WarpPath::maxJ() const
{
    return _tsJindexes[_tsJindexes.size() - 1];
}

void WarpPath::addFirst(JInt i, JInt j)
{
    _tsIindexes.insert(_tsIindexes.begin(), i);
    _tsJindexes.insert(_tsJindexes.begin(), j);
}

void WarpPath::addLast(JInt i, JInt j)
{
    _tsIindexes.push_back(i);
    _tsJindexes.push_back(j);
}

void WarpPath::getMatchingIndexesForI(JInt i,vector<JInt>& outVec) const
{
    //find first time i appears
    vector<JInt>::const_iterator it = find(_tsIindexes.begin(), _tsIindexes.end(), i);
    //find continuous indices of i.
    while (it != _tsIindexes.end() && *it == i)
    {
        outVec.push_back(_tsJindexes[it-_tsIindexes.begin()]);
        ++it;
    }
}

void WarpPath::getMatchingIndexesForJ(JInt j,vector<JInt>& outVec) const
{
    vector<JInt>::const_iterator it = find(_tsJindexes.begin(), _tsJindexes.end(), j);
    while (it!=_tsJindexes.end() && *it == j) {
        outVec.push_back(_tsIindexes[it-_tsJindexes.begin()]);
        ++it;
    }
}

void WarpPath::invertedCopy(WarpPath& path) const
{
    path._tsIindexes = _tsJindexes;
    path._tsJindexes = _tsIindexes;
}

void WarpPath::invert()
{
    vector<JInt> tmp = _tsIindexes;
    _tsIindexes = _tsJindexes;
    _tsJindexes = tmp;
}

ColMajorCell WarpPath::get(JInt index) const
{
    //Original Java code have boundary check bug here.
    //if ( (index>this.size()) || (index<0) )
    FDASSERT0(index>=0 && index<_tsIindexes.size(), "NoSuchElementException");
    return ColMajorCell(_tsIindexes[index],_tsJindexes[index]);
    
}

bool WarpPath::operator==(const WarpPath& path) const
{
    return _tsIindexes == path._tsIindexes && _tsJindexes == path._tsJindexes;
}

bool WarpPath::operator<(const WarpPath& path) const //For containers, so arbitery judgement works here.
{
    if (_tsIindexes==path._tsIindexes)
    {
        return _tsJindexes < path._tsJindexes;
    }
    else
    {
        return _tsIindexes < path._tsIindexes;
    }
}

void WarpPath::print(ostream& stream) const
{
    for (JInt i = 0; i<_tsIindexes.size(); ++i) {
        stream<<"("<<_tsIindexes[i]<<"," << _tsJindexes[i] << ") ";
    }
    stream<<"\n";
}

FD_NS_END