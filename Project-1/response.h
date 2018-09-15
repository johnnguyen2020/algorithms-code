#pragma once
#ifndef RESPONSE_H
#define	RESPONSE_H
#include<iostream>

class response {

public:
	response(); // Constructor for response object with no inputs
	response(int correct, int incorrect); // Constructor for response object with two int inputs
	bool comparison(response resp1); // Compares the local response object with an input response object
	int getResponseCorrect(); // Extracts the numCorrect member of a response object
	int getResponseIncorrect(); // Extracts the numIncorrect member of a response object
	void printResponse(); // Prints the two data members of a response object

private:
	int numCorrect; // The number of correct number correct spot matches between two codes
	int numIncorrect; // The number of correct number incorrect spot matches between two codes

};

response::response() {}

response::response(int correct, int incorrect) {
	
	// Sets numCorrect and numIncorrect to the input ints
	numCorrect = correct;
	numIncorrect = incorrect;

}

bool response::comparison(response resp1) {

	// Compares two reponse objects and returns true if their corresponding numCorrect and 
	// numIncorrect members are equal, and false otherwise
	return (numCorrect == resp1.getResponseCorrect()) &&
		(numIncorrect == resp1.getResponseIncorrect());
}

int response::getResponseCorrect() {

	return numCorrect; // Extracts the numCorrect data member
}

int response::getResponseIncorrect() {

	return numIncorrect; // Extracts the numIncorrect data member
}

void response::printResponse() {

	// Prints the members of response object
	std::cout << "\nYour guess has the following result: ";
	std::cout << "(" << numCorrect << ", " << numIncorrect << ")\n" << std::endl;

	return;
}

#endif	/* RESPONSE_H */
