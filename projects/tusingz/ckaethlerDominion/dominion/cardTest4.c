#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//SEA HAG TEST
int main(){
	int i;
	int seed = 4;
	int numPlayer = 10;
	int player = 0;
	int check;
	int card[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState testGame;

	#if(NOISY_TEST == 1)
	printf("Test player %d playing a sea_hag starting hand size %d \n\n", player+1, 5);
	#endif

	check = initializeGame(numPlayer, card, seed, &testGame);
	for (i = 0; i < numPlayer; ++i)
	{
		testGame.handCount[i] = 5;
	}

	int coin_bonus = 0;
	int handVar;
	handVar = 0;
	
	cardEffect(sea_hag, 0, 0, 0, &testGame, 0, &coin_bonus);

	for (i = 0; i < numPlayer; ++i)
	{
		#if(NOISY_TEST == 1)
		printf("player %d hand size %d \n\n", i, testGame.handCount[i]);
		#endif

		#if (handVar != 1)
			assert(testGame.handCount[i] == 4);
			
		#endif
	}
	assert(testGame.handCount[player] == 5);

	printf("All tests passed!\n");

	return check;
}