#include "card.h"

void Card::setType(developmentType t){
    type = t;
}

void Card::setNumber(int n){     //Setting a number so we can just check an int value with getNumber (getNumber matching a specific value)
    number = n;                 //if getNumber matches a value then this if/elseif/else statement happens. Saves us from having to make 5 different card actions like we did in UNO
}

developmentType Card::getType(){
    return type;
}

int Card::getNumber(){
    return number;
}

string Card::render(int line){
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: return "|           |";
        case 3: return "|           |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

DevelopmentCard::DevelopmentCard(developmentType t, int n){
    setType(t);
    setNumber(n);
}

string DevelopmentCard::render(int line)
    {
    switch(line)
        {
            case 0: return ".___________.";
            case 1: return "|           |";
            case 2: 
            switch(type)
            {
                case LIBRARY:
                    return "|  LIBRARY  |";
                    break;
                case UNIVERSITY:
                    return "|UNIVERSITY |";
                    break;
                case TOWNHALL:
                    return "| TOWN HALL |";
                    break;
                case HARVESTBOUNTY:
                    return "|  HARVEST  |";
                    break;
                case KNIGHT:
                    return "|  KNIGHT  |";
                    break;    
                default:
                    return "|           |";
                    break;
                break;
            }
            case 3:
            switch(type)
            {
                case LIBRARY:
                    return "|           |";
                    break;
                case UNIVERSITY:
                    return "|           |";
                    break;
                case TOWNHALL:
                    return "|           |";
                    break;
                case HARVESTBOUNTY:
                    return "|   BOUNTY  |";
                    break;
                case KNIGHT:
                    return "|           |";
                    break;
            }
            case 4: return "|           |";
            case 5: return "|           |";
            case 6: return "|           |";
            case 7: return "|___________|";
            default:
            return " ";
        }
    }

bool Card::play(Card discard){
    return false;
}
bool DevelopmentCard::play(Card discard){                                   //Super incorrect but needs work, had to put something so it would compile
    if(1){
        return true;
    } else {
        return false;
    }
}
//leaving this trash here incase its needed 