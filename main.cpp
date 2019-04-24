#include <iostream>
#include <vector>
#include "tile.h"
#include "player.h"
#include "card.h"
using namespace std;

// Function declarations
void buildDeck(vector<Card*> &deck);
void shuffleDeck(vector<Card*> &deck);
void buildIsland(vector<Tile*> &island, int size, int playerCount);
void shuffleIsland(vector<Tile*> &island);
void renderIsland(vector<Tile*> island, int size);
void initializePlayers(vector<Player*> &players, int playerCount);
void resources(vector<Player*> &players, int z);
void buySettlement(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size);
void buyDevelopmentCard(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size);
void buyCity(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size);
void buyPrompt(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size);
void tradePrompt(vector<Player*> &players, vector<Tile*> &island, int player, int size);
void takeTurn(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size);

// Global variables
int currentPlayer = 0;

// Function definitions
void buildDeck(vector<Card*> &deck)
{
    for (int i = 0; i < 20; i++)
    {
        deck.push_back(new Card(i%5));
    }
}

void shuffleDeck(vector<Card*> &deck)
{
    Card* temp;
    int i1, i2;
    for (int i = 0; i < 1000; i++)
    {
        i1 = rand() % deck.size();
        i2 = rand() % deck.size();
        temp = deck.at(i1);
        deck.at(i1) = deck.at(i2);
        deck.at(i2) = temp;
    }
}

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

void resources(vector<Player*> &players, int z)
{
    cout << "Wood(" << players.at(z)->getWood();
    cout << ") Bricks(" << players.at(z)->getBricks();
    cout << ") Grain(" << players.at(z)->getGrain();
    cout << ") Wool(" << players.at(z)->getWool();
    cout << ") Ore(" << players.at(z)->getOre() << ")" << endl;
}

void buySettlement(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size)
{
    int row, column; //Variables which store inputs for row and column
    int index; //Variable which stores calculated index in the island vector
    
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
    
    //Calculates the index in the vector based off of the row and column input
    index = (size * (row - 1)) + (column - 1);
    cout << index << endl;
    cout << endl << "Vector index: " << (index + 1) << endl;
    cout << "Owner: " << island.at(index)->getOwner() << endl << endl;
    
    //Produce a message to the user if there is already a settlement at
    //the selected tile
    if(island.at(index)->getOwner() != -1)
    {
        renderIsland(island, size);
        cout << endl << "There is already a settlement on this tile." << endl;
        cout << "Please choose another tile." << endl << endl;
        buySettlement(players, island, deck, player, size);
    }
    
    //The selected tile is not already settled
    else
    {
        int land = island.at(index)->getLand(); //Save the landtype of the current tile
        int value = island.at(index)->getNumber(); //Sae the number of the current tile
        
        //The user chose the first row (don't test tile above)
        if(row == 1)
        { 
            //The user chose the first column (don't test tile to the left)
            if(column == 1)
            {
                //Verifies that the player owns a settlement either to the right of or below the chosen tile
                if(island.at(1)->getOwner() == (player + 1) || island.at(size)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
            
            //The user chose the last column (don't test tile to the right)
            else if(column == size)
            {
                //Verifies that the player owns a settlement either to the left of or below the chosen tile
                if(island.at(size - 1)->getOwner() == (player + 1) || island.at((size * 2) - 1)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
            
            //The user did not choose a side column (test both left and right)
            else
            {
                //Verifies that the player owns a settlement either to the left of, to the right of, or below the chosen tile
                if(island.at(column - 2)->getOwner() == (player + 1) || island.at(column)->getOwner() == (player + 1) || island.at(size + column - 1)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
        }
        
        //The user chose the bottom row (don't test tile below)
        else if(row == size)
        {
            //The user chose the first column (don't test tile to the left)
            if(column == 1)
            {
                //Verifies that the player owns a settlement either to the right of or above the chosen tile
                if(island.at(index + 1)->getOwner() == (player + 1) || island.at(index - size)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
            
            //The user chose the last column (don't test tile to the right)
            else if(column == size)
            {
                //Verifies that the player owns a settlement either to the left of or above the chosen tile
                if(island.at(index - 1)->getOwner() == (player + 1) || island.at(index - size)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
            
            //The user did not choose a side column (test both left and right)
            else
            {
                //Verifies that the player owns a settlement either to the left of, to the right of, or above the chosen tile
                if(island.at(index - 1)->getOwner() == (player + 1) || island.at(index + 1)->getOwner() == (player + 1) || island.at(index - size)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
        }
        
        //The user did not choose the top or bottom row (test both above and below)
        else
        {
            //The user chose the first column (don't test tile to the left)
            if(column == 1)
            {
                //Verifies that the player owns a settlement either above, below, or to the right of the chosen tile
                if(island.at(index - size)->getOwner() == (player + 1) || island.at(index + size)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
            
            //The user chose the last column (don't test tile to the right)
            else if(column == size)
            {
                //Verifies that the player owns a settlement either above, below, or to the left of the chosen tile
                if(island.at(index - size)->getOwner() == (player + 1) || island.at(index + size)->getOwner() == (player + 1) || island.at(index - 1)->getOwner() == (player + 1) || island.at(index + 1)->getOwner() == player)
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
            
            //The user did not choose a side column (test both left and right)
            else
            {
                //Verifies that the player owns a settlement either above, below, to the right of, or to the left of the chosen tile
                if(island.at(index - size)->getOwner() == (player + 1) || island.at(index + size)->getOwner() == (player + 1) || island.at(index + 1)->getOwner() == (player + 1) || island.at(index - 1)->getOwner() == (player + 1))
                {
                    island.at(index) = new SettledTile((LandType)land, value, (player + 1));
                    players.at(player)->modifyWood(-1);
                    players.at(player)->modifyBricks(-1);
                    players.at(player)->modifyGrain(-1);
                    players.at(player)->modifyWool(-1);
                    players.at(player)->modifyOre(-1);
                    renderIsland(island, size);
                    takeTurn(players, island, deck, player, size);
                }
                else
                {
                    renderIsland(island, size);
                    cout << endl << "You don't own a settlement on an adjacent tile." << endl;
                    cout << "Please choose another tile." << endl << endl;
                    buySettlement(players, island, deck, player, size);
                }
            }
        }
    }
}

void buyDevelopmentCard(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size)
{
    int type = deck.at(deck.size() - 1)->getType();
    deck.pop_back();
    int input = 0;
    int resource = rand() % 5;
    
    players.at(player - 1)->modifyOre(-1);
    players.at(player - 1)->modifyGrain(-1);
    players.at(player - 1)->modifyWool(-1);
    
    //Library card is drawn
    if(type == 0)
    {
        cout << "You drew a Library card." << endl;
        cout << "You have been awarded one victory point!" << endl;
        players.at(player - 1)->modifyVictoryPoints(1);
    }
    //University card is drawn
    else if(type == 1)
    {
        cout << "You drew a University card." << endl;
        cout << "You have been awarded one victory point!" << endl;
        players.at(player - 1)->modifyVictoryPoints(1);
    }
    //Town hall card is drawn
    else if(type == 2)
    {
        cout << "You drew a Town Hall card." << endl;
        cout << "You have been awarded one victory point!" << endl;
        players.at(player - 1)->modifyVictoryPoints(1);
    }
    //Harvest Bounty card is drawn
    else if(type == 3)
    {
        cout << "You drew a Harvest Bounty card." << endl;
        cout << "You have been awarding one of each resource!" << endl;
        players.at(player - 1)->modifyWood(1);
        players.at(player - 1)->modifyBricks(1);
        players.at(player - 1)->modifyGrain(1);
        players.at(player - 1)->modifyWool(1);
        players.at(player - 1)->modifyOre(1);
    }
    //Knight card is drawn
    else
    {
        cout << "You drew a Knight card." << endl;
        cout << "Choose a player to steal a random resource from." << endl;
        for (int i = 0; i < players.size(); i++)
        {
            if(i != (player - 1))
            {
                cout << i+1 << ": " << players.at(i)->getName() << endl;
            }
        }
        cin >> input;
        
        while(input == player || input < 0 || input > players.size())
        {
            cout << "Invalid player choice." << endl;
            cout << "Choose a player to steal a random resource from: ";
            cin >> input;
        }
        
        switch (resource)
        {
            case 0:
                if(players.at(input - 1)->getWood() != 0)
                {
                    players.at(input - 1)->modifyWood(-1);
                    players.at(player - 1)->modifyWood(1);
                    cout << players.at(player - 1)->getName() << " stole 1 wood from " << players.at(input - 1)->getName() << "!" << endl;
                    break;  
                }
            case 1:
                if(players.at(input - 1)->getBricks() != 0)
                {
                    players.at(input - 1)->modifyBricks(-1);
                    players.at(player - 1)->modifyBricks(1);
                    cout << players.at(player - 1)->getName() << " stole 1 brick from " << players.at(input - 1)->getName() << "!" << endl;
                    break;
                }
            case 2:
                if(players.at(input - 1)->getGrain() != 0)
                {
                    players.at(input - 1)->modifyGrain(-1);
                    players.at(player - 1)->modifyGrain(1);
                    cout << players.at(player - 1)->getName() << " stole 1 grain from " << players.at(input - 1)->getName() << "!" << endl;
                    break;
                }
            case 3:
                if(players.at(input - 1)->getWool() != 0)
                {
                    players.at(input - 1)->modifyWool(-1);
                    players.at(player - 1)->modifyWool(1);
                    cout << players.at(player - 1)->getName() << " stole 1 wool from " << players.at(input - 1)->getName() << "!" << endl;
                    break;
                }
            case 4:
                if(players.at(input - 1)->getOre() != 0)
                {
                    players.at(input - 1)->modifyOre(-1);
                    players.at(player - 1)->modifyOre(1);
                    cout << players.at(player - 1)->getName() << " stole 1 ore from " << players.at(input - 1)->getName() << "!" << endl;
                    break;
                }
        }
    }
}

void buyCity(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size)
{
    int row, column; //Variables which store inputs for row and column
    int index; //Variable which stores calculated index in the island vector
    
    cout << "BUYING A CITY" << endl;
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
    
    //Calculates the index in the vector based off of the row and column input
    index = (size * (row - 1)) + (column - 1);
    cout << index << endl;
    cout << endl << "Vector index: " << (index + 1) << endl;
    cout << "Owner: " << island.at(index)->getOwner() << endl << endl;
    
    //Produce a message to the user if there is already a settlement at
    //the selected tile
    if(island.at(index)->getOwner() != (player + 1) && ((island.at(index)->getOwner()) / 10) != (player + 1))
    {
        renderIsland(island, size);
        cout << endl << "This is not your Settlement" << endl;
        cout << "Please choose another tile." << endl << endl;
        buyCity(players, island, deck, player, size);
    }
    else if((island.at(index)->getOwner() / 10) == (player + 1))
    {
        renderIsland(island, size);
        cout << endl << "You already have a city here." << endl;
        cout << "Please choose another tile." << endl << endl;
        buyCity(players, island, deck, player, size);
    }
    
    //The selected tile is not already settled
    else
    {
        int land = island.at(index)->getLand(); //Save the landtype of the current tile
        int value = island.at(index)->getNumber(); //Sae the number of the current tile
        int owner = island.at(index)->getOwner();
        owner = owner * 10;
        island.at(index) = new cityTile((LandType)land, value, owner); 
        players.at(player)->modifyWood(-1);
        players.at(player)->modifyGrain(-3);
        takeTurn(players, island, deck, currentPlayer, size);
    }
}

void buyPrompt(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size)
{
    int choice = 0;
    
    while (choice != 4)
    {
        cout << "What would you like to buy?" << endl;
        cout << "1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)" << endl;
        cout << "2: City (2 ore, 3 grain)" << endl;
        cout << "3: Development Card  (1 ore, 1 grain, 1 wool)" << endl;
        cout << "4: Back" << endl;
        cin >> choice;
        
        //Test to ensure input is valid
        while (choice < 1 || choice > 4)
        {
            cout << "INVALID CHOICE!" << endl;
            cout << "1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)" << endl;
            cout << "2: City (2 ore, 3 grain)" << endl;
            cout << "3: Development Card (1 ore, 1 grain, 1 wool)" << endl;
            cout << "4: Back" << endl;
            cin >> choice;
        }
        
        //Fork to follow if user chooses to buy a settlement if they have enough resources
        if (choice == 1)
        {
            if(players.at(player)->getWood() >= 1 && players.at(player)->getBricks() >= 1 && players.at(player)->getGrain() >= 1 && players.at(player)->getWool() >= 1)
            {
                buySettlement(players, island, deck, player, size); // theres an error
            }
            else
            {
                cout << "You do not have enough resources to build a settlement." << endl;
                takeTurn(players, island, deck, player, size);
            }
        }
        else if (choice == 2)
        {
            if(players.at(player)->getOre() >= 2 && players.at(player)->getGrain() >= 3)
            {
                buyCity(players, island, deck, player, size);//Call function for buying a city
            }
            else
            {
                cout << "You do not have enough resources to build a city." << endl;
                takeTurn(players, island, deck, player, size);
            }
        }
        else if (choice == 3)
        {
            if(players.at(player)->getOre() >= 1 && players.at(player)->getGrain() >= 1 && players.at(player)->getWool() >= 1)
            {
                buyDevelopmentCard(players, island, deck, player, size);
            }
            else
            {
                cout << "You do not have enough resources to buy a development card." << endl;
                takeTurn(players, island, deck, player, size);
            }
        }
    }
}

void tradePrompt(vector<Player*> &players, vector<Tile*> &island, int player, int size)
{
    int playerChoice, giveRsrc, giveAmt, recRsrc, recAmt = 0;
    bool done = false;
    char response;
    
    cout << "Who would you like to trade with?" << endl;
        
    for (int i = 0; i < players.size(); i++)
    {
        if(i != player)
        {
            cout << i+1 << ": " << players.at(i)->getName() << endl;
        }
    }
    
    cin >> playerChoice;
    
    while(playerChoice < 1 || playerChoice > players.size() || playerChoice == player)
    {
        cout << "Invalid player choice." << endl;
        cout << "Who would you like to trade with?" << endl;
        
        for (int i = 0; i < players.size(); i++)
        {
            if(i != player)
            {
                cout << i+1 << ": " << players.at(i)->getName() << endl;
            }
        }
        cin >> playerChoice;
    }
    
    cout << "You currently have ";
    resources(players, currentPlayer);
    cout << "Which resource would you like to give " << players.at(playerChoice-1)->getName() << "?" << endl;
    cout << "1: Wood" << endl;
    cout << "2: Brick" << endl;
    cout << "3: Grain" << endl;
    cout << "4: Wool" << endl;
    cout << "5: Ore" << endl;
    cin >> giveRsrc;
    
    do{
        cout << "How many?" << endl;
        cin >> giveAmt;

        switch(giveRsrc){
            case 1:
                if (players.at(currentPlayer)->getWood() < giveAmt){
                    cout << "You dont have enough resources for that trade. Try again." << endl;
                    break;
                }
                else
                    done = true;
            case 2:
                if (players.at(currentPlayer)->getBricks() < giveAmt){
                    cout << "You dont have enough resources for that trade. Try again." << endl;
                    break;
                }
                else
                    done = true;
            case 3:
                if (players.at(currentPlayer)->getGrain() < giveAmt){
                    cout << "You dont have enough resources for that trade. Try again." << endl;
                    break;
                }
                else
                    done = true;
            case 4:
                if (players.at(currentPlayer)->getWool() < giveAmt){
                    cout << "You dont have enough resources for that trade. Try again." << endl;
                    break;
                }
                else
                    done = true;
            case 5:
                if (players.at(currentPlayer)->getOre() < giveAmt){
                    cout << "You dont have enough resources for that trade. Try again." << endl;
                    break;
                }
                else
                    done = true;
        }
    } while(!done);
    done = false;
    cout << "Which resource would you like to ask " << players.at(playerChoice-1)->getName() << " for?" << endl;
    cout << "1: Wood" << endl;
    cout << "2: Brick" << endl;
    cout << "3: Grain" << endl;
    cout << "4: Wool" << endl;
    cout << "5: Ore" << endl;
    cin >> recRsrc;
    
    cout << "How many?" << endl;
    cin >> recAmt;
    
    cout << players.at(playerChoice-1)->getName() << ", will you trade with " << players.at(currentPlayer)->getName() << "? (Y or N)" << endl;
    cin >> response;
    
    // Need code to check if response != y or n
    if (response == 'Y' || response == 'y'){
        do{
            switch(recRsrc){
                case 1:
                    if (players.at(playerChoice-1)->getWood() < recAmt){
                        cout << players.at(playerChoice-1)->getName() << " does not have enough resources for that trade." << endl;
                        break;
                    }
                    else if (giveRsrc == 1){
                        players.at(currentPlayer)->modifyWood(-giveAmt);
                        players.at(currentPlayer)->modifyWood(recAmt);
                        players.at(playerChoice-1)->modifyWood(giveAmt);
                        players.at(playerChoice-1)->modifyWood(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 2){
                        players.at(currentPlayer)->modifyWood(-giveAmt);
                        players.at(currentPlayer)->modifyBricks(recAmt);
                        players.at(playerChoice-1)->modifyWood(giveAmt);
                        players.at(playerChoice-1)->modifyBricks(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 3){
                        players.at(currentPlayer)->modifyWood(-giveAmt);
                        players.at(currentPlayer)->modifyGrain(recAmt);
                        players.at(playerChoice-1)->modifyWood(giveAmt);
                        players.at(playerChoice-1)->modifyGrain(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 4){
                        players.at(currentPlayer)->modifyWood(-giveAmt);
                        players.at(currentPlayer)->modifyWool(recAmt);
                        players.at(playerChoice-1)->modifyWood(giveAmt);
                        players.at(playerChoice-1)->modifyWool(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 5){
                        players.at(currentPlayer)->modifyWood(-giveAmt);
                        players.at(currentPlayer)->modifyOre(recAmt);
                        players.at(playerChoice-1)->modifyWood(giveAmt);
                        players.at(playerChoice-1)->modifyOre(-recAmt);
                        done = true;
                    }
                case 2:
                    if (players.at(playerChoice-1)->getBricks() < recAmt){
                        cout << players.at(playerChoice-1)->getName() << " does not have enough resources for that trade." << endl;
                        break;
                    }
                    else if (giveRsrc == 1){
                        players.at(currentPlayer)->modifyBricks(-giveAmt);
                        players.at(currentPlayer)->modifyWood(recAmt);
                        players.at(playerChoice-1)->modifyBricks(giveAmt);
                        players.at(playerChoice-1)->modifyWood(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 2){
                        players.at(currentPlayer)->modifyBricks(-giveAmt);
                        players.at(currentPlayer)->modifyBricks(recAmt);
                        players.at(playerChoice-1)->modifyBricks(giveAmt);
                        players.at(playerChoice-1)->modifyBricks(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 3){
                        players.at(currentPlayer)->modifyBricks(-giveAmt);
                        players.at(currentPlayer)->modifyGrain(recAmt);
                        players.at(playerChoice-1)->modifyBricks(giveAmt);
                        players.at(playerChoice-1)->modifyGrain(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 4){
                        players.at(currentPlayer)->modifyBricks(-giveAmt);
                        players.at(currentPlayer)->modifyWool(recAmt);
                        players.at(playerChoice-1)->modifyBricks(giveAmt);
                        players.at(playerChoice-1)->modifyWool(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 5){
                        players.at(currentPlayer)->modifyBricks(-giveAmt);
                        players.at(currentPlayer)->modifyOre(recAmt);
                        players.at(playerChoice-1)->modifyBricks(giveAmt);
                        players.at(playerChoice-1)->modifyOre(-recAmt);
                        done = true;
                    }
                case 3:
                    if (players.at(playerChoice-1)->getGrain() < recAmt){
                        cout << players.at(playerChoice-1)->getName() << " does not have enough resources for that trade." << endl;
                        break;
                    }
                    else if (giveRsrc == 1){
                        players.at(currentPlayer)->modifyGrain(-giveAmt);
                        players.at(currentPlayer)->modifyWood(recAmt);
                        players.at(playerChoice-1)->modifyGrain(giveAmt);
                        players.at(playerChoice-1)->modifyWood(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 2){
                        players.at(currentPlayer)->modifyGrain(-giveAmt);
                        players.at(currentPlayer)->modifyBricks(recAmt);
                        players.at(playerChoice-1)->modifyGrain(giveAmt);
                        players.at(playerChoice-1)->modifyBricks(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 3){
                        players.at(currentPlayer)->modifyGrain(-giveAmt);
                        players.at(currentPlayer)->modifyGrain(recAmt);
                        players.at(playerChoice-1)->modifyGrain(giveAmt);
                        players.at(playerChoice-1)->modifyGrain(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 4){
                        players.at(currentPlayer)->modifyGrain(-giveAmt);
                        players.at(currentPlayer)->modifyWool(recAmt);
                        players.at(playerChoice-1)->modifyGrain(giveAmt);
                        players.at(playerChoice-1)->modifyWool(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 5){
                        players.at(currentPlayer)->modifyGrain(-giveAmt);
                        players.at(currentPlayer)->modifyOre(recAmt);
                        players.at(playerChoice-1)->modifyGrain(giveAmt);
                        players.at(playerChoice-1)->modifyOre(-recAmt);
                        done = true;
                    }
                case 4:
                    if (players.at(playerChoice-1)->getWool() < recAmt){
                        cout << players.at(playerChoice-1)->getName() << " does not have enough resources for that trade." << endl;
                        break;
                    }
                    else if (giveRsrc == 1){
                        players.at(currentPlayer)->modifyWool(-giveAmt);
                        players.at(currentPlayer)->modifyWood(recAmt);
                        players.at(playerChoice-1)->modifyWool(giveAmt);
                        players.at(playerChoice-1)->modifyWood(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 2){
                        players.at(currentPlayer)->modifyWool(-giveAmt);
                        players.at(currentPlayer)->modifyBricks(recAmt);
                        players.at(playerChoice-1)->modifyWool(giveAmt);
                        players.at(playerChoice-1)->modifyBricks(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 3){
                        players.at(currentPlayer)->modifyWool(-giveAmt);
                        players.at(currentPlayer)->modifyGrain(recAmt);
                        players.at(playerChoice-1)->modifyWool(giveAmt);
                        players.at(playerChoice-1)->modifyGrain(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 4){
                        players.at(currentPlayer)->modifyWool(-giveAmt);
                        players.at(currentPlayer)->modifyWool(recAmt);
                        players.at(playerChoice-1)->modifyWool(giveAmt);
                        players.at(playerChoice-1)->modifyWool(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 5){
                        players.at(currentPlayer)->modifyWool(-giveAmt);
                        players.at(currentPlayer)->modifyOre(recAmt);
                        players.at(playerChoice-1)->modifyWool(giveAmt);
                        players.at(playerChoice-1)->modifyOre(-recAmt);
                        done = true;
                    }
                case 5:
                    if (players.at(playerChoice-1)->getOre() < recAmt){
                        cout << players.at(playerChoice-1)->getName() << " does not have enough resources for that trade." << endl;
                        break;
                    }
                    else if (giveRsrc == 1){
                        players.at(currentPlayer)->modifyOre(-giveAmt);
                        players.at(currentPlayer)->modifyWood(recAmt);
                        players.at(playerChoice-1)->modifyOre(giveAmt);
                        players.at(playerChoice-1)->modifyWood(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 2){
                        players.at(currentPlayer)->modifyOre(-giveAmt);
                        players.at(currentPlayer)->modifyBricks(recAmt);
                        players.at(playerChoice-1)->modifyOre(giveAmt);
                        players.at(playerChoice-1)->modifyBricks(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 3){
                        players.at(currentPlayer)->modifyOre(-giveAmt);
                        players.at(currentPlayer)->modifyGrain(recAmt);
                        players.at(playerChoice-1)->modifyOre(giveAmt);
                        players.at(playerChoice-1)->modifyGrain(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 4){
                        players.at(currentPlayer)->modifyOre(-giveAmt);
                        players.at(currentPlayer)->modifyWool(recAmt);
                        players.at(playerChoice-1)->modifyOre(giveAmt);
                        players.at(playerChoice-1)->modifyWool(-recAmt);
                        done = true;
                    }
                    else if (giveRsrc == 5){
                        players.at(currentPlayer)->modifyOre(-giveAmt);
                        players.at(currentPlayer)->modifyOre(recAmt);
                        players.at(playerChoice-1)->modifyOre(giveAmt);
                        players.at(playerChoice-1)->modifyOre(-recAmt);
                        done = true;
                    }
            }
        } while(!done);
        resources(players, currentPlayer);
        resources(players, playerChoice-1);
    }
}

void takeTurn(vector<Player*> &players, vector<Tile*> &island, vector<Card*> &deck, int player, int size)
{
    int choice = 0; //Variable to store user menu input
    
    while (choice != 4)
    {
    //Prompt user for move choice
    cout << "What would you like to do?" << endl;
    cout << "1: Buy" << endl;
    cout << "2: Trade" << endl;
    cout << "3: Swap" << endl;
    cout << "4: End Turn" << endl;
    cin >> choice;
    
    //Test to ensure input is valid
    while (choice < 1 || choice > 4)
    {
        cout << "INVALID CHOICE!" << endl;
        cout << "1: Buy" << endl;
        cout << "2: Trade" << endl;
        cout << "3: Swap" << endl;
        cout << "4: End Turn" << endl;
        cin >> choice;
    }

    // Buy
    if (choice == 1)
        buyPrompt(players, island, deck, player, size);
    // Trade
    else if (choice == 2)
        tradePrompt(players, island, player, size);
    //Swap three resources for one
    else if (choice == 3)
    {
        //Implement code to swap resources
    }
        

    //Swap three cards for one
    //else if (choice == 3)
        //Implement code to swap cards


    //Swap three cards for one
    //else if (choice == 3)
        //Implement code to swap cards
    }
}

int main()
{
    //Seed the random number generator
    srand(time(0));
    //Declare variables used to store size of n x n island
    //as well as number of players in the game
    int size;
    int playerCount;
    //Declare variables for the current player indicator as
    //well as the dice roll value and initialize them at 0
    int currentPlayer = 0;
    int roll = 0;
    //Create vectors to store tile objects for the island,
    //player objects for each player, and card objects for
    //the development card deck
    vector<Tile*> island;
    vector<Player*> players;
    vector<Card*> deck;
    
    //Prompt user to input size for an n x n island, then store in size variable
    cout << "Enter a value for 'n' between 4 and 7 to create an 'n' by 'n' island: ";
    cin >> size;
    //Validate size input
    while (size < 4 || size > 7)
    {
        cout << "INVALID SIZE!" << endl;
        cout << "Enter a value for 'n' between 4 and 7 to create an 'n' by 'n' island: ";
        cin >> size;
    }
    
    //Prompt user to input number of players
    cout << "How many players will there be? (2-4): ";
    cin >> playerCount;
    //Validate input for number of players
    while (playerCount < 2 || playerCount > 4)
    {
        cout << "INVALID PLAYER COUNT!" << endl;
        cout << "How many players will there be? (2-4): ";
        cin >> playerCount;
    }
    
    //Build player vector
    initializePlayers(players, playerCount);
    //Build island vector
    buildIsland(island, size, playerCount);
    //Shuffle the elements in the island vector to promote randomness
    shuffleIsland(island);
    //Display the island
    renderIsland(island, size);
    
    //Loop to continue gameplay until a player reaches 10 victory points
    while(players.at(currentPlayer)->getVictoryPoints() < 10)
    {
        //Output to display the current player's name as well as their resources
        cout << players.at(currentPlayer)->getName() << "'s turn." << endl;
        resources(players, currentPlayer);
        //Dice roll
        roll = (rand() % 11 + 2);
        //Functionality for turn taking
        takeTurn(players, island, deck, currentPlayer, size); 
        /* ********Look at this line and look at intialize players line, to make it easier for you******
        to see I'll copy and paste it here:
        When current players is intialized to zero and player count is taken its immediately sent up to initializePlayers
        takeTurn(players, island, currentPlayer + 1, size); causes you to skip over an entire player and when you want the last player to play their turn
        it bugs out
        But since initializePlayers FIRST value is actually zero, the program is skipping over an entire player
        I've tried tweaking it a bunch but with the if loop in intialize players to help print their name I keep getting another error which is
        the exact same thing that shows up. Ill keep looking at it, but 6 eyes are better than two :)
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

*/
        //Re-render island when user choses to end their turn
        renderIsland(island, size);
        //Increment current player counter
        currentPlayer++;
        //Validate that the current player does not exceed the total
        //number of players. currentPlayer variable maximum should never
        //exceed (playerCount - 1) because playerCount is a raw integer that
        //is used to indicate the true number of players, whereas currentPlayer
        //is used as index to reference the player vector (which starts at 0).
        if(currentPlayer == (playerCount - 1))
        {
            currentPlayer = 0;
        }
    }
    return 0;
}
