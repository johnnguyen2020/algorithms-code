#ifndef wordList_h
#define wordList_h
#include "heap.h"
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

class wordList {
    
public:
    void readWordList(std::ifstream &inFile); // Reads file of a list of words and puts them into a vector
    std::vector <std::string> getWordList(); // Returns the vecotr of a list of words
    void deleteWord(int index); // Deletes a word in the given index from the word list
    friend std::ostream& operator<<(std::ostream& output, const wordList& w); // Overloaded print operator to print out vector of strings
    void insertionSort(); // Sorts an array using insertion sort method
    void quickSort(); // Sorts an array using quick sort method (for first iteration on private data member)
    void quickSort(std::vector <std::string> &tempVec, int start, int end); // Sorts an array using quick sort method (overloaded for subsequent iterations)
    int partition(std::vector <std::string> &tempVec, int start, int end); // Used by quicksort to partition array
    void mergeSort(); // Sorts an array using merge sort method (first iteration for private data member)
    void mergeSort(int start, int end); // Sorts an array using insertion sort method (overloaded for subsequent iterations
    void merge(int start, int mid, int end); // Used by merge sort to merge multiple arrays into 1
    void heapSortList(); // Sorts an array using heap sort method
    int binarySearch(std::string word); // Seaches an array using binary search method (first iteration for private data member)
    int binarySearch(int low, int high, std::string word); // Searches an array using binary search method (overloaded for subsequent iterations)
    
private:
    std::vector <std::string> list; // Vector data member that holds list of strings
    heap <std::string> h; // heap data member used in heap sort function
};

// Takes in text file and puts contents in string vector
void wordList::readWordList(std::ifstream &inFile) {
    
    // If the file is not found, error is thrown
    if (!inFile) {
        std::cerr << "Unable to open file.";
        exit(1);   // call system to stop
    }
    
    std::string line; // Current line being read in file
    
    // Loops through every line in the file
    while(std::getline(inFile, line)) {
        // If the first letter of a word is uppercase, it is made lower case
        if (isupper(line[0]))
            line = tolower(line[0]);
        list.push_back(line); // Word in line is added to private vector of strings
    }

    return;
}

// Returns the vecotr of a list of words
std::vector <std::string> wordList::getWordList() {
    
    return list; // Returns vector of strings
}

// Deletes a word in the given index from the word list
void wordList::deleteWord(int index) {
    // To keep words sorted, the word being removed is moved to the front
    // of the array and replaced with an empty string.
    
    // Loops through each element before the one being removed and moves
    // them forward in the list one spot
    for (int i = index-1; i >= 0; i--) {
        list[i+1] = list[i];
    }
    
    list[index] = ""; // Replaces element to be removed with an empty string
    
    return;
}

// Overloaded print operator to print vector of strings
std::ostream& operator<<(std::ostream& output, const wordList& w) {
    
    for (int i = 0; i < w.list.size(); i++) {
        output << w.list[i] << "\n";
    }
    
    return output;
}

// Sorts vector using insertion sort
void wordList::insertionSort() {
    
    std::string key; // Key is initialized
    int i; // Counter for
    
    // Loops through the entire vector of strings
    for (int j = 1; j < list.size(); j++) {
        key = list[j]; // Key starts at second element and increments by 1 until the end
        i = j-1; // i is index before the key
        
        // Loops while i has not reached beginning of vector and values before the key are greater then the key
        while (i >= 0 && (list[i] > key)) {
            list[i+1] = list[i]; // Value in i index moves up one
            i = i-1;
        }
        
        list[i+1] = key; // Key is assigned to index where all elements before it are smaller
    }
    
    return;
}

// Sorts vector using quick sort (for first iteration on private data member)
void wordList::quickSort() {
    
    int start = 0; // First index in vector
    int end = (int) list.size()-1; // Last index in vector
    
    // Runs if start index is less than end index
    if (start < end) {
        int partitionIndex = partition(list, start, end); // partition is run and index for new partition is returneds
        quickSort(list, start, partitionIndex-1); // Quicksort called for left side
        quickSort(list, partitionIndex+1, end); // Quicksort called for right side
    }
    
    return;
}

// Sorts an array using quick sort method (overloaded for subsequent iterations)
void wordList::quickSort(std::vector <std::string> &tempVec, int start, int end) {
    
    // Runs if start index is less than end index
    if (start < end) {
        int partitionIndex = partition(tempVec, start, end); // partition is run and index for new partition is returneds
        quickSort(tempVec, start, partitionIndex-1); // Quicksort called for left side
        quickSort(tempVec, partitionIndex+1, end); // Quicksort called for right side
    }
    
    return;
}

// Sorts vector using insertion sort (overloaded)
int wordList::partition(std::vector <std::string> &tempVec, int start, int end) {
    
    std::string pivot = tempVec[end]; // Pivot is set to the last element of the input vector
    int partitionIndex = start; // partitionIndex is initialized as the input start
    
    // Loops through the vector from the partitionIndex to the passed in end minus 1
    for (int i = partitionIndex; i < end; i++) {
        // Runs if the current element in the passed in vector is less than or equal to the pivot.
        // The current element and the partitionIndex element are swapped
        if (tempVec[i] <= pivot) {
            std::string tempI = tempVec[i]; // Element in index i stored temporarily
            tempVec[i] = tempVec[partitionIndex]; // index i in the vector set to the partitinIndex element
            tempVec[partitionIndex] = tempI; // Element in index i placed in partitionIndex of vector
            partitionIndex++; // partitionIndex incremented
        }
    }
    
    // Element in partitionIndex and last element are swapped
    std::string tempPartition = tempVec[partitionIndex]; // Element in index partitionIndex stored temporarily
    tempVec[partitionIndex] = tempVec[end]; // Last vector element placed in partitionIndex of vector
    tempVec[end] = tempPartition; // // Element in index partitionIndex placed at end of vector
    
    return partitionIndex;
}

// Sorts an array using merge sort method (first iteration for private data member)
void wordList::mergeSort() {
    
    // Meregesort run on the private list data member. Lowest index is 0, and
    // highest index is the size of the list minus 1.
    mergeSort(0, (int) list.size()-1);
    
    return;
}

// Sorts an array using insertion sort method (overloaded for subsequent iterations
void wordList::mergeSort(int start, int end) {

    if (start < end) {
        int mid = (start+end)/2; // Middle index of the merge list is found
        mergeSort(start, mid); // Mergesort run on lower half
        mergeSort(mid+1, end); // Meregsort run on upper half
        merge(start, mid, end); // Both halfs are then merged
    }
    
    return;
}

// Used by merge sort to merge multiple arrays into 1
void wordList::merge(int start, int mid, int end) {
    
    int n1 = mid-start+1; // Length of left array set
    int n2 = end-mid; // Length of right array set
    std::string left[n1]; // Left array initialized
    std::string right[n2]; // Right array initialized
    
    int i, j, k; // Counters for going through the arrays. i counts left array elements, j counts right array elements, k counts merged array elements
    std::string temp[end-start+1]; // temporary array holding merged values
    
    // Left array filled with original array from indexes start to mid, and right array filled with original array from indexes mid+1 to end
    for (int i = 0; i < n1; i++)
        left[i] = list[i+start];
    for (int j = 0; j < n2; j++)
        right[j] = list[j+mid+1];
    
    i = start; // i set to first member of left array
    j = mid+1; // j set to first member of right array
    k = 0;
    
    // Loop runs while both left and right arrays have not been fully gone through
    while (i <= mid && j <= end) {
        // If the current element in left array is less than curent in right array
        if (list[i] < list[j]) {
            temp[k] = list[i]; // Left array current is put in merged array
            i++; // i incremented
            k++; // k incremented
        }
        // If the current element in right array is less than or equal to current in left array
        else {
            temp[k] = list[j]; // Right array current is put in merged array
            j++; // j incremented
            k++; // k incremented
        }
    }
    
    // If right array was gone through first, remaining elements in left array added to merged array
    while (i <= mid) {
        temp[k] = list[i]; // Left array current is put in merged array
        i++; // i incremented
        k++; // k incremented
    }
    
    // If left array was gone through first, remaining elements in right array added to merged array
    while (j <= end) {
        temp[k] = list[j]; // Right array current is put in merged array
        j++; // j incremented
        k++; // k incremented
    }
    
    // Temp array elements in the given indexes added to the original array, which is the private member list
    for (i = start; i <= end; i++) {
        list[i] = temp[i-start];
    }
}

// Sorts an array using heap sort method (using its own class)
void wordList::heapSortList() {
    
    h.initializeMaxHeap(list); // Heap is initialized
    h.heapsort(); // Heap is sorted
 
    std::vector <std::string> listCopy = h.getVec(); // Gets sorted vector of strings
    
    // list data member is replaced its sorted version
    for (int i = 0; i < list.size(); i++)
        list[i] = listCopy[i];
    
    return;
}

// Seaches an array using binary search method (first iteration for private data member)
int wordList::binarySearch(std::string word) {
    
    int low = 0; // Lowest index is intitially 0
    int high = list.size()-1; // Highest inde is initially the size of the private list minus 1
    
    return binarySearch(low, high, word); // Binary search is run
    
    return -1;
}

// Searches an array using binary search method (overloaded for subsequent iterations)
int wordList::binarySearch(int low, int high, std::string word) {
    
    // Runs as long as the lowest index is lower than the highest index
    if (low <= high) {
        int mid = low+(high-low)/2; // Middle index in the search list is determined
        
        // If the middle element is the word, that index is returned
        if (list[mid] == word)
            return mid;
        
        // If the middle element is greater than the word, binary search is run on the lower half
        if (list[mid] > word)
            return binarySearch(low, mid-1, word);
        
        // Else if the middle element is less than the word, binary search is run on the upper half
        else
            return binarySearch(mid+1, high, word);
    }

    return -1;
}

#endif /* wordList_h */
