#include <iostream>
#include "player.h"

using namespace std;

Player::Player(string name, int wood, int bricks, int grain, int wool, int ore)
{
    this->name = name;
    this->wood = wood;
    this->bricks = bricks;
    this->grain = grain;
    this->wool = wool;
    this->ore = ore;
}

string Player::getName()
{
    return name;
}

int Player::getWood()
{
    return wood;
}

int Player::getBricks()
{
    return bricks;
}

int Player::getGrain()
{
    return grain;
}

int Player::getWool()
{
    return wool;
}

int Player::getOre()
{
    return ore;
}

void Player::modifyWood(int w)
{
    wood = wood + w;
}

void Player::modifyBricks(int b)
{
    bricks = bricks + b;
}

void Player::modifyGrain(int g)
{
    grain = grain + g;
}

void Player::modifyWool(int wo)
{
    wool = wool + wo;
}

void Player::modifyOre(int o)
{
    ore = ore + o;
}