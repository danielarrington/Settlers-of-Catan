#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player
{
    private:
        string name;
        int wood;
        int bricks;
        int grain;
        int wool;
        int ore;
        
    public:
        Player(string name, int wood, int bricks, int grain, int wool, int ore);
        
        string getName();
        int getWood();
        int getBricks();
        int getGrain();
        int getWool();
        int getOre();
        
        void modifyWood(int wd);
        void modifyBricks(int b);
        void modifyGrain(int g);
        void modifyWool(int wo);
        void modifyOre(int o);
    
};

#endif