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
        // check if empty
        if (size == 0) {
        cerr << "Heap underflow: cannot pop from empty heap\n";
        return -1; // nothing to remove
    }
        // save the root
        int minIdx = data[0];

        // Move last element to roots position
        size--;
        data[0] = data[size];

        //fix order, compare it with children below . 
        if (size> 0){
            downheap(0,weightArr);
        }

        return minIdx; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        //bubble upward while node should be above parent
        while (pos>0) {
            int parent = (pos-1)/2;
            int childIdx = data[pos]; //node index stored at pos
            int parentIdx = data[parent]; // node index stored at parent
            // tie favors smaller index
            bool childIsSmaller =
                (weightArr[childIdx] < weightArr[parentIdx]);
            if (!childIsSmaller) {
                 break;
            }


            //swap chiild with parent, continue from parent posiition
            std::swap(data[pos], data[parent]);
            pos = parent;

        }
    }

    void downheap(int pos, int weightArr[]) {
        while(true){
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;
        
        //check if left exists then sees if it's smaller
            if (left<size){
                int li = data[left], si = data[smallest];
            if (weightArr[li]<weightArr[si]){
                smallest = left;
            }
        }
        //check if right exists then sees if it's smaller
            if (right < size){
                int ri = data[right], si = data[smallest];
            if (weightArr[ri] < weightArr[si]){
                smallest = right;
            }
        }
        //if we already have smallest we donzo
            if (smallest == pos) break;

        // if not we swap and the code keeps looping till we have smallest = pos
            std::swap(data[pos], data[smallest]);
        
            pos = smallest; // moves position down so it can compare it with the next two children
    }
}
        
        
};

#endif