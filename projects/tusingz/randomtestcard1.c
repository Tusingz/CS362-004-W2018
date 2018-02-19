#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
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
	int numSmithyTotal;
	int check;

	while(count < numTests)
	{
		int i;
		int seed = randRange(1, 40);
		int numPlayer = randRange(2, 200);
		int player = randRange(0, numPlayer-1);
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
		printf("Test player %d playing a smithy starting hand size %d \n\n", player+1, initialState.handCount[player]);
		#endif


		int numSmithy;
		numSmithy = randRange(1, 10);
		int play;
		for (play = 0; play < numSmithy; ++play)
		{
			cardEffect(smithy, 0, 0, 0, &testGame, 0, &coin_bonus);
		}
		

		#if(NOISY_TEST == 1)
		printf("Players hand size %d = %d(expected hand size) \n\n", testGame.handCount[player], (initialState.handCount[player] + (numSmithy*2)));
		printf("Num Smithies played: %d \n", numSmithy);
		#endif

		if(testGame.handCount[player] != (initialState.handCount[player] + (numSmithy*2)))
		{
			fails++;
			failDraw++;
			excessCards = excessCards + testGame.handCount[player] - ((initialState.handCount[player] + (numSmithy*2)));
		}

		numSmithyTotal = numSmithyTotal + numSmithy;
		count++;
	}

	printf("Num Tests run: %d \n", numTests);
	printf("Smithy failed %d times \n", fails);
	printf("Smithy didn't draw the right number of cards %d times", failDraw);
	printf("Total Smithies played : %d \n", numSmithyTotal);
	printf("Total of cards drawn or underdrawn : %d \n", excessCards);

	return check;
}
