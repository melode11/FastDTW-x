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
#include "SearchWindow.h"
#include "Assert.h"
#include <vector>
#include <limits>
FD_NS_START

using namespace std;

template <typename ValueType>
class MemoryResidentMatrix : public CostMatrix<ValueType>
{
    vector<ValueType> _cellValues;
    vector<JInt> _colOffsets;
    const SearchWindow* _window;
protected:
    MemoryResidentMatrix(const SearchWindow* searchWindow):_window(searchWindow),_cellValues(searchWindow->size()),_colOffsets(searchWindow->maxI()+1)
    {

//        memset(_cellValues.data(), 0, _cellValues.capacity()*sizeof(ValueType));
        JInt currentOffset = 0;
        for (JInt i = searchWindow->minI(); i<=searchWindow->maxI(); ++i) {
            _colOffsets[i] = currentOffset;
            currentOffset += searchWindow->minJForI(i) - searchWindow->minJForI(i) + 1;
        }
    }
public:
    
    void put(JInt col, JInt row, ValueType value)
    {
        FDASSERT(row>=_window->minJForI(col) && row <= _window->maxJForI(col), "CostMatrix is filled in a cell (col=%d, row=%d) that is not in the search window",col,row);
        _cellValues[_colOffsets[col] + row - _window->minJForI(col)] = value;
    }
    
    ValueType get(JInt col, JInt row) const
    {
        if (row < _window->minJForI(col) || row > _window->maxJForI(col)) {
            return numeric_limits<ValueType>::max();
        }
        else
        {
            return _cellValues[_colOffsets[col] + row - _window->minJForI(col)];
        }
    }
    
    JInt size() const
    {
        return _cellValues.size();
    }
};
FD_NS_END
#endif /* defined(__FastDTW_x__MemoryResidentMatrix__) */
