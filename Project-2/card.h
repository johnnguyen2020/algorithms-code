#ifndef card_h
#define card_h
#include<iostream>

// Enumerated data type for suits
enum suit {
    SPADES,
    HEARTS,
    CLUBS,
    DIAMONDS
};

// Enumerated data type for values
enum value {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

class card {
    
public:
    card(); // Empty constructor for card
    card(value val, suit type); // Overloaded constructor that gives card a value and suit
    void setValue(value val); // Sets that value of the card to the passed in value
    void setSuit(suit type); // Sets that suit of the card to the passed in suit
    value getValue(); // Returns the value of the card
    suit getSuit(); // Returns the suit of the card
    friend std::ostream& operator<< (std::ostream& output, card& card); // Overloaded print operator
    
private:
    value val; // Enumerated date type member that stores value of card
    suit type; // Enumerated date type member that stores suit of card
};

card::card() {
    
    val = ACE;
    type = SPADES;
}

card::card(value newVal, suit newType) {
    
    val = newVal;
    type = newType;
}

void card::setValue(value newVal) {
    
    val = newVal;
    
    return;
}

void card::setSuit(suit newType) {
    
    type = newType;
    
    return;
}

value card::getValue() {
    
    return val;
}

suit card::getSuit() {
    
    return type;
}

std::ostream& operator<< (std::ostream &output, card& card) {
    
    // Values and suits are matched to their outputs
    if (card.val == ACE)
        output << "Ace";
    if (card.val == TWO)
        output << "Two";
    if (card.val == THREE)
        output << "Three";
    if (card.val == FOUR)
        output << "Four";
    if (card.val == FIVE)
        output << "Five";
    if (card.val == SIX)
        output << "Six";
    if (card.val == SEVEN)
        output << "Seven";
    if (card.val == EIGHT)
        output << "Eight";
    if (card.val == NINE)
        output << "Nine";
    if (card.val == TEN)
        output << "Ten";
    if (card.val == JACK)
        output << "Jack";
    if (card.val == QUEEN)
        output << "QUEEN";
    if (card.val == KING)
        output << "King";
    
    output << " of ";
    
    if (card.type == 0)
        output << "Spades" << std::endl;
    else if (card.type == 1)
        output << "Hearts" << std::endl;
    else if (card.type == 2)
        output << "Clubs" << std::endl;
    else if (card.type == 3)
        output << "Diamonds" << std::endl;
    
    return output;
}

#endif /* card_h */



