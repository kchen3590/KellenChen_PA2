//
// Created by Manju Muralidharan on 10/19/25.

//implement simple minheap for frequency encoding, the smaller weight frequencies are pushed to the top.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];           //stores indices of nodes
    int size;                   // this is the number of items currently in the heap

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;               //puts new item at the end
        upheap(size, weightArr);        //restores the order
        size++;                         //increase heap size
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0)                 //edge case
            return -1;

        int top = data[0];
        size--;

        if (size >0) {
            data[0] = data[size];
            downheap(0, weightArr);      //this fixes heap order
        }
        return top;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos >0) {
            int parent = (pos - 1) / 2;                                 //this is to find parent index
            if (weightArr[data[pos]] < weightArr[data[parent]]) {       //if parent is bigger than child,  swap
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = temp;
                pos = parent;
            } else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left = 2*pos+1;
            int right = 2*pos+2;
            int smallest = pos;

            //to find which is smallest, the parent, left, or right
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) {
                smallest = left;
            }
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
                smallest = right;
            }
            if (smallest == pos) {      //if the parent is already the smallest=break
                break;
            }

            int temp =data[pos];            //this swaps parent w/ the smallest child
            data[pos] = data[smallest];
            data[smallest] = temp;

            pos = smallest;                 //moves downward and repeats
        }
    }
};

#endif