/*****
** AUTHOR: CATHERINE KAETHLER
** CLASS: CS 362
** DUE DATE: FEBRUARY 4, 2018
** DESCRIPTION: TESTS THE FUNCTION numHandCards() IN DOMINION.C
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
** DESCRIPTION: RECEIVES A GAME STATE
** RETURNS A COUNT OF THE CURRENT PLAYER'S HAND
*****/
int checkNumHandCard(struct gameState *thisGame)
{
	int count;
	count = numHandCards(thisGame);
	return count;
}

/*****************************************************************************/

int main() 
{
	// INITIALIZE GAME VARIABLES
	struct gameState G;
	int k[10] = {adventurer, smithy, village, council_room, feast, embargo,
				gardens, minion, mine, tribute};
	int numPlayers = 4;
	int player, thisCount, gameVal;
	int j = 0;

	// FIXED TESTS
	printf("TESTING numHandCards FUNCTION.\n");
	for (player = 0; player < 5; player++)
	{
		for (thisCount = 0; thisCount <= 5; thisCount++)
		{
			// CLEAR GAMESTATE & INITIALIZE GAME
			memset(&G, 23, sizeof(struct gameState));
			gameVal = initializeGame(numPlayers, k, 1, &G);

			// SET CARD VALUES
			G.handCount[player] = thisCount;
			G.whoseTurn = player;
			// TEST VALUES
			int testCount;
			testCount = checkNumHandCard(&G);

			if (thisCount != testCount)
			{
				printf("TEST FAILURE AT: *********** \n");
				printf("PLAYER: %d \n", player);
				printf("HAND COUNT: %d \n", thisCount);
				printf("VALUE RETURNED: %d \n", testCount);
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