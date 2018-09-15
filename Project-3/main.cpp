#include <iostream>
#include <cmath>
#include "wordList.h"
#include "grid.h"
#include "heap.h"
#include "hashTable.h"
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

void findMatches(std::ifstream& wordListFile, std::ifstream& gridFile, int whichSort); // Finds and prints words found in grid
void search(int whichSort); // Reads the name of the grid file and wordlist and prints all the words that can be found

int main() {
    
    search(4);
    
    return 0;
}

// Reads in the name of the grid file from the keyboard and prints out the words
// fromt he wordlist that can be found in the grid and the times it takes to sort
// the word list, search for the words, and total time.
void search(int whichSort) {
    
    int gridChoice; // Holds grid that is chosen
    std::ifstream gridFile; // Holds grid file
    std::ifstream gridFile2; // Holds grid file
    std::ifstream wordListFile; // Holds wordlist file
    std::ifstream wordListFile2; // Holds wordlist2 file
    
    // Asks user to choose grid
    std::cout << "Please choose one of the following grid files by pressing the corresponding key:\n"
    "1 - puzzle10.txt\n"
    "2 - input15.txt\n"
    "3 - input30.txt\n"
    "4 - input50.txt\n"
    "5 - input250.txt\n" << std::endl;
    
    std::cin >> gridChoice; // User input for grid choice
    
    // Throws error for input outside range and ends program
    try{
        if (gridChoice != 1 && gridChoice != 2 && gridChoice != 3 && gridChoice != 4 && gridChoice != 5)
            throw(gridChoice);
        else if
            (std::cin.fail())
            throw(gridChoice);
    }
    catch(int e) {
        std::cout<<"Error: Please enter either 1, 2, 3, 4, or 5.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail(),'\n');
        exit(1);
    }
    
    if (gridChoice == 1) {
        gridFile.open("/Users/nguye/Desktop/SearchWords2/puzzle10.txt");
    }
    else if (gridChoice == 2) {
        gridFile.open("/Users/nguye/Desktop/SearchFINAL/input15.txt");
    }
    else if (gridChoice == 3) {
        gridFile.open("/Users/nguye/Desktop/SearchFINAL/input30.txt");
    }
    else if (gridChoice == 4) {
        gridFile.open("/Users/nguye/Desktop/SearchFINAL/input50.txt");
    }
    else if (gridChoice == 5) {
        gridFile.open("/Users/nguye/Desktop/SearchFINAL/input250.txt");
    }
    
    // Runs algorithm for wordlist 1
    wordListFile.open("/Users/nguye/Desktop/SearchFINAL/wordlist.txt");
    findMatches(wordListFile, gridFile, whichSort); // Finds words in grid
    
    if (gridChoice == 1)
        gridFile2.open("/Users/nguye/Desktop/SearchFINAL/puzzle10.txt");
    else if (gridChoice == 2)
        gridFile2.open("/Users/nguye/Desktop/SearchFINAL/input15.txt");
    else if (gridChoice == 3)
        gridFile2.open("/Users/nguye/Desktop/SearchFINAL/input30.txt");
    else if (gridChoice == 4)
        gridFile2.open("/Users/nguye/Desktop/SearchFINAL/input50.txt");
    else if (gridChoice == 5)
        gridFile2.open("/Users/nguye/Desktop/SearchFINAL/input250.txt");
    
    // Runs algorithm for wordlist 2
    wordListFile2.open("/Users/nguye/Desktop/SearchFINAL/wordlist2.txt");
    findMatches(wordListFile2, gridFile2, whichSort); // Finds words in grid
    
    return;
}

// Takes in a wordlist file and grid file and and prints out all the words in the wordlist that
// can be found in the grid. The method of sort is determined by the whichSort parameter.
void findMatches(std::ifstream& wordListFile, std::ifstream& gridFile, int whichSort) {
    
    wordList newWordList; // Declares new wordList type
    newWordList.readWordList(wordListFile); // Reads in the wordlist that was chosen
    
    grid newGrid; // Declares new grid type
    newGrid.readInGrid(gridFile); // Reads in grid that was chosen
    newGrid.createGridCombos(newWordList); // Creates all the possible combos of words in the grid
    
    // Insertion Sort Method
    if (whichSort == 1) {
        
        std::clock_t startSort = std::clock(); // Starts timer for sort
        newWordList.insertionSort(); // Sorts word list using insertion sort
        double durationSort = (std::clock() - startSort) / (double)CLOCKS_PER_SEC; // Ends timer for sort
        
        std::vector<std::string> gridCombos = newGrid.getGridCombos(); // Gets string vector of all the possible combos of words in the grid
        std::vector<std::string> foundWords; // Make empty vector to hold words that were found
        
        int searchResult; // Result of binary search for each iteration
        
        std::clock_t startSearch = std::clock(); // Starts timer for search
        // Loops through each string in grid combos and seaches for it in the word list
        for (int i = 0; i < gridCombos.size(); i++) {
            // Binary search is called to search for word. Returns index if it exists, and -1 if it does not
            searchResult = newWordList.binarySearch(gridCombos[i]);
            
            // If word was found, it is added to vector of found words and deleted from the list
            if (searchResult >= 0) {
                foundWords.push_back(gridCombos[i]);
                newWordList.deleteWord(searchResult);
            }
        }
        double durationSearch = (std::clock() - startSearch) / (double)CLOCKS_PER_SEC; // Ends timer for search
        
        std::cout << "The words (with length of at least five characters) found for this word list and grid are:\n" << std::endl;
        for (int k = 0; k < foundWords.size(); k++) {
            std::cout << foundWords[k] << std::endl;
        }
        
        std::cout << "\nTime for Insertion Sort: " << durationSort << std::endl;
        std::cout << "Time for Binary Search: " << durationSearch << std::endl;
        std::cout << "Total Time: " << durationSort+durationSearch << std::endl;
    }
    
    // Quicksort method
    if (whichSort == 2) {
        
        std::clock_t startSort = std::clock(); // Starts timer for sort
        newWordList.quickSort(); // Sorts word list using quicksort
        double durationSort = (std::clock() - startSort) / (double)CLOCKS_PER_SEC; // Ends timer for sort
        
        std::vector<std::string> gridCombos = newGrid.getGridCombos(); // Gets string vector of all the possible combos of words in the grid
        std::vector<std::string> foundWords; // Make empty vector to hold words that were found
        
        int searchResult; // Result of binary search for each iteration
        
        std::clock_t startSearch = std::clock(); // Starts timer for search
        // Loops through each string in grid combos and seaches for it in the word list
        for (int i = 0; i < gridCombos.size(); i++) {
            // Binary search is called to search for word. Returns index if it exists, and -1 if it does not
            searchResult = newWordList.binarySearch(gridCombos[i]);
            
            // If word was found, it is added to vector of found words and deleted from the list
            if (searchResult >= 0) {
                foundWords.push_back(gridCombos[i]);
                newWordList.deleteWord(searchResult);
            }
        }
        double durationSearch = (std::clock() - startSearch) / (double)CLOCKS_PER_SEC; // Ends timer for search
        
        std::cout << "The words (with length of at least five characters) found for this word list and grid are:\n" << std::endl;
        for (int k = 0; k < foundWords.size(); k++) {
            std::cout << foundWords[k] << std::endl;
        }
        
        std::cout << "\nTime for Quick Sort: " << durationSort << std::endl;
        std::cout << "Time for Binary Search: " << durationSearch << std::endl;
        std::cout << "Total Time: " << durationSort+durationSearch << std::endl;
    }
    
    // Merge sort method
    if (whichSort == 3) {
        
        std::clock_t startSort = std::clock(); // Starts timer for sort
        newWordList.mergeSort(); // Sorts word list using merge sort
        double durationSort = (std::clock() - startSort) / (double)CLOCKS_PER_SEC; // Ends timer for sort
        
        std::vector<std::string> gridCombos = newGrid.getGridCombos(); // Gets string vector of all the possible combos of words in the grid
        std::vector<std::string> foundWords; // Make empty vector to hold words that were found
        
        int searchResult; // Result of binary search for each iteration
                
        std::clock_t startSearch = std::clock(); // Starts timer for search
        // Loops through each string in grid combos and seaches for it in the word list
        for (int i = 0; i < gridCombos.size(); i++) {
            // Binary search is called to search for word. Returns index if it exists, and -1 if it does not
            searchResult = newWordList.binarySearch(gridCombos[i]);
            
            // If word was found, it is added to vector of found words and deleted from the list
            if (searchResult >= 0) {
                foundWords.push_back(gridCombos[i]);
                newWordList.deleteWord(searchResult);
            }
        }
        double durationSearch = (std::clock() - startSearch) / (double)CLOCKS_PER_SEC; // Ends timer for search
        
        std::cout << "The words (with length of at least five characters) found for this word list and grid are:\n" << std::endl;
        for (int k = 0; k < foundWords.size(); k++) {
            std::cout << foundWords[k] << std::endl;
        }
        
        std::cout << "\nTime for Merge Sort: " << durationSort << std::endl;
        std::cout << "Time for Binary Search: " << durationSearch << std::endl;
        std::cout << "Total Time: " << durationSort+durationSearch << std::endl;
    }
    
    // Heap sort method
    if (whichSort == 4) {
        
        std::clock_t startSort = std::clock(); // Starts timer for sort
        newWordList.heapSortList(); // Sorts wordlist using heap sort
        double durationSort = (std::clock() - startSort) / (double)CLOCKS_PER_SEC; // Ends timer for sort
        
        std::vector<std::string> gridCombos = newGrid.getGridCombos(); // Gets string vector of all the possible combos of words in the grid
        std::vector<std::string> foundWords; // Makes empty vector to hold words that were found
        
        int searchResult; // Result of binary search for each iteration
        
        std::clock_t startSearch = std::clock(); // Starts timer for search
        // Loops through each string in grid combos and seaches for it in the word list
        for (int i = 0; i < gridCombos.size(); i++) {
            // Binary search is called to search for word. Returns index if it exists, and -1 if it does not
            searchResult = newWordList.binarySearch(gridCombos[i]);
            
            // If word was found, it is added to vector of found words and deleted from the list
            if (searchResult >= 0) {
                foundWords.push_back(gridCombos[i]);
                newWordList.deleteWord(searchResult);
            }
        }
        double durationSearch = (std::clock() - startSearch) / (double)CLOCKS_PER_SEC; // Ends timer for search
        
        std::cout << "The words (with length of at least five characters) found for this word list and grid are:\n" << std::endl;
        for (int k = 0; k < foundWords.size(); k++) {
            std::cout << foundWords[k] << std::endl;
        }
        
        std::cout << "\nTime for Heap Sort: " << durationSort << std::endl;
        std::cout << "Time for Binary Search: " << durationSearch << std::endl;
        std::cout << "Total Time: " << durationSort+durationSearch << std::endl;
    }
    
    // Hash table method
    if (whichSort == 5) {
        
        hashTable<std::string> hashMethod;
        
        std::clock_t startSort = std::clock(); // Starts timer for sort
        hashMethod.makeHashTable(newWordList.getWordList());
        double durationSort = (std::clock() - startSort) / (double)CLOCKS_PER_SEC; // Ends timer for sort
        
        std::vector<std::string> gridCombos = newGrid.getGridCombos(); // Gets string vector of all the possible combos of words in the grid
        std::vector<std::string> foundWords; // Make empty vector to hold words that were found
        
        int hashResult; // Declares variable for result of searching for item in hash table
        
        std::clock_t startSearch = std::clock(); // Starts timer for search
        // Loops through each string in grid combos and seaches for it in the word list
        for (int i = 0; i < gridCombos.size(); i++) {
            // Checks to see if the current string from grid combos is located in the list.
            // Returns index if it is, and returns -1 if it is not
            hashResult = hashMethod.inList(gridCombos[i]);
            
            // If the string is in the has table and word list, it is added to thevector fo found words and
            // the item is deleted from the table
            if (hashResult >= 0) {
                foundWords.push_back(gridCombos[i]);
                hashMethod.deleteItem(gridCombos[i]);
            }
        }
        double durationSearch = (std::clock() - startSearch) / (double)CLOCKS_PER_SEC; // Ends timer for search
        
        std::cout << "The words (with length of at least five characters) found for this word list and grid are:\n" << std::endl;
        for (int k = 0; k < foundWords.size(); k++) {
            std::cout << foundWords[k] << std::endl;
        }
        
        std::cout << "\nTime for Hash Sort: " << durationSort << std::endl;
        std::cout << "Time for Search: " << durationSearch << std::endl;
        std::cout << "Total Time: " << durationSort+durationSearch << std::endl;
    }
    
    return;
}



