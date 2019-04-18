#include <iostream>
#include <vector>
#include "tile.h"
#include "player.h"

using namespace std;

void buildIsland(vector<Tile*> &island, int size)
{
    int type;
    for (int i = 0; i < (size * size); i++)
    {
        island.push_back(new EmptyTile((LandType)(rand() % 5), (rand() % 11 + 2))); // I think theres an error with the pushback of the island
    }
}

void renderIsland(vector<Tile*> island, int size)
{
    for (int s = 0; s < size; s++)
    {
        for (int i = 0; i <= 6; i++)
        {
            for (int j = size * s; j < island.size() / size + size * s; j++)
            {
                cout << island.at(j)->render(i) << " ";
            }
            cout << endl;
        }
    }
}

void initializePlayers(vector<Player*> &players, int playerCount)
{
    string name;
    for (int i = 0; i < playerCount; i++)
    {
        cout << "What is Player " << (i + 1) << "'s name? ";
        cin >> name;
        players.push_back(new Player(name, 1, 1, 1, 1, 1, 0));
    }
    
    cout << "Welcome to the Island of Catan";
    
    for (int i = 0; i < playerCount; i++)
    {
        if (i == playerCount - 1)
        {
            cout << " & " << players.at(i)->getName() << "." << endl;
        }
        else
        {
            cout << ", " << players.at(i)->getName();
        }
    }
}

void takeTurn(vector<Player*> &players, int z)
{
    int choice;
    cout << "What would you like to do?" << endl;
    cin >> choice;
    while (choice < 1 || choice > 3)
    {
        cout << "INVALID CHOICE!" << endl;
        cout << "1: Buy, 2: Trade, 3: End Turn";
        cin >> choice;
    }
    if (choice == 1)
    {
        cout << " What would you like to buy?";
        cin >> choice;
        cout << "1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)" << endl;
        cout << "2: City (2 ore, 3 grain)" << endl;
        cout << "3: Development Card (1 ore, 1 grain, 1 wool)" << endl;
        cout << "4: Quit" << endl;
        
        while (choice < 1 || choice > 4)
        {
            cout << "INVALID CHOICE!" << endl;
            cout << "1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)" << endl;
            cout << "2: City (2 ore, 3 grain)" << endl;
            cout << "3: Development Card (1 ore, 1 grain, 1 wool)" << endl;
            cout << "4: Quit" << endl;
        }
        if (choice == 1 && players.at(z))
        {
            cout << "place on which tile? Must be adjacent to existing settlement or city.";
            cout << "Enter row index: ";
            cin >> choice;
            while (choice)             // need to finish this*********
            {
                                       //checks for correct row choice
            }
            cout << "Enter column index: ";
            cin >> choice;
            while (choice)              // need to finish this*********
            {
                                        // checks for correct column choice
            }
            players.at(z)->getWood();
        }
    }
}
    
void resources(vector<Player*> &players, int z)
{
    cout << " Wood( " << players.at(z)->getWood() << " ) Bricks (" << players.at(z)->getBricks() << ") Grain (" << players.at(z)->getGrain() << ") Wool (" << players.at(z)->getWool() << ") Ore (" << players.at(z)->getOre() << endl;
    
}



int main()
{
    int size;
    int playerCount;
    int roll = 0;
    
    vector<Tile*> island;
    vector<Player*> players;
    
    cout << "Enter a value for 'n' between 4 and 7 to create an 'n' by 'n' island: ";
    cin >> size;
    
    while (size < 4 || size > 7)
    {
        cout << "INVALID SIZE!" << endl;
        cout << "Enter a value for 'n' between 4 and 7 to create an 'n' by 'n' island: ";
        cin >> size;
    }
    
    cout << "How many players will there be? (2-4): ";
    cin >> playerCount;
    
    while (playerCount < 2 || playerCount > 4)
    {
        cout << "INVALID PLAYER COUNT!" << endl;
        cout << "How many players will there be? (2-4): ";
        cin >> playerCount;
    }
    initializePlayers(players, playerCount);
    
    buildIsland(island, size);
    renderIsland(island, size);
    
    int z = 0;
    while(players.at(z)->getVictoryPoints() < 10)
    {
        cout << players.at(z)->getName() << " turn." << endl;
        resources(players, z);
        roll = (rand() % 11 + 2);
        takeTurn(players, z);
        
    }
    
    
    return 0;
}
