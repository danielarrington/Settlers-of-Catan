#include <iostream>
#include <vector>
#include "tile.h"
#include "player.h"

using namespace std;

void buildIsland(vector<Tile*> &island, int size, int playerCount)
{
    for (int i = 0; i < (size * size) - playerCount; i++)
    {
        island.push_back(new EmptyTile((LandType)(rand() % 5), (rand() % 11 + 2)));
    }
    for (int i = 1; i <= playerCount; i++)
    {
        island.push_back(new SettledTile((LandType)(rand() % 5), (rand() % 11 + 2), i));
    }
}

void shuffleIsland(vector<Tile*> &island)
{
    Tile* temp;
    int i1, i2;
    for (int i = 0; i < 1000; i++)
    {
        i1 = rand() % island.size();
        i2 = rand() % island.size();
        temp = island.at(i1);
        island.at(i1) = island.at(i2);
        island.at(i2) = temp;
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

void takeTurn(vector<Player*> &players, int player, int size)
{
    int choice; //Variable to store user menu input
    int row, column; //Variables which store inputs for row and column
    int index; //Variable which stores calculated index in the island vector
    
    //Prompt user for move choice
    cout << "What would you like to do?" << endl;
    cout << "1: Buy" << endl;
    cout << "2: Trade" << endl;
    cout << "3: End Turn" << endl;
    cin >> choice;
    
    //Test to ensure input is valid
    while (choice < 1 || choice > 3)
    {
        cout << "INVALID CHOICE!" << endl;
        cout << "1: Buy" << endl;
        cout << "2: Trade" << endl;
        cout << "3: End Turn" << endl;
        cin >> choice;
    }
    
    //Fork to follow if user chooses to buy
    if (choice == 1)
    {
        cout << "What would you like to buy?" << endl;
        cout << "1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)" << endl;
        cout << "2: City (2 ore, 3 grain)" << endl;
        cout << "3: Development Card (1 ore, 1 grain, 1 wool)" << endl;
        cout << "4: Quit" << endl;
        cin >> choice;
        
        //Test to ensure input is valid
        while (choice < 1 || choice > 4)
        {
            cout << "INVALID CHOICE!" << endl;
            cout << "1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)" << endl;
            cout << "2: City (2 ore, 3 grain)" << endl;
            cout << "3: Development Card (1 ore, 1 grain, 1 wool)" << endl;
            cout << "4: Quit" << endl;
        }
        
        //Fork to follow if user chooses to buy a settlement
        if (choice == 1)
        {
            cout << "BUYING A SETTLEMENT" << endl;
            cout << "On which row is the desired tile located?" << endl;
            
            for(int i = 1; i <= size; i++)
            {
                cout << "[" << i << "]" << endl;
            }
            
            cin >> row;
            
            while(row < 1 || row > size)
            {
                cout << "Error: Row is out of range." << endl;
                cout << "On which row is the desired tile located?" << endl;
                
                for(int i = 1; i <= size; i++)
                {
                    cout << "[" << i << "]" << endl;
                }
                cin >> row;
            }
            
            cout << "On which column is the desired tile located?" << endl;
            
            for(int i = 1; i <= size; i++)
            {
                cout << "[" << i << "] ";
            }
            cout << endl;
            cin >> column;
            
            while(column < 1 || column > size)
            {
                cout << "Error: Column is out of range." << endl;
                cout << "On which column is the desired tile located?" << endl;
            
                for(int i = 1; i <= size; i++)
                {
                    cout << "[" << i << "] ";
                }
                cout << endl;
                cin >> column;
            }
            
            index = size * row - (size - column);
        }
    }
}

void resources(vector<Player*> &players, int z)
{
    cout << "Wood(" << players.at(z)->getWood();
    cout << ") Bricks (" << players.at(z)->getBricks();
    cout << ") Grain (" << players.at(z)->getGrain();
    cout << ") Wool (" << players.at(z)->getWool();
    cout << ") Ore (" << players.at(z)->getOre() << ")" << endl;
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
    
    buildIsland(island, size, playerCount);
    shuffleIsland(island);
    renderIsland(island, size);
    cout << island.size();
    
    int z = 0;
    while(players.at(z)->getVictoryPoints() < 10)
    {
        cout << players.at(z)->getName() << " turn." << endl;
        resources(players, z);
        roll = (rand() % 11 + 2);
        takeTurn(players, z, size);
        
    }
    
    
    return 0;
}
