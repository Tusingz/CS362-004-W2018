#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//test draw card
int main(){
	int i, i2;
	int seed = 4;
	int numPlayer = 2;
	int check;
	int card[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState testGame;

	#if(NOISY_TEST == 1)
	printf("Test Drawing cards until max hand size \n\n");
	#endif

	check = initializeGame(numPlayer, card, seed, &testGame);

	for (i = 6; i < MAX_HAND; ++i)
	{
		for (i2 = 0; i2 < 2; ++i2)
		{
			drawCard(i2, &testGame);
			assert(testGame.handCount[i2] = i);
		}
	}

	printf("All tests passed!\n");
}