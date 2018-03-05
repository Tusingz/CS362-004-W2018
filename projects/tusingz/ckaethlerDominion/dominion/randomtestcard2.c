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

//Village test
int main(){
	srand(time(NULL));
	int numTests = randRange(1, 200);
	int count = 0;

	int fails;
	int failDraw;
	int failAction;
	int excessCards;
	int excessActions;
	int numVillageTotal;
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
			testGame.handCount[i] = randRange(1, 400);
			initialState.handCount[i] = testGame.handCount[i];
		}
		#if(NOISY_TEST == 1)
		printf("Test player %d playing a village starting hand size %d \n\n", player+1, initialState.handCount[player]);
		#endif
		int numVillage;
		numVillage = randRange(1, 10);
		int play;
		for (play = 0; play < numVillage; ++play)
		{
			cardEffect(village, 0, 0, 0, &testGame, 0, &coin_bonus);
		}
		

		#if(NOISY_TEST == 1)
		printf("Players hand size %d = %d(expected hand size) \n\n", testGame.handCount[player], (initialState.handCount[player] + (numVillage*2)));
		printf("Num Villages played: %d \n", numVillage);
		#endif

		if(testGame.handCount[player] != (initialState.handCount[player] + (numVillage*2)))
		{
			fails++;
			failDraw++;
			excessCards = testGame.handCount[player] - ((initialState.handCount[player] + (numVillage*2)));
		}

		if(testGame.numActions != (initialState.numActions + (numVillage*2)))
		{
			fails++;
			failAction++;
			excessActions = excessActions + testGame.numActions - ((initialState.numActions + (numVillage)));
		}

		numVillageTotal = numVillageTotal + numVillage;
		count++;
	}

	printf("Num Tests run: %d \n", numTests);
	printf("Village failed %d times \n", fails);
	printf("Total Villages played : %d \n", numVillageTotal);
	printf("Village didn't draw the right number of cards %d times\n", failDraw);
	printf("Total of cards drawn or underdrawn : %d \n", excessCards);
	printf("Village didn't add the right number of actions %d times\n", failAction);
	printf("Total of cards drawn or underdrawn : %d \n", excessActions);

	return check;
}