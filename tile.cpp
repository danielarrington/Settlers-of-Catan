#include <iostream>
#include <iomanip>
#include "tile.h"
#include "player.h"

void Tile::setLand(LandType l){
    land = l;
}

void Tile::setNumber(int n){
    number = n;
}

LandType Tile::getLand(){
    return land;
}

int Tile::getNumber(){
    return number;
}

string Tile::render(int line){
    switch(line){
        case 0: return " ___________ ";
        case 1: return "|           |";
        case 2: return "|           |";
        case 3: return "|           |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|___________|";
        default:
            return " ";
    }
}

EmptyTile::EmptyTile(LandType l, int n){
    setLand(l);
    setNumber(n);
}

string EmptyTile::render(int line){
    stringstream ss;
    switch(line){
        case 0: return " ___________ ";
        case 1: 
            switch(land){
            case FOREST:
                ss << "|Forest   " << setw(2) << number << "|";
                return ss.str();
                break;
            case HILLS:
                ss << "|Hills    " << setw(2) << number << "|";
                return ss.str();
                break;
            case FIELD:
                ss << "|Field    " << setw(2) << number << "|";
                return ss.str();
                break;
            case PASTURE:
                ss << "|Pasture  " << setw(2) << number << "|";
                return ss.str();
                break;
            case MOUNTAIN:
                ss << "|Mountain " << setw(2) << number << "|";
                return ss.str();
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 2: return "|           |";
        case 3: return "|           |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|___________|";
        default:
            return " ";
    }
}

// Need to add parameter to pass in which player established settlement
SettledTile::SettledTile(LandType l, int n){
    setLand(l);
    setNumber(n);
}

// Need to add rendering for player settlement
string SettledTile::render(int line){
    stringstream ss;
    switch(line){
        case 0: return " ___________ ";
        case 1: 
            switch(land){
            case FOREST:
                ss << "|Forest   " << setw(2) << number << "|";
                return ss.str();
                break;
            case HILLS:
                ss << "|Hills    " << setw(2) << number << "|";
                return ss.str();
                break;
            case FIELD:
                ss << "|Field    " << setw(2) << number << "|";
                return ss.str();
                break;
            case PASTURE:
                ss << "|Pasture  " << setw(2) << number << "|";
                return ss.str();
                break;
            case MOUNTAIN:
                ss << "|Mountain " << setw(2) << number << "|";
                return ss.str();
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 2: return "|    ___    |";
        case 3: return "|   /   \\   |";
        case 4: return "|   |___|   |";
        case 5: return "|           |";
        case 6: return "|___________|";
        default:
            return " ";
    }
}