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
        island.push_back(new EmptyTile((LandType)(rand() % 5), (rand() % 11 + 2)));
    }
}

void renderIsland(vector<Tile*> island, int size)
{
    for (int s = 0; s <= size; s++)
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
        players.push_back(new Player(name, 1, 1, 1, 1, 1));
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

int main()
{
    int size;
    int playerCount;
    
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
    
    return 0;
}