//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        if (size>=64) {
            cerr << "Heap overflow: cannot push more elements\n";  //Fixed data
            return;
        }
        //new node index at the end of the array
        data[size] = idx;
        //fix
        upheap(size,weightArr);
        size++; //inserted another element
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        //bubble upward while node should be above parent
        while (pos>0) {
            int parent = (pos-1)/2;
            int childIdx = data[pos]; //node index stored at pos
            int parentIdx = data[parent]; // node index stored at parent
            // tie favors smaller index
            bool childIsSmaller =
                (weightArr[childIdx] < weightArr[parentIdx]) ||
                    (weightArr[childIdx] == weightArr[parentIdx] && childIdx < parentIdx);
            if (!childIsSmaller) {
                 break;
            }


            //swap chiild with parent, continue from parent posiition
            std::swap(data[pos], data[parent]);
            pos = parent;

        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif