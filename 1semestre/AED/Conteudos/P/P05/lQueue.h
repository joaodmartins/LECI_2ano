//
// Tomás Oliveira e Silva, AED, October 2014, September 2015
//
// Generic queue (First In First Out) implementation based on an linked list
//

#ifndef _AED_lQueue_
#define _AED_lQueue_

#include <cassert>
#include "sList.h"

template <typename T>
class lQueue {

private:
    sList <T> list;
    int maxSize, curSize;

public:
    //lQueue constructor
    lQueue(int n = 100) {

        assert(n >= 10 && n <= 1000000);
        maxSize = n;
        curSize = 0;
    }

    //lQueue destructor(list.size() == 0) ? 1 : 0
    ~lQueue(void) {
        list.~sList();
    }

    //clear queue
    void clear(void) {
        list.size = 0;
    }

    //Queue size
    int size(void) const {
        return list.size();
    }

    int is_full(void) const {
        return (list.size() == maxSize) ? 1 : 0 ;
    }

    int is_empty(void) const {
        return (list.size() == 0) ? 1 : 0;
    }

    //Add element
    void enqueue(T &v) {
        list.insert_after_tail(v);
    }

    //Remove
    T dequeue(void) {

        assert(is_empty()!=1);
        list.move_to_head();
        T v = list.value();
        list.remove();
        return v;
    }

    T peek(void) {
        assert(is_empty()!=1);
        list.move_to_head();
        return list.value();

    }
};

#endif
