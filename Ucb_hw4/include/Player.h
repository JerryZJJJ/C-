#ifndef XYZ
#define XYZ
#include <ctime>
#include <fstream>
#include <string.h>
class Player{
    public:
    int numChips;
    const int* chipRule;

    Player* leftPlayer;
    Player* rightPlayer;
    Player();
    Player(const int *);
    ~Player();
    void setLeftPlayer(Player* );
    void setRightPlayer(Player* );
    Player* getLeftPlayer();
    Player* getRightPlayer();
    int getNumChips();
    void setNumChips(int);
    int addChips(int);
    int play(int, int, int);
};

Player::Player(){
    const int a[] = {0,0,0,1,2,3};
    this->chipRule = a;
}

Player::Player(const int * chipDistribution){
    chipRule = chipDistribution;
}

Player::~Player(){}

void Player::setLeftPlayer(Player* p){
    leftPlayer = p;
}

void Player::setRightPlayer(Player* p){
    rightPlayer = p;
}

Player* Player::getLeftPlayer(){
    return leftPlayer;
}

Player* Player::getRightPlayer(){
    return rightPlayer;
}

int Player::getNumChips(){
    return numChips;
}

void Player::setNumChips(int nc){
    numChips = nc;
}

int Player::addChips(int nc){
    this->setNumChips(this->getNumChips() + nc);
    return numChips;
}

int Player::play(int d1, int d2, int d3){
    int real_num = min(3,numChips);
    int dice[] = {d1,d2,d3};
    int center_dice = 0;

    for(int i =0;i<real_num;i++){
        int result = chipRule[dice[i]-1];
        switch (result)
        {
        case 0:
            break;
        case 1:
            rightPlayer ->addChips(1);
            numChips -= 1;
            break;
        case 2:
            center_dice +=1;
            numChips -= 1;
            break;
        case 3:
            leftPlayer ->addChips(1);
            numChips -= 1;
            break;
        }
    }
    return center_dice;
}
#endif