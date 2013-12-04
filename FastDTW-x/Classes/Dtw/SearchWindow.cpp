//
//  SearchWindow.cpp
//  FastDTW-x
//
//  Created by Melo Yao on 12/4/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#include "SearchWindow.h"
#include "Assert.h"

FD_NS_START

SearchWindowIterator::SearchWindowIterator(SearchWindow* w):_window(w),_hasMoreElements(w->size()>0),_currentI(w->minI()),_currentJ(w->minJ())
{
    
}

JBool SearchWindowIterator::hasNext()
{
    return _hasMoreElements;
}

ColMajorCell SearchWindowIterator::next()
{
    FDASSERT0(_window->getModCount() == _expectedModCount, "ConcurrentModificationException");
    FDASSERT0(_hasMoreElements, "NoSuchElementException");
    ColMajorCell cell(_currentI,_currentJ);
    if(++_currentJ > _window->maxJForI(_currentI))
    {
        if (++_currentI<=_window->maxI()) {
            _currentJ = _window->minJForI(_currentI);
        }
        else
        {
            _hasMoreElements = false;
        }
    }
    return cell;
}

SearchWindow::SearchWindow(JInt tsIsize, JInt tsJsize):_minValues(tsIsize),_maxValues(tsIsize),_maxJ(tsJsize -1),_size(0),_modCount(0)
{
    fill(_minValues.begin(), _minValues.end(), -1);
    fill(_maxValues.begin(), _maxValues.end(), 0);
}

SearchWindow::~SearchWindow()
{
    
}

JBool SearchWindow::isInWindow(JInt i, JInt j) const
{
    return (i>=minI())&&(i<=maxI())&&(_minValues[i]<=j)&&(_maxValues[i]>=j);
}

JInt SearchWindow::minI() const
{
    return 0;
}

JInt SearchWindow::maxI() const
{
    return _minValues.size() - 1;
}

JInt SearchWindow::minJ() const
{
    return 0;
}

JInt SearchWindow::maxJ() const
{
    return _maxJ;
}

JInt SearchWindow::minJForI(JInt i) const
{
    return _minValues[i];
}

JInt SearchWindow::maxJForI(JInt i) const
{
    return _maxValues[i];
}

JInt SearchWindow::size() const
{
    return _size;
}

JInt SearchWindow::getModCount() const
{
    return _modCount;
}

void SearchWindow::expandSearchWindow(JInt radius)
{
    
}

void SearchWindow::expandWindow(JInt radius)
{
    
}

void SearchWindow::markVisited(JInt col, JInt row)
{
    if (_minValues[col] == -1) {
        _minValues[col] = row;
        _maxValues[col] = row;
        _size++;
        _modCount++;
    }
    else if(_maxValues[col]>row)
    {
        _size+=_minValues[col] - row;
        _minValues[col] = row;
        _modCount++;
    }
    else if(_maxValues[col]<row)
    {
        _size+=row - _maxValues[col];
        _maxValues[col] = row;
        _modCount++;
    }
}

FD_NS_END