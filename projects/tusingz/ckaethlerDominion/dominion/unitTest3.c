#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//test whose turns
int main(){


	int lp;
	int seed = 4;
	int numPlayer = 10;
	int check;
	int card[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState testGame;
	check = initializeGame(numPlayer, card, seed, &testGame);

	#if(NOISY_TEST == 1)
	printf("tests to make sure the function returns the correct players turn \n\n");
	#endif

	for (lp = 0; lp < 10; ++lp)
	{
		testGame.whoseTurn = lp;
		assert(whoseTurn(&testGame) == lp);
	}
	
	printf("All tests passed!\n");

}