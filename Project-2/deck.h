#ifndef deck_h
#define deck_h
#include "card.h"
#include "node.h"

#define NUM_CARDS 52 // Number of cards in a deck

class deck {
    
public:
    deck(); // Empty constructor for deck
    ~deck();
    card* deal(); // Returns the first card of deck and resets the first card
    void replace(card* repCard); // Puts a card at the bottom of the deck
    void shuffle(); // Shuffles the deck so the order of cards changes
    friend std::ostream& operator << (std::ostream& output, deck& d); // Overloaded print operator
    
private:
    node<card*> *firstCard; // Node of data type card* member that holds the first card in the deck
};

deck::deck() {
    
    node<card*> *temp = new node<card*>(); // Temporary card used to start linked list
    node<card*> *current = temp; // Current card sweeper set to temp card
    
    // Sweeps through 4 suits and 13 values per suit
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j<= 13; j++) {
            // Current node<card*> set to point to a new allocated space for a node<card*>
            current->next = new node<card*> (new card(value(j), suit(i)));
            // The current node<card*> is set to the newly created node<card*>
            current = current->next;
        }
    }
    
    firstCard = temp->next; // The first card in the deck is set to the node<card*> temp points to
    delete temp; // The empty value temp card is deleted
}

deck::~deck() {
    
    node<card*> *currentCard = firstCard;
    node<card*> *toDelete;
    
    while (currentCard != 0) {
        toDelete = currentCard;
        currentCard = currentCard->next;
        delete toDelete;
    }
}

card* deck::deal() {
    
    card* topValue = firstCard->nodeValue;
    node<card*> *previousTop = firstCard;
    firstCard = firstCard->next;
    delete previousTop;
    
    return topValue;
}

void deck::replace(card* repCard) {
    
    // If deck has no cards, passed card is set as the first card
    if (firstCard == NULL) {
        firstCard = new node<card*>(repCard, NULL);
    }
    
    else {
        node<card*> *current = firstCard; // Current card sweeper is set to first card
        while (current->next != NULL) {
            // Current card moves through the entire deck until it reaches the final card
            current = current->next;
        }
        
        // The final card pointer points to a new card of which the value is given as te passed in card
        current->next = new node<card*>(repCard, NULL);
    }
}

void deck::shuffle() {
    
    node<card*> *deck_array[NUM_CARDS]; // Array to hold nodes of type card*
    node<card*> *currentCard = firstCard; // Current card sweeper set to first card in deck
    
    // Each node is placed in an array slot
    for (int i = 1; i < NUM_CARDS; i++) {
        deck_array[i] = currentCard;
        currentCard = currentCard->next;
    }
    
    srand(time(0));
    for (int j = 1; j < NUM_CARDS; j++) {
        int randIndex = rand() % NUM_CARDS;
        node<card*> *tempVal = deck_array[j];
        deck_array[j] = deck_array[randIndex];
        deck_array[randIndex] = tempVal;
    }
    
    firstCard = deck_array[0];
    currentCard = firstCard;
    
    for (int k = 1; k < (NUM_CARDS); k++) {
        currentCard->next = deck_array[k];
        currentCard = currentCard->next;
    }
    
    return;
}

std::ostream& operator << (std::ostream &output, deck& d) {
    
    node<card*> *currentCard;
    currentCard = d.firstCard;
    card *c;
    
    while (currentCard != 0) {
        c = currentCard->nodeValue;
        output << *c << "\n";
        currentCard = currentCard->next;
    }
    
    return output;
}


#endif /* deck_h */


