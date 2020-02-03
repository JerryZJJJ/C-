#include <ctime>
#include <fstream>
#include <string.h>
#include "Player.h"
#include <random>
using namespace std;
class Game{
    public:
    Player **Players;
    int numPlayer;
    int startPlayer;
    std::mt19937 mt_rand;
    int * chip_count;

    Game(int, const int*, long);
    ~Game();
    int countPlayersWithChips();
    int playRound(int);
    const int* playGame(const int* , int);
};

// constructor
Game::Game(int numPlayer, const int * chipDistribution, long seed){
    Players = new Player*[numPlayer];
    this->numPlayer = numPlayer;

    for(int i =0;i<numPlayer;i++){
        Player *temp = new Player(chipDistribution);
        Players[i] = temp;
        temp -> ~Player();
    }

    for(int i =0;i<numPlayer;i++){
        Players[i] -> setLeftPlayer(Players[(i+1) % numPlayer]);
        Players[i] -> setRightPlayer(Players[((i-1)<0?i-1+numPlayer:i-1)]); 
    }

    mt_rand.seed(seed);
    std::uniform_int_distribution<int> dis_int(0,numPlayer-1);
    this ->startPlayer = dis_int(mt_rand);

    chip_count = new int[numPlayer];
}

// destructor
Game::~Game(){
    for(int i=0;i<numPlayer;i++){
        Players[i] -> ~Player();
    }
    delete []Players;
    delete []chip_count;
}

// count how many players have chips
int Game::countPlayersWithChips(){
    int result_chips = 0;
    for(int i=0;i<numPlayer;i++){
        if (Players[i] -> getNumChips()!=0){
            result_chips += 1;
        }
    }
    return result_chips;
}

// play one round with start player
int Game::playRound(int startingPlayer){
    std::uniform_int_distribution<int> dis_int(1,6);
    int sum_center_dice = 0;

    for (int i = 0; i < numPlayer; i++) {
        int d1 = dis_int(mt_rand);
        int d2 = dis_int(mt_rand);
        int d3 = dis_int(mt_rand);
        int index = (i + startingPlayer) % numPlayer; 
        sum_center_dice += Players[index] ->play(d1,d2,d3);
        // cout <<"Player: "<<index<<" "<<Players[index]->getNumChips()<<" (d1,d2,d3) = "<<d1<<" "<<d2<<" "<<d3<<endl;
    }
    return sum_center_dice;
}

const int* Game::playGame(const int* startingChips, int maxRounds){
    int round = 0;

    // set startingChips
    for (int i = 0; i < numPlayer; i++) {
        Players[i] -> setNumChips(startingChips[i]);
    }

    // game simulation
    while (countPlayersWithChips() != 1 && round<maxRounds){
        int sum_center_track = playRound(startPlayer);
        round += 1;
    }

    // return chip count
    for (int i = 0; i < numPlayer; i++) {
        chip_count[i] = Players[i] -> getNumChips();
    }
    return chip_count;

}