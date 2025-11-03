//
// Created by Manju Muralidharan on 10/19/25.
//
//The program reads and encodes text from input.txt through frequency based
//encoding. In other words, the more frequent the character, the shorter the binary code.
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
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap heap;

    // 2. Push all leaf node indices into the heap.
    for (int i=0; i<nextFree; i++) {
        heap.push(i, weightArr);
    }

    // 3. While the heap size is greater than 1:
    if (heap.size == 0) return -1;          //edge case
    //    - Pop two smallest nodes

    while (heap.size > 1) {
        int a = heap.pop(weightArr);
        int b = heap.pop(weightArr);

        //    - Create a new parent node with combined weight & Set left/right pointers
        int parent = nextFree++;
        leftArr[parent] = a;
        rightArr[parent] = b;
        weightArr[parent] = weightArr[a] + weightArr[b];

        //    - Push new parent index back into the heap
        heap.push(parent, weightArr);
    }
    // 4. Return the index of the last remaining node (root)

    return heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    if (root == -1) return;                                      //edge case

    if (leftArr[root] == -1 && rightArr[root] == -1) {          //for cases where only one unique character like aaaa
        codes[charArr[root] - 'a'] = "0";
        return;
    }

    stack<pair<int, string>> st;                     //use a stack for traversal
    st.push({root, ""});

    while (!st.empty()) {
        auto current = st.top();
        st.pop();

        int node = current.first;
        string path = current.second;

        int left = leftArr[node];
        int right = rightArr[node];


        if (left == -1 && right == -1) {                //if leaf node: assign its code. push right then left so left is processed first.
            char ch = charArr[node];
            codes[ch - 'a'] = path;
        }
        else {
            if (right !=-1)
                st.push({right, path + "1"});
            if (left !=-1)
                st.push({left, path + "0"});
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