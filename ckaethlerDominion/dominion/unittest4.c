/*****
** AUTHOR: CATHERINE KAETHLER
** CLASS: CS 362
** DUE DATE: FEBRUARY 4, 2018
** DESCRIPTION: TESTS THE FUNCTION supplyCount() IN DOMINION.C
*****/

/*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*****************************************************************************/
/*****
** DESCRIPTION: RECEIVES A GAME STATE AND CARD
** RETURNS A COUNT OF THE SUPPLY COUNT OF THAT CARD
*****/
int checkSupplyCount(int card, struct gameState *thisGame)
{
	int count;
	count = supplyCount(card, thisGame);
	return count;
}

/*****************************************************************************/

int main() 
{
	// INITIALIZE GAME VARIABLES
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	int testCount, thisCount, gameVal;
	int m, i;
	int j = 0;

	// FIXED TESTS
	printf("TESTING supplyCount FUNCTION.\n");
	// VICTORY/CURSE CARD LOOP
	for (m = 0; m < treasure_map+1; m++)
	{
		//  PROVINCE CARDS LOOP
		for (i = 0; i <= 30; i++)
		{	
			// CLEAR GAMESTATE & INITIALIZE GAME
			memset(&G, 23, sizeof(struct gameState));
			gameVal = initializeGame(4, k, 1, &G);

			// SET SUPPLY CARDS TO ENTER BOTH SCENARIOS
			G.supplyCount[m] = i;

			// TEST AGAINST CODE
			thisCount = i;
			testCount = checkSupplyCount(m, &G);
			if (testCount != thisCount)
			{
				printf("TEST FAILED AT THIS POINT: ******************** \n");
				printf("CARD: %d\n", m);
				printf("SUPPLY COUNT SET TO: %d\n", thisCount);
				printf("SUPPLY COUNT RECEIVED: %d\n", testCount);
				j++;
			}
		}
	}
	if (j == 0)
	{
		printf("TEST WAS SUCCESSFUL. NO NOTED ERRORS. \n");
	}
	return 0;
}
/*****************************************************************************/