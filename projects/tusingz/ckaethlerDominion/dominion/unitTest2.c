#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//test discard card
int main(){


	int i,i2,lp;
	int seed = 4;
	int numPlayer = 2;
	int check;
	int card[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState testGame;
	check = initializeGame(numPlayer, card, seed, &testGame);

	#if(NOISY_TEST == 1)
	printf("Test discarding down to no hand size for multiple players \n\n");
	#endif

	for (lp = 0; lp < 2; ++lp)
	{
		for (i = 5; i > 0; --i)
		{
			discardCard(i, lp, &testGame, 0);
			assert(testGame.handCount[lp] == i);
		}
	}
	
	printf("All tests passed!\n");

}