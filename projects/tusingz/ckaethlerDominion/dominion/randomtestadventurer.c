#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int randRange(int min, int max)
{
	int x;
	x = rand() % (max + 1 - min) + min;
	return x;
}

//smithy test
int main(){
	srand(time(NULL));
	int numTests = randRange(1, 200);
	int count = 0;

	int fails;
	int failDraw;
	int excessCards;
	int notTreasure;
	int numAdventurerTotal;
	int check;

	while(count < numTests)
	{
		int i;
		int seed = randRange(1, 40);
		int numPlayer = randRange(2, 200);
		int player = randRange(1, numPlayer);
		
		int card[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
		struct gameState testGame;
		struct gameState initialState;

		check = initializeGame(numPlayer, card, seed, &testGame);
		check = initializeGame(numPlayer, card, seed, &initialState);
		int coin_bonus = 0;
		for (i = 0; i < numPlayer; ++i)
		{
			testGame.handCount[i] = randRange(1, 200);
			initialState.handCount[i] = testGame.handCount[i];
		}

		#if(NOISY_TEST == 1)
		printf("Test player %d playing a adventurer starting hand size %d \n\n", player+1, initialState.handCount[player]);
		#endif


		int numAdventurer;
		numAdventurer = randRange(1, 10);
		int play;
		for (play = 0; play < numAdventurer; ++play)
		{
			cardEffect(adventurer, 0, 0, 0, &testGame, 0, &coin_bonus);
		}
		

		#if(NOISY_TEST == 1)
		printf("Players hand size %d = %d(expected hand size) \n\n", testGame.handCount[player], (initialState.handCount[player] + (numAdventurer*2)));
		printf("Num Adventurers played: %d \n", numAdventurer);
		#endif

		if(testGame.handCount[player] != (initialState.handCount[player] + (numAdventurer*2)))
		{
			fails++;
			failDraw++;
			excessCards = excessCards + testGame.handCount[player] - ((initialState.handCount[player] + (numAdventurer*2)));
		}

		if((testGame.hand[player][testGame.handCount[player]] == copper || testGame.hand[player][testGame.handCount[player]] == silver || testGame.hand[player][testGame.handCount[player]] == gold) && (testGame.hand[player][(testGame.handCount[player] + 1)] == copper || testGame.hand[player][(testGame.handCount[player] + 1)] == silver || testGame.hand[player][(testGame.handCount[player] + 1)] == gold))
		{
			
		}//code checks for the two new hand slots for being a copper/silver/gold
		else 
		{
			fails++;
			notTreasure++;
		}

		if(testGame.handCount[player] != (initialState.handCount[player] + (numAdventurer)))
		{
			fails++;
			failDraw++;
			excessCards = testGame.handCount[player] - ((initialState.handCount[player] + (numAdventurer)));
		}

			numAdventurerTotal = numAdventurerTotal + numAdventurer;
			count++;
	}

	printf("Num Tests run: %d \n", numTests);
	printf("Adventurer failed %d times \n", fails);
	printf("Adventurer didn't draw the right number of cards %d times\n", failDraw);
	printf("Total Adventurers played : %d \n", numAdventurerTotal);
	printf("Number of times adventurer didn't draw treasure : %d \n", notTreasure);
	printf("Total of cards drawn or underdrawn : %d \n", excessCards);

	return check;
}
