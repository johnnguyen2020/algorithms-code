#pragma once
#ifndef MASTERMIND_H
#define	MASTERMIND_H
#include "code.h"
#include "response.h"
#include "d_except.h"

#define CODE_SIZE 4 // The amount of numbers in a code
#define MAX_ROUNDS 10 // The max number of rounds allowed

class mastermind {

public:
	mastermind(); // Constructor for mastermind object
	void printSecretCode(); // Prints secretCode data member to the screen
	code humanGuess(); // Creates a code object using 4 user input ints
	response getResponse(code real, code guess); // Takes in two codes and returns response object 
	bool isSolved(response resp);
	void playGame(); 

private:
	code secretCode; // Code object used to store the secret code

};

mastermind::mastermind() {}

void mastermind::printSecretCode() {

	// Prints the code object data member
	std::cout << "The Secret Code is ";
	secretCode.printCode();

}

code mastermind::humanGuess() {

	int n1, n2, n3, n4; // The 4 numbers that will make up the guess code

	// Taking in 4 numbers from the user, and will throw exception handles if an input is out of range
	try {
	std::cout << "\nPlease enter the first digit of the guess: ";
	std::cin >> n1;
		if (n1 > 5 || n1 < 0) {
			throw n1;
		}
	}		
	catch (int exHandler) {
		std::cout << "The number you entered is not in the expected range.\n" << std::endl;
	}
	
	try {
		std::cout << "\nPlease enter the second digit of the guess: ";
		std::cin >> n2;
		if (n1 > 5 || n2 < 0) {
			throw n1;
		}
	}
	catch (int exHandler) {
		std::cout << "The number you entered is not in the expected range.\n" << std::endl;
	}

	try {
		std::cout << "\nPlease enter the third digit of the guess: ";
		std::cin >> n3;
		if (n1 > 5 || n3 < 0) {
			throw n1;
		}
	}
	catch (int exHandler) {
		std::cout << "The number you entered is not in the expected range.\n" << std::endl;
	}

	try {
		std::cout << "\nPlease enter the fourth digit of the guess: ";
		std::cin >> n4;
		if (n1 > 5 || n4 < 0) {
			throw n1;
		}
	}
	catch (int exHandler) {
		std::cout << "The number you entered is not in the expected range.\n" << std::endl;
	}

	std::cout << "\n";



	code guessCode(n1, n2, n3, n4); // Initialize the human guess as a code object

	return guessCode; // The guess code object is returned
}

response mastermind::getResponse(code real, code guess) {

	// response object with the number of correct number/correct spot and correct number/incorrect spot
	// numbers found by calling the checkCorrect and checkIncorrect response class functions
	response result(real.checkCorrect(guess), real.checkIncorrect(guess));

	return result; // The result response object is returned
}

bool mastermind::isSolved(response resp) {

	response solved(4, 0); // Response object that signifies a guess that solves the secret code

	// The comparison response class function is called to compare the input response to the solved response
	return resp.comparison(solved); // True is returned if the guess solved the secret
}

void mastermind::playGame() {

	std::cout << "Welcome to Mastermind!\n\nThe computer will generate a random "
		"4 digit code, with each digit being between 0 and 5. You are tasked to try to guess "
		"that code in ten turns or less. After each turn, you will be given a two digit response: "
		"the first digit represents how many numbers were guessed correctly in the right place, "
		"and the second digit represents how many numbers were guessed correctly, but in the "
		"wrong place.\n\nGood Luck!\n\n" << std::endl;

	secretCode.initRand(); // The secretCode data member has a random code stored in it
	//secretCode.printCode();

	bool win = 0; // Will keep track of whether the user guesses the code correctly

	// The game will continue for a maximum of ten rounds
	for (int i = 0; i < MAX_ROUNDS; i++) {

		code userGuess = humanGuess(); // A human guess is initialized as a code object
		response gameResponse = getResponse(secretCode, userGuess); // response object that gives user a response to the guess
		gameResponse.printResponse(); // The computer response is printed
		win = isSolved(gameResponse); // Determines if the user guess solved the code

		// If the the secret code is solved, the for loop is exited
		if (win)
			break;

		// The amount of guesses the user has left is displayed
		if (i != MAX_ROUNDS)
			std::cout << "Remaining guesses: " << MAX_ROUNDS - i - 1 << std::endl;
	}

	// Output is delivered that depends on whether or not the user won
	if (win)
		std::cout << "You Win!" << std::endl;
	else
	{
		std::cout << "Sorry, the computer wins. The secret code is:";
		secretCode.printCode();
		std::cout << ".\n" << std::endl;
	}

	system("pause");

	return;
}

#endif	/* MASTERMIND_H */


