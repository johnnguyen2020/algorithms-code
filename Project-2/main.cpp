#include <iostream>
#include "card.h"
#include "deck.h"
#include "node.h"

int main() {
    
    deck Deck; // Initializing deck object
    
    //Shuffling deck three times
    Deck.shuffle();
    Deck.shuffle();
    Deck.shuffle();
    
    int play = 1; // Keeps track of whether user wants game to keep going
    int decision;
    int score = 0; // Keeps track of score
    int pointsChange = 0; // Keeps track of score change on current deal
    
    // Game will be played while play is true. User sets play with input at end of each turn.
    while (play == 1) {
        
        pointsChange = 0;
        
        card* dealt; // Initializes card* to hold dealt cards
        dealt = Deck.deal(); // Deals the first card in the deck
        value temp_val = dealt->getValue(); // Value of dealt card
        suit temp_type = dealt->getSuit(); // Suit of dealt card
        
        // Assigns value to pointsChange based on dealt card value
        if (temp_val == ACE)
            pointsChange += 10;
        if (temp_val == KING || temp_val == QUEEN || temp_val == JACK)
            pointsChange += 5;
        if (temp_val == EIGHT || temp_val == NINE || temp_val == TEN)
            pointsChange += 0;
        if (temp_val == SEVEN)
            pointsChange -= score/2;
        if (temp_val == TWO || temp_val == THREE || temp_val == FOUR || temp_val == FIVE || temp_val == SIX)
            pointsChange -= score;
        
        // Extra point awarded for heart
        if(temp_type == HEARTS)
            pointsChange += 1;
        
        score += pointsChange; // Score is updated
        
        std::cout << "The card dealt was the " << *dealt << std::endl;
        if (pointsChange >= 0)
            std::cout << "You have gained " << pointsChange << " points." << std::endl;
        else
            std::cout << "You have lost " << abs(pointsChange) << " points." << std::endl;
        
        std::cout << "Your score is now " << score << "." << std::endl;
        
        std::cout << "\nPress 1 to draw again, or press 0 to end game: ";
        std::cin >> decision;
        
        play = decision;
        
        Deck.replace(dealt); // Replaces dealt card on bottom of deck
    }
    
    std::cout << "Your final score is " << score << "!";
    
    system("pause");
    
    return 0;
}
