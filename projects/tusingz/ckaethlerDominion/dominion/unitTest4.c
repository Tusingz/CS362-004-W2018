#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//test numHandCards
int main(){


	int lp;
	int seed = 4;
	int numPlayer = 2;
	int check;
	int card[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState testGame;
	check = initializeGame(numPlayer, card, seed, &testGame);

	#if(NOISY_TEST == 1)
	printf("Tests that the returned number of cards is correct \n\n");
	#endif

	for (lp = 0; lp < MAX_HAND; ++lp)
	{
		testGame.handCount[whoseTurn(&testGame)] = lp;
		assert(numHandCards(&testGame) == lp);
	}
	
	printf("All tests passed!\n");

}