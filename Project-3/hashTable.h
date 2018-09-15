#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#ifndef hashTable_h
#define hashTable_h


template <typename T> // Geneeric type T used by the class
class hashTable {
    
public:
    void makeHashTable(std::vector <T> wordlist); // Creates a hash table out of wordlist
    void addItem(T item); // Adds item to hash table
    void deleteItem(T item); // Deletes item from hash table
    int inList(T item); // Determines if item is in hash table
    int hash(T item); // Hash function
    // friend std::ostream& operator<<(std::ostream& output, const hashTable<T>& h); // Overloaded print operator, unused

    
private:
    std::vector <std::vector <T> > table; // Vector of vectors that makes up hash table
    std::vector <T> listToSort; // Vector of items to be sorted into hash table
    int n; // Number of buckets in the hash table
};

// Reads in a vector of type T and puts it in a hash table, formed using a vector of vectors
template <typename T>
void hashTable<T>::makeHashTable(std::vector <T> wordlist) {
    
    listToSort = wordlist; // Sets the list being put in the hash tale to the input vector
    n = (int) listToSort.size() / 10; // Sets the number of buckets to 1/10th the size of the list to be sorted
    table.resize(n); // Resizes the hash table to have the correct amount of buckets/vector indices
    
    // Loops through the list to be sorted and adds each item to the hash table
    for (int i = 0; i < listToSort.size(); i++)
        addItem(listToSort[i]); // Adds item to list based on hash value
    
    return;
}

// Adds item to the hash table, called by the makeHashTable public function
template <typename T>
void hashTable<T>::addItem(T item) {
    
    // The hash value of the item to be added is calculated by the hash function.
    // That value serves as the row index for its place in the table, and the item
    // is added to the vector that is that row.
    table[hash(item)].push_back(item);
    
    return;
}

// Takes in an item and deletes it from the hash table
template <typename T>
void hashTable<T>::deleteItem(T item) {
    
    int indexTable = hash(item); // Hash value (row index) of the item is found
    int indexMemberToRemove; // Declares the variable to carry the index of the vector inside the right for the item to be removed
    std::vector <T> tempBucket = table[indexTable]; // Vector in the bucket that the item to be removed is located

    int i = 0; // Counter variable for temp vector index
    
    // Loops through the temporary vector while the index is greater than 0
    // and less than the size of the vector
    while (i >= 0 && i < tempBucket.size()) {
        // If the item to be deleted is equal to the value of index i in
        // the temp array, the indexMemberToRemove is set to i and the loop is broken
        if (tempBucket[i] == item) {
            indexMemberToRemove = i;
            break;
        }
        
        i++; // Increments index i
    }
    
    // The table member in the indexMemberToRemove is set to an empty string
    table[indexTable][indexMemberToRemove] = "";
    
    return;
}

// Takes in an item and determines if it exists in the hash table
template <typename T>
int hashTable<T>::inList(T item) {
    
    // Vector in the bucket that the item to be removed is located.
    // The bucket is determined by the hash value of the item
    std::vector <T> tempBucket = table[hash(item)];
    
    // Loops through the temporary vector vector and returns the index inside
    // the vector that the item is located in
    for (int i = 0; i < tempBucket.size(); i++) {
        if (tempBucket[i] == item) {
            return i;
        }
    }
    
    return -1; // -1 is returned if the item is not in the table
}

// Takes in an item (string) and calculates its hash value
template <typename T>
int hashTable<T>::hash(T item) {
    
    long long stringVal = 0; // Initializes value of item to 0
    double exponent; // Declares exponent used in the calculation
    
    // Loops through each character in the string and adds the value of the
    // character to the value of the string
    for (int i = 0; i < item.length(); i++) {
        // Exponent used in hash equation below
        exponent = (double) item.length()-1-i;
        // Equation used to assign value to character. That value is added to the value of the total string
        stringVal +=  (long long)item[i] * (long long)pow(128, (float)exponent);
    }
    
    // The value of the string is moded by the number of buckets in the hash table to
    // get the hash value of the string
    int modResult = (int)(stringVal % n);
    
    // If the mod result is negative, it is converted to a positive value and
    // returned. Otherwise it is just returned.
    if (modResult < 0)
        return modResult + n;
    else
        return modResult;
}

// Overloaded print operator, unused
//template <typename T>
//std::ostream& operator<<(std::ostream& output, const hashTable<T>& h) {
//
//    std::vector<T> temp;
//
//        for (int i = 0; i < h.table.size(); i++) {
//
//            temp = h.table[i];
//
//            for (int j = 0; j < h.table.size(); j++) {
//                output << temp[j] << " ";
//            }
//
//            output << "\n";
//        }
//
//        return output;
//}

#endif /* hashTable_h */
