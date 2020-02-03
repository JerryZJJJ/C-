#include <math.h>
#include <iomanip> 
using namespace std;
#include <iostream>
#include <random>
#include <ctime>
#include "Player.h"
#include "Game.h"

void SimulateGame(const char* desc
				, int numPlayers
				, const int* chipDistribution
				, long seed
				, const int* startingChips
				, int maxRounds
				, ostream& outputStream) 
{
	
	// create the game object
	Game game(numPlayers, chipDistribution, seed);

	// initialize our expected chips array
	double* expectedChips= new double[numPlayers];
	for (int i = 0; i < numPlayers; i++) {
		expectedChips[i] = 0;
	}

	double roundsWithWinner = 0;
	// run 100000 simulations
	for (int s = 0; s < 100000; s++) {
		
		// play a single game
		const int* playerChips = game.playGame(startingChips, maxRounds);
		
		// keep track of chips held at end of game
		for (int i = 0; i < numPlayers; i++) {
			expectedChips[i] += playerChips[i];
		}
		
		// was there a single winner?
		if (game.countPlayersWithChips() == 1) {
			roundsWithWinner += 1;
		}

		// for simulation iterations of 100, 1000, 10000 and 100000, write the output
		if ((s + 1) == 100 || (s + 1) == 1000 || (s + 1) == 10000 || (s + 1) == 100000) {
			cout << desc << ',' << (s + 1) << endl;
			outputStream << desc << ',' << (s + 1) << ',' << (roundsWithWinner/(s+1));
			for (int i = 0; i < numPlayers; i++) {
				double ev = expectedChips[i] / (s + 1);
				outputStream << ',' << ev;
			}
			outputStream << endl;
		}

	}
}


int main()
{
	ofstream outfile;

	// open the file
	outfile.open("lcr_output.csv");

	// write a header
	outfile << "Game,MaxRounds,RoundsWithWinner" ;
	for (int i = 0; i < 9; i++) {
		outfile << ",Player" << (i + 1);
	}
	outfile << endl;

	// standard game
	int chipDistribution[] = { 0,0,0,1,2,3 };
	int playerChips[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10};
	SimulateGame("standard", 9, chipDistribution, (long)time(0), playerChips, 100, outfile);

	// standard game - one player has more
	int playerChipsTilted[] = { 5, 5, 5, 5, 50, 5, 5, 5, 5, 5 };
	SimulateGame("standard-tilted", 9, chipDistribution, (long)time(0), playerChipsTilted, 100, outfile);

	// game with greater chance of passing but no center 
	int chipDistributionNoCenter[] = { 0,0,1,1,3,3 };
	SimulateGame("nocenter", 9, chipDistributionNoCenter, (long)time(0), playerChips, 100, outfile);

	SimulateGame("nocenter-tilted", 9, chipDistributionNoCenter, (long)time(0), playerChipsTilted, 100, outfile);

	// game with greater chance of passing but no 'holding'
	int chipDistributionNoHold[] = { 1,1,2,2,3,3 };
	SimulateGame("nohold", 9, chipDistributionNoHold, (long)time(0), playerChips, 100, outfile);

	SimulateGame("nohold-tilted", 9, chipDistributionNoHold, (long)time(0), playerChipsTilted, 100, outfile);


	// close the file
	outfile.close();

	return 0;
}
