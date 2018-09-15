#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#ifndef grid_h
#define grid_h
#include "wordList.h"


class grid {
    
public:
    void readInGrid(std::ifstream &inFile); // Reads in text file and puts contents into a grid
    std::vector<std::string> getGridCombos(); // Returns list of possible combinations of letters in grid
    void createGridCombos(wordList refList); // Creates vector of possible combinations of words in grid, takes in reference wordlist to limit letter combos to a maximum and minimum
    void wordsN(int row, int col, int minLength, int maxLength); // Finds letter combos in north direction
    void wordsNE(int row, int col, int minLength, int maxLength); // Finds letter combos in northeast direction
    void wordsE(int row, int col, int minLength, int maxLength); // Finds letter combos in east direction
    void wordsSE(int row, int col, int minLength, int maxLength); // Finds letter combos in southeast direction
    void wordsS(int row, int col, int minLength, int maxLength); // Finds letter combos in south direction
    void wordsSW(int row, int col, int minLength, int maxLength); // Finds letter combos in southwest direction
    void wordsW(int row, int col, int minLength, int maxLength); // Finds letter combos in west direction
    void wordsNW(int row, int col, int minLength, int maxLength); // Finds letter combos in northwest direction
    //friend std::ostream& operator<<(std::ostream& output, const grid& g); // Overloaded print operator, unused

private:
    std::vector <std::vector <char> > puzzle; // Vector of vector of characters that holds the grid
    std::vector <std::string> gridCombos; // Vector of strings that holds combos of possible words
    
};

// Reads in text file and puts contents into a grid
void grid::readInGrid(std::ifstream &inFile) {
    
    // If input file is not found, a error is thrown
    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    
    int rows, cols; // Declaring the number of rows and columns in the table
    inFile >> rows; // Reads in rows from txt file
    inFile >> cols; // Reads in columns from txt file
               
    char newChar; // Declares the variable to hold each new character
    int i = 0, j = 0; // Initializes column and row counters
    std::vector <char> currentRow(cols); // Character vector to hold the current row, with initialized length being the number of columns
    puzzle.resize(rows); // Resizes the grid based on number of rows
    
    // Loops through the input text file while there are still characters
    while (inFile >> newChar) {
        // Sets the character of current index in the current row
        // to the character that was just read in
        currentRow[i] = newChar;
        
        // If the column counter reaches the last column, and if the row counter
        // has yet to reach the last row, the current row increments by 1
        if (i == cols-1) {
            if (j < rows) {
                puzzle[j] = currentRow; // Current row set to next row in puzzle
                j++; // Row counter is incremented
                i = -1; // i re-set to negative 1 (will be incremented immediately to 0
            }
        }
        
        i++; // Column counter incremented by 1
    }
    
    return;
}

// Returns the vector of strings of all the combos of grid words
std::vector<std::string> grid::getGridCombos() {
    
    return gridCombos;
}

// Creates the vector of every appropriate-length character combo in the grid.
// A wordlist is taken in to limit the combos length by finding the longest length word in the wordlist.
void grid::createGridCombos(wordList refList) {

    std::vector<std::string> refListVec = refList.getWordList(); // String vector of the wordlist in the passed in wordlist
    std::string refString = refListVec[0]; // refString initialized to the first string of the wordlist
    int minLength = 5; //(int) refString.length();
    int maxLength = (int) refString.length(); // The maximum length is initialized to the first string
    
    // Loops through the wordlist
    for (int m = 1; m < refListVec.size(); m++) {
        refString = refListVec[m]; // Reference string is set to current string in wordlist
        
//        if (refString.length() < minLength)
//            minLength = (int) refString.length();
        
        // If the current string length is longer than the max length, the max length is updated
        if (refString.length() > maxLength)
            maxLength = (int) refString.length();
    }
    
    std::vector <char> row = puzzle[0]; // Initializes character vector of row to row 1 (used to find lngth of row for loop)
    
    // Loops through each character in the grid
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < row.size(); j++) {
            wordsN(i, j, minLength, maxLength); // Searches north direction
            wordsNE(i, j, minLength, maxLength); // Searches northeast direction
            wordsE(i, j, minLength, maxLength); // Searches east direction
            wordsSE(i, j, minLength, maxLength); // Searches southeast direction
            wordsS(i, j, minLength, maxLength); // Searches south direction
            wordsSW(i, j, minLength, maxLength); // Searches southwest direction
            wordsW(i, j, minLength, maxLength); // Searches west direction
            wordsNW(i, j, minLength, maxLength); // Searches northwest direction
        }
    }
    
    return;
}

// Overloaded print operator, unused
//std::ostream& operator<<(std::ostream& output, const grid& g) {

// Prints grid

//    std::vector <char> temp;
//
//    for (int i = 0; i < g.puzzle.size(); i++) {
//
//        temp = g.puzzle[i];
//
//        for (int j = 0; j < g.puzzle.size(); j++) {
//            output << temp[j] << " ";
//        }
//
//        output << "\n";
//    }
//
//    return output;

// Prints list of word combos in grid

//    std::vector <std::string> gridList = g.gridCombos;
//
//    for (int i = 0; i < gridList.size(); i++) {
//        output << gridList[i] << "\n";
//    }
//
//    return output;
//}

// Searches north direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsN(int row, int col, int minLength, int maxLength) {
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row]; // Current row is set to the input row
    std::string newString; // String of combos created in North direction
    newString += currentRow[col]; // Character at passed in location added to string
    
    // Loops through characters in north direction and adds them to the newString
    for (int i = 1; i <= maxLength; i++) {
        
        // Accounts for reaching top of grid
        if (rowToAppend == 0) {
            rowToAppend = puzzle.size()-1;
            colToAppend = colToAppend;
        }
        // Otherwise row dereased by 1
        else {
            rowToAppend = rowToAppend-1;
            colToAppend = colToAppend;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches northeast direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsNE(int row, int col, int minLength, int maxLength) {
   
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in northeast direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in northeast direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching right edge of grid
        if (colToAppend == puzzle.size()-1) {
            rowToAppend = puzzle.size()-1;
            colToAppend = 0+(puzzle.size()-1-row);
        }
        // Accounts for reaching top of grid
        else if (rowToAppend == 0) {
            rowToAppend = 0+(puzzle.size()-1-col);
            colToAppend = 0;
        }
        else {
            rowToAppend = rowToAppend-1;
            colToAppend = colToAppend+1;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches east direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsE(int row, int col, int minLength, int maxLength) {
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in east direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;                 
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in east direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching right side of grid
        if (colToAppend == puzzle.size()-1) {
            rowToAppend = rowToAppend;
            colToAppend = 0;
        }
        else {
            rowToAppend = rowToAppend;
            colToAppend = colToAppend+1;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches southeast direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsSE(int row, int col, int minLength, int maxLength) {
 
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in southeast direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in southeast direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching right edge of grid
        if (colToAppend == puzzle.size()-1) {
            rowToAppend = 0;
            colToAppend = 0+(puzzle.size()-1-rowToAppend);
        }
        // Accounts for reaching bottom of grid
        else if (rowToAppend == puzzle.size()-1) {
            rowToAppend = 0+(puzzle.size()-1-colToAppend);
            colToAppend = 0;
        }
        else {
            rowToAppend = rowToAppend+1;
            colToAppend = colToAppend+1;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches south direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsS(int row, int col, int minLength, int maxLength) {
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in south direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in south direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching bottom of grid
        if (rowToAppend == puzzle.size()-1) {
            rowToAppend = 0;
            colToAppend = colToAppend;
        }
        else {
            rowToAppend = rowToAppend+1;
            colToAppend = colToAppend;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches southwest direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsSW(int row, int col, int minLength, int maxLength) {
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in southwest direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in southwest direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching left edge of grid
        if (colToAppend == 0) {
            rowToAppend = 0;
            colToAppend = 0+(puzzle.size()-1-rowToAppend);
        }
        // Accounts for reaching bottom edge of grid
        else if (rowToAppend == puzzle.size()-1) {
            rowToAppend = 0+(puzzle.size()-1-colToAppend);
            colToAppend = puzzle.size()-1;
        }
        else {
            rowToAppend = rowToAppend+1;
            colToAppend = colToAppend-1;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches west direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsW(int row, int col, int minLength, int maxLength) {
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in west direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in west direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching left edge of grid
        if (colToAppend == 0) {
            rowToAppend = rowToAppend;
            colToAppend = puzzle.size()-1;
        }
        else {
            rowToAppend = rowToAppend;
            colToAppend = colToAppend-1;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

// Searches northwest direction, adds all appropriate-length combos to the list of combos.
// Takes in row and column of current cahracter being evaluated, and the min and max
// length combos to create.
void grid::wordsNW(int row, int col, int minLength, int maxLength) {
    
    // Initializes the row and column of the next character to be added to create a combo to the current row and column
    // Current row is set to the input row
    // String of combos created in northwest direction
    // Character at passed in location added to string
    int rowToAppend = row, colToAppend = col;
    std::vector <char> currentRow = puzzle[row];
    std::string newString;
    newString += currentRow[col];
    
    // Loops through characters in northwest direction and adds them to the newString
    for (int i  = 1; i <= maxLength; i++) {
        
        // Accounts for reaching left edge of grid
        if (colToAppend == 0) {
            rowToAppend = puzzle.size()-1;
            colToAppend = 0+(puzzle.size()-1-rowToAppend);
        }
        // Accounts for reaching top edge of grid
        else if (rowToAppend == 0) {
            rowToAppend = 0+(puzzle.size()-1-colToAppend);
            colToAppend = puzzle.size()-1;
        }
        else {
            rowToAppend = rowToAppend-1;
            colToAppend = colToAppend-1;
        }
        
        // If the new character reaches itself in a loop, the loop is broken
        if (rowToAppend == row && colToAppend == col)
            return;
        
        currentRow = puzzle[rowToAppend]; // Current row is updated
        newString += currentRow[colToAppend]; // Character in current location is added to the newString
        
        // If the newString is within the length restriction, it is added to the list of combos
        if (newString.length() >= minLength && newString.length() <= maxLength)
            gridCombos.push_back(newString);
    }
    
    return;
}

#endif /* grid_h */
