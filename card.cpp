#include "card.h"

Card::Card(int type)
{
    setType(type);
}

void Card::setType(int t)
{
    type = t;
}

int Card::getType()
{
    return type;
}
