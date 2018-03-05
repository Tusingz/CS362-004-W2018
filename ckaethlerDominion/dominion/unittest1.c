/*****
** AUTHOR: CATHERINE KAETHLER
** CLASS: CS 362
** DUE DATE: FEBRUARY 4, 2018
** DESCRIPTION: TESTS THE FUNCTION isGameOver() IN DOMINION.C 
*****/

/*****************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define MAX_PROVINCE 8

/*****************************************************************************/
/*****
** DESCRIPTION: RECEIVES GAMESTATE STRUCT AND RETURNS TRUE FUNCTION
** fullDeckCount() RETURNS CORRECT CARD COUNT
*****/
int checkGameOver(struct gameState *thisGame)
{
	int status;
	status = isGameOver(thisGame);
	return status;
}

/*****************************************************************************/
int main() 
{
	// INITIALIZE GAME VARIABLES
	struct gameState G;
	int k[10] = {adventurer, smithy, village, council_room, feast, embargo,
				gardens, minion, mine, tribute};
	int numPlayers = 2;
	int gameVal, thisGame, testGame;
	int f = 0;
	int i, j, m;

	// FIXED TESTS
	printf("TESTING isGameOver FUNCTION.\n");
	// VICTORY/CURSE CARD LOOP
	for (m = 0; m < 8; m++)
	{
		//  PROVINCE CARDS LOOP
		for (i = 0; i <= 8; i++)
		{	
			// CLEAR GAMESTATE & INITIALIZE GAME
			memset(&G, 23, sizeof(struct gameState));
			gameVal = initializeGame(numPlayers, k, 1, &G);

			// SET SUPPLY CARDS TO ENTER BOTH SCENARIOS
			G.supplyCount[0] = m; // curse
			G.supplyCount[1] = m; // estate
			G.supplyCount[2] = m; // duchy
			G.supplyCount[3] = i; // province
			for (j = 4; j < 11; j++) // copper to gardens
			{
				G.supplyCount[j] = 1;
			}

			// PROVINCE OR THREE SUPPLY STACKS AT 0 ENDS GAME
			if ((G.supplyCount[3] == 0) || (m == 0))
			{
				thisGame = 1;
			}
			else
			{
				thisGame = 0;
			}

			// TEST AGAINST CODE
			testGame = checkGameOver(&G);
			if (testGame != thisGame)
			{
				printf("TEST FAILED AT THIS POINT: ******************** \n");
				printf("NUMBER OF PROVINCE CARDS: %d\n", G.supplyCount[3]);
				printf("NUMBER IN STACK OF THREE TEST SUPPLIES: %d\n", G.supplyCount[0]);
				printf("NUMBER IN REST OF SUPPLY STACKS: %d\n", G.supplyCount[10]);
				f++;
			}
		}
	}
	if (f == 0)
	{
		printf("TEST WAS SUCCESSFUL. NO NOTED ERRORS. \n");
	}
	return 0;
}
/*****************************************************************************/