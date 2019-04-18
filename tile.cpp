#include <iostream>
#include <iomanip>
#include "tile.h"

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
        case 1: return "|           |";
        case 2: 
            switch(land){
            case FOREST:
                return "|  FOREST   |";
                break;
            case HILLS:
                return "|   HILLS   |";
                break;
            case FIELD:
                return "|   FIELD   |";
                break;
            case PASTURE:
                return "|  PASTURE  |";
                break;
            case MOUNTAIN:
                return "| MOUNTAIN  |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|    " << setw(2) << number << "     |";
            return ss.str();
            break;
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
        case 1: return "|           |";
        case 2: 
            switch(land){
            case FOREST:
                return "|  FOREST   |";
                break;
            case HILLS:
                return "|   HILLS   |";
                break;
            case FIELD:
                return "|   FIELD   |";
                break;
            case PASTURE:
                return "|  PASTURE  |";
                break;
            case MOUNTAIN:
                return "| MOUNTAIN  |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|    " << setw(2) << number << "     |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|___________|";
        default:
            return " ";
    }
}