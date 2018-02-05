#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//ADVERTURER CARD TEST
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
	printf("Test player %d playing an adventurer starting hand size %d \n\n", player+1, 5);
	#endif

	check = initializeGame(numPlayer, card, seed, &testGame);
	int coin_bonus = 0;
	for (i = 0; i < numPlayer; ++i)
	{
		testGame.handCount[i] = 5;
	}

	cardEffect(adventurer, 0, 0, 0, &testGame, 0, &coin_bonus);

	#if(NOISY_TEST == 1)
	printf("Players hand size %d = %d(expected hand size) \n\n", testGame.handCount[player], 6);
	#endif

	#if(NOISY_TEST == 1)
	printf("testing if both cards drawn were treasures \n\n");
	#endif

	if((testGame.hand[player][5] == copper || testGame.hand[player][5] == silver || testGame.hand[player][5] == gold) && (testGame.hand[player][6] == copper || testGame.hand[player][6] == silver || testGame.hand[player][6] == gold))
		{

		}//code checks for the two new hand slots for being a copper/silver/gold
	else 
		{
			assert(0);
		}
	assert(testGame.handCount[player] == 6);

	printf("All tests passed!\n");

	return check;
}