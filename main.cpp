//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {

     MinHeap heap;
        
        //push all, we start with our minheap before doing huffman

        for (int i = 0; i < nextFree; ++i) {
            heap.push(i,weightArr);
        }

        //if too small return the root
        if (heap.size == 0){
            return -1;
        }
        if (heap.size == 1) {
            return heap.pop(weightArr);
        }

        // keep combining two smallest nodes until only one root remains
        while(heap.size > 1 ){
            
            int a = heap.pop(weightArr);
            int b = heap.pop(weightArr);

            charArr[nextFree] = '\0';
            leftArr[nextFree] = a;
            rightArr[nextFree]  = b;
            weightArr[nextFree] = weightArr [a] + weightArr[b];

            //push parent back into heap

            heap.push(nextFree, weightArr);
            ++nextFree;

        }
        // final remaining is root of encoding tree
        return heap.pop(weightArr); 

}
// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    //clear previous codes
    for (int i = 0; i<26; ++i){
        codes [i].clear();
    }

    
    // if no tree, nothing
    if (root <0){
        return;
    }
    //DFS stack 
    stack<int> nodes; // which node to visit next
    stack<string> paths; //store bitstring

    //start at root with empty path
    nodes.push(root);   
    paths.push(""); 

    //DFS loop
    while (!nodes.empty()) {
        int u = nodes.top();
        nodes.pop();
        string path = paths.top(); paths.pop();
        
        //get left and right indices of this node
        int L = leftArr[u];
        int R = rightArr[u]; 
        
        bool isLeaf = (L == -1 && R == -1);
        if (isLeaf) {
            char c = charArr[u]; 
            if (c>= 'a' && c <='z') {  // only assign code for letters
                // in case our file is only one letter we create this edge case
                codes [ c-'a'] = path.empty() ? "0": path;
            }
        }else {
            //push right first then left, so left gets proccess first, LIFO
            if (R != -1) { nodes.push(R); paths.push(path + "1");}
            if (L != -1) {nodes.push(L); paths.push(path + "0");}
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}