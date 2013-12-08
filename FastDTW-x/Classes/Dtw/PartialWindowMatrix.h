//
//  PartialWindowMatrix.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/8/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__PartialWindowMatrix__
#define __FastDTW_x__PartialWindowMatrix__

#include "Foundation.h"
#include <vector>
#include "CostMatrix.h"
#include "SearchWindow.h"

using namespace std;
FD_NS_START
template <typename ValueType>
class PartialWindowMatrix : public CostMatrix<ValueType>
{
    vector<ValueType> _lastCol;
    vector<ValueType> _currCol;
    JInt _currColIndex;
    JInt _minLastRow;
    JInt _minCurrRow;
    const SearchWindow *_window;
    
    PartialWindowMatrix(const SearchWindow* searchWindow):_window(searchWindow),_lastCol(),_currCol()
    {
        if (searchWindow->maxI() > 0) {
            _currCol.resize(searchWindow->maxJForI(1) - searchWindow->minJForI(1) + 1);
            _currColIndex = 1;
            _minLastRow = searchWindow->minJForI(_currColIndex - 1);
        }
        else
        {
            _currColIndex = 0;
            _minLastRow = 0;
        }
        _minCurrRow = searchWindow->minJForI(_currColIndex);
        _lastCol.resize(searchWindow->maxJForI(0) - searchWindow->minJForI(0) + 1);
    }
    
};
FD_NS_END
#endif /* defined(__FastDTW_x__PartialWindowMatrix__) */
