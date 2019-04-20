#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

enum developmentType{LIBRARY, UNIVERSITY, TOWNHALL, HARVESTBOUNTY, KNIGHT};

// The base class for all Uno Development Types
class Card{
    protected:
    // describes the Development Type's type
    developmentType type;
    // describes the Development Type's number
    int number;
    
    public:
    // Mutators and Accessors
    void setType(developmentType);
    void setNumber(int);
    developmentType getType();
    int getNumber();
    
    // virtual function to render the Development Type's image in the terminal
    virtual string render(int); 
    // virutal function to call derived class' implementations
    // play returns a boolean to determine if Development Type is valid to play and is 
    // passed the game manager to update changes in the game's state such as
    // turn order reversing or skipping next turn.
    virtual bool play(Card);  
};
class DevelopmentCard : public Card{
    public:
    DevelopmentCard(developmentType, int);
    string render(int);
    bool play(Card);
};

#endif