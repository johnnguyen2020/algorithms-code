#pragma once
#ifndef CODE_H
#define	CODE_H
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>

#define CODE_SIZE 4

class code {

public:
	code(); // Constructor for a code object with no inputs
	code(int n1, int n2, int n3, int n4); // Constructor for code object with for int inputs
	void initRand(); // Stores a random code in a code object
	int checkCorrect(code guessCode); // Finds how many code digits in one code are the same number and in the same spot as another code
	int checkIncorrect(code guessCode); // Finds how many code digits in one code are the same number and in a different spot as another code
	int getCodeElement(int n); // Returns element n from a code object vector
	void printCode(); // Prints the code in a code object

private:
	std::vector <int> newCode; // Vector data member
};

code::code() {}

code::code(int n1, int n2, int n3, int n4) {
	
	// Four numbers are added to the end of the vector data member
	newCode.push_back(n1);
	newCode.push_back(n2);
	newCode.push_back(n3);
	newCode.push_back(n4);
}

void code::initRand() {

	int remainder; // Used to store a number between 0-5 found using rand()

	srand(time(0)); // Initializes time for rand()
	for (int i = 0; i < 4; i++) 
	{
		remainder = rand() % 6; // Returns a number between 0 and 5
		newCode.push_back(remainder); // Number is placed on the end of vector data member
	}

	return;
}

int code::checkCorrect(code guessCode) {

	int correctCounter = 0; // Counter for correct numbers in correct locations

	// Loops through the vector member in an input code object and compares it to the
	// local object data member. The counter adds 1 for every match.
	for (int i = 0; i < CODE_SIZE; i++) {
		if (guessCode.getCodeElement(i) == newCode[i]) {
			correctCounter++;
		}
	}

	return correctCounter; // The counter variable is returned
}

int code::checkIncorrect(code guessCode) {

	int incorrectNumber = 0; // Counter for correct numbers in incorrect locations
	std::vector<int> copyReal = newCode; // The code data member is copied so it can be edited

	// Loops through the elements of the codes, and if the input code and local code have
	// matching digits in the same element, the copy of the local code is set to -1 so that it cannot
	// be matched in the next loop.
	for (int i = 0; i < CODE_SIZE; i++)
	{
		if (guessCode.getCodeElement(i) == copyReal[i])
			copyReal[i] = -1;
	}

	// Loops through the codes looking for numbers that are the same but in different spots 
	for (int i = 0; i < CODE_SIZE; i++)
	{	
		// If the number in element i of the input code is not the same as the corresponding
		// number in the local code, another for loop is entered to look for a match in another element
		if (guessCode.getCodeElement(i) != newCode[i])
		{
			// The copied code is used for this loop through because the -1 elements in place of the 
			// numbers that got same spot matches will not be counted again.
			for (int j = 0; j < CODE_SIZE; j++)
			{
				// If element i of the input code matches a number, the counter adds 1, and the number in
				// the copied code is set to -1 so that it cannot be counted again. The loop is exited.
				if (guessCode.getCodeElement(i) == copyReal[j])
				{
					incorrectNumber++;
					copyReal[j] = -1;

					break;
				}
			}
		}
	}

	return incorrectNumber; // The counter variable is returned
}

int code::getCodeElement(int n) {

	return newCode[n]; // The number in element i of the vector data in a code object is returned

}

void code::printCode() {

	// The vector elements of a code object are printed
	std::cout << "(";
	for (int i = 0; i < CODE_SIZE; i++)
		std::cout << newCode[i];
	std::cout << ")" << std::endl;

	return;
}

#endif	/* CODE_H */



