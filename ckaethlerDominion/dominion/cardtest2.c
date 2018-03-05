/*****
** AUTHOR: CATHERINE KAETHLER
** CLASS: CS 362
** DUE DATE: FEBRUARY 4, 2018
** DESCRIPTION: TESTS THE CARD SMITHY IN DOMINION.C
*****/

/*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/*****************************************************************************/

#define TESTCARD "SMITHY"

/*****************************************************************************/

int main() 
{
	// VARIABLE DECLARATIONS FOR SMITHY ACTIONS & GAME PLAY & TESTS
    int newCards = 3;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;

    // VARIABLE DECLARATIONS FOR GAMEPLAY AND TESTING
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int errors = 0;
	int testHand, thisHand, testDeck, thisDeck, testCoin, thisCoin;
	int i, thisSupply, testSupply;
	int j = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// COPY GAME STATE TO TEST CASE & RUN SMITHY CARD
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	// TEST: COMPARES HAND COUNT BEFORE AND AFTER SMITHY CARD USED-------------
	thisHand = G.handCount[thisPlayer] + newCards - discarded;
	testHand = testG.handCount[thisPlayer];
	printf("\n---- TESTING HAND COUNT ----\n");
	if (thisHand != testHand)
	{
		printf("FAILED HAND COUNT TEST:\n");
		printf("hand count = %d, expected = %d\n", testHand, thisHand);
		errors++;
	}
	else
	{
		printf("SUCCESS: HAND COUNT TEST PASSED!\n");	
	}

	// TEST: COMPARES DECK COUNT BEFORE AND AFTER SMITHY CARD USED-------------
	thisDeck = G.deckCount[thisPlayer] - newCards + shuffledCards;
	testDeck = testG.deckCount[thisPlayer];
	printf("\n---- TESTING DECK COUNT ----\n");
	if (testDeck != thisDeck)
	{
		printf("FAILED DECK COUNT TEST:\n");
		printf("deck count = %d, expected = %d\n", testDeck, thisDeck);
		errors++;
	}
	else
	{
		printf("SUCCESS: DECK COUNT TEST PASSED!\n");
	}

	// TEST: COMPARES COIN COUNT BEFORE AND AFTER SMITHY CARD USED-------------
	thisCoin = G.coins + xtraCoins;
	testCoin = testG.coins;
	printf("\n---- TESTING COIN COUNT ----\n");
	if (thisCoin != testCoin)
	{
		printf("FAILED COIN COUNT TEST:\n");
		printf("coins = %d, expected = %d\n", testCoin, thisCoin);
		errors++;
	}
	else
	{
		printf("SUCCESS: COIN COUNT TEST PASSED!\n");
	}

	// TEST: OTHER PLAYER'S INFORMATION----------------------------------------
	int otherPlayer;
	otherPlayer = thisPlayer + 1;
	thisHand = G.handCount[otherPlayer];
	testHand = testG.handCount[otherPlayer];
	thisDeck = G.deckCount[otherPlayer];
	testDeck = testG.deckCount[otherPlayer];
	printf("\n---- TESTING PLAYER %d DECK AND HAND COUNT ----\n", otherPlayer);
	if ((testDeck != thisDeck) || (thisHand != testHand))
	{
		printf("FAILED PLAYER COUNT TEST: \n");
		printf("deck count = %d, expected = %d\n", testDeck, thisDeck);
		printf("hand count = %d, expected = %d\n", testHand, thisHand);
		errors++;
	}
	else
	{
		printf("SUCCESS: OTHER PLAYER'S COUNT TEST PASSED!\n");
	}

	// TEST: VICTORY CARD AND KINGDOM CARD-------------------------------------
	printf("\n---- TESTING VICTORY AND KINGDOM CARD PILES ----\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		thisSupply = G.supplyCount[i];
		testSupply = testG.supplyCount[i];
		if (thisSupply != testSupply)
		{
			printf("FAILED SUPPLY COUNT TEST AT: \n");
			printf("SUPPLY DECK: %d", i);
			printf("deck count = %d, expected = %d\n", testSupply, thisSupply);
			j++;
		}
	}
	printf(" KINGDOM CARD TEST COMPLETE WITH %d ERRORS \n", j);

	// END TESTS---------------------------------------------------------------
	printf("\nNUMBER OF ERRORS FOUND: %d \n", errors);
	printf("\n >>>>> %s TEST COMPLETE <<<<<\n", TESTCARD);
	return 0;
}
/*****************************************************************************/