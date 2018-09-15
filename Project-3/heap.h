#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#ifndef heap_h
#define heap_h

template <class T>
class heap {
    
public:
    int parent(int n); // Create parent node
    int left(int n);   // Create left child node
    int right(int n);  // Create right child node
    T getItem(int n);  //Return vector elements
    void initializeMaxHeap(std::vector<T> values); //Make copy of MaxHeap
    void maxHeapify(int i); // Heapsort algorithm to bring smallest value to bottom leaf
    void buildMaxHeap();    // Uses maxHeapify to create binary tree with root as max value
    void heapsort();        // Uses buildMaxHeap and maxHeapify to sort incrementing
    void minHeapify(int i); // Heapsort algorithm to bring biggest value to bottom leaf
    void buildMinHeap();    // Uses minHeapify to create binary tree with root as min value
    void minHeapsort();     // Uses buildMinHeap and minHeapify to sort decrementing
    std::vector<T> getVec();

private:
    std::vector<T> vec;    //Vector of items to be sorted 
    int heapsize;          //Private member for heap vector size
    int largest;           //Private member to store largest node
    int smallest;          //Private member to store smallest node
    
};

//Returns index of parent node in linear vector
template<class T>
int heap<T>::parent(int n) {
    
    return (n - 1) / 2; //Parent of node/index is at this index
}

//Returns left index child of the node in linear vector
template<class T>
int heap<T>::left(int n) {
    
    return (n * 2) + 1; //Left is children of the node/index at this index
}

//Returns right index child of the node in linear vector
template<class T>
int heap<T>::right(int n) {
    
    return (n * 2) + 2; //Right is children of the node/index at this index
}

//Get accessor for specific vector element
template <class T>
T heap<T>::getItem(int n) {
    
    return vec[n]; //Returns nth indexed item from heap
}

// Initiliazes copy vector vec
template<class T>
void heap<T>::initializeMaxHeap(std::vector<T> values)
{
    vec = std::vector<T>(values);
    return;
}

// Generic swap function to swap vector values
template <typename t>
void swap(t& x, t& y)
{
    t temp = x;
    x = y;
    y = temp;
    
    return;
}

//Bring smallest values to leaves of binary tree
template<class T>
void heap<T>::maxHeapify(int i) {
    
    //L and r index of children NOT values
    int l = left(i);
    int r = right(i);
    
    if (l <= heapsize-1 && vec[l] > vec[i]) {
        largest = l; //Largest keeps track of largest value
    }
    else {
        largest = i;
    }
    
    if (r <= heapsize-1 && vec[r] > vec[largest]) {
        largest = r; //Find index of largest value
    }
    
    //If found larger child node, switch with parent, only values are switched
    if (largest != i) {
        swap(vec[i], vec[largest]);
        maxHeapify(largest);  //Now calls maxheapify ercursively for new value of child node --> keeps going until at leaf and no nodes smaller
    }
    return;
}

//Creates max binary tree with root as largest value
template<class T>
void heap<T>::buildMaxHeap() {
    heapsize = vec.size(); //Iterates through all nodes
    for (int i = (vec.size() / 2) - 1; i >= 0; i--) { //Using binary tree index properties, iterate thorugh half of the tree ensures all branches are heapified
        maxHeapify(i);     //Recursively bring smallest values to leaves
    }
    return;
}

//Sorts maxHeap binary tree into linear vector
template<class T>
void heap<T>::heapsort() {
    
    buildMaxHeap(); // buildmaxheap builds ordered max tree
    
     // For loop swaps the max value at the root node with the last value and then deletes that new last value a.k.a the root value
    for (int i = vec.size() - 1; i >= 1; i--) {
        swap(vec[0], vec[i]);
        //Then runs max heapify at the root to make sure max value is at the root/top
        heapsize--;
        //Highest values are at the end of vector and the root v[0] = smallest value and done sorting
        maxHeapify(0);
    }
    return;
}

//Bring largest values to leaves of binary tree
template<class T>
void heap<T>::minHeapify(int i) {
    
    int l = left(i); // L and r index of children NOT value
    int r = right(i);
    if (l <= heapsize-1 && vec[l] < vec[i]) {
        smallest = l;
    }
    else {
        smallest = i;
    }
    if (r <= heapsize-1 && vec[r] < vec[smallest]) {
        smallest = r;
    }
    
    // If found smaller child node, switch with parent, only values are switched
    if (smallest != i) {
        swap(vec[i], vec[smallest]);
        
        //Now do minheapify again for new value of child node --> keeps going until at leaf and no nodes smaller
        minHeapify(smallest);
    }
    
    return;
}

// Recursively uses minHeapify to build binay tree with root as smallest value
template<class T>
void heap<T>::buildMinHeap() {
    
    heapsize = vec.size();
    
    // Iterates through all nodes
    for (int i = (vec.size()/2) - 1; i >= 0; i--){
        minHeapify(i);
    }
    
    return;
}

//Sorts decrementing in value
template<class T>
void heap<T>::minHeapsort() {
    
    buildMinHeap(); //buildmaxheap builds ordered max tree
    
    //for loop swaps the max value at the root node with the last value and then deletes that new last value a.k.a the root value
    for (int i = vec.size() -1; i >= 1; i--) {
        swap(vec[0], vec[i]);
        heapsize--;
        
        //highest values are at the end of vector and the root v[0] = smallest value and done sortin
        minHeapify(0);
    }
    
    return;
}

//Get accessor to obtain vector
template<class T>
std::vector<T> heap<T>::getVec() {
 
    return vec;
}

#endif /* heap_h */
