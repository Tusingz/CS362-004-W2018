/*****
** AUTHOR: CATHERINE KAETHLER
** CLASS: CS 362
** DUE DATE: FEBRUARY 4, 2018
** DESCRIPTION: TESTS THE FUNCTION fullDeckCount() IN DOMINION.C 
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
** DESCRIPTION: RECEIVES GAMESTATE STRUCT AND PLAYER 
** RETURNS COUNT OF CARDS IN HANDS
*****/
int checkDeckCount(int player, struct gameState *realGame)
{
	int count;
	count = fullDeckCount(player, 0, realGame);
	return count;
}

/*****************************************************************************/
int main() 
{
	// INITIALIZE GAME VARIABLES
	struct gameState G;
	int k[10] = {adventurer, smithy, village, council_room, feast, embargo,
				gardens, minion, mine, tribute};
	int numPlayers = 2;
	int player, deckCount, discardCount, handCount, gameVal;
	int j = 0;

	// FIXED TESTS
	printf("TESTING fullDeckCount FUNCTION.\n");
	for (player = 0; player < 2; player++)
	{
		for (deckCount = 0; deckCount < 5; deckCount++)
		{
			for (discardCount = 0; discardCount < 5; discardCount++)
			{
				for (handCount = 0; handCount < 5; handCount++)
				{
					// CLEAR GAMESTATE & INITIALIZE GAME
					memset(&G, 23, sizeof(struct gameState));
					gameVal = initializeGame(numPlayers, k, 1, &G);

					// SET CARD VALUES
					G.deckCount[player] = deckCount;
					memset(G.deck[player], 0, sizeof(int) * deckCount);
					G.discardCount[player] = discardCount;
					memset(G.discard[player], 0, sizeof(int) * discardCount);
					G.handCount[player] = handCount;
					memset(G.hand[player], 0, sizeof(int) * handCount);

					// TEST VALUES
					int thisCount = deckCount + discardCount + handCount;
					int testCount = checkDeckCount(player, &G);
					if (thisCount != testCount)
					{
						printf("TEST FAILURE AT:\n");
						printf("PLAYER: %d \n", player);
						printf("DECK COUNT: %d \n", deckCount);
						printf("HAND COUNT: %d \n", handCount);
						printf("DISCARD COUNT: %d \n", discardCount);
						j++;
					}
				}
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