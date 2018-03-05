#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//Village test
int main(){
	int i;
	int seed = 4;
	int numPlayer = 2;
	int player = 0;
	int check;
	int card[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState testGame;

	#if(NOISY_TEST == 1)
	printf("Test player %d playing a village starting hand size %d \n\n", player+1, testGame.handCount[player]);
	#endif

	#if(NOISY_TEST == 1)
	printf("Test player %d playing a village with current action count %d \n\n", player+1, testGame.numActions);
	#endif

	check = initializeGame(numPlayer, card, seed, &testGame);
	int coin_bonus = 0;
	for (i = 0; i < numPlayer; ++i)
	{
		testGame.handCount[i] = 5;
	}

	cardEffect(village, 0, 0, 0, &testGame, 0, &coin_bonus); //play action

	#if(NOISY_TEST == 1)
	printf("Players hand size %d = %d(expected hand size) \n\n", testGame.handCount[player], 5);
	#endif

	#if(NOISY_TEST == 1)
	printf("Players action count %d = %d(expected action count) \n\n", testGame.numActions, 2);
	#endif

	assert(testGame.handCount[player] == 5);
	assert(testGame.numActions == 2);

	printf("All tests passed!\n");

	return check;
}