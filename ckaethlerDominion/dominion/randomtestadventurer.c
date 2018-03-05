/*****
** AUTHOR: CATHERINE KAETHLER
** CLASS: CS 362
** DUE DATE: FEBRUARY 4, 2018
** DESCRIPTION: TESTS THE CARD ADVENTURER IN DOMINION.C
*****/

/*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "ADVENTURER"

/*****************************************************************************/

int main() 
{
	int m;
	for (m = 0; m < 10000; m++)
	{
		int x, thisCount;
		int treasureCount = 0;
		int seed = rand() % 10000 + 1;
		int numPlayers = rand() % 4 + 1;
		int thisPlayer = rand() % 5;

		while (thisPlayer >= numPlayers)
		{
			thisPlayer = rand() % 5;
		}

		int otherPlayer = rand() % 5;
		if(numPlayers > 1)
		{
			while ((thisPlayer == otherPlayer) || (otherPlayer >= numPlayers))
			{
				otherPlayer = rand() % 5;
			}
		}
		else
		{
			thisPlayer = 0;
		}

		// VARIABLES OUTLINED FOR ADVENTURER GAMEPLAY
	    int newCards = 2;
	    int newActions = 0;
	    int newBuys = 0;
	    int discard = 0;
	    int xtraCoins = 0;
	    int shuffledCards = 0;

	    // VARIABLES FOR GAMEPLAY
	    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
		struct gameState G, testG;
		int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
				sea_hag, tribute, smithy, council_room};

		// TEST VARIABLE DECLARATIONS
		int errors = 0;
		int testHand, thisHand, testDeck, thisDeck, testCoin, thisCoin;
		int i, thisAction, testAction, thisSupply, testSupply;
		int thisBuy, testBuy;
		int j = 0;

		// INITIALIZE GAME STATE AND GET DISCARD/TREASURE CARD COUNT
		initializeGame(numPlayers, k, seed, &G);
		thisCount = G.deckCount[thisPlayer];
		while((treasureCount <= 2) || (thisCount != 0))
		{
			if((G.deck[thisPlayer][thisCount] == gold) 
			|| (G.deck[thisPlayer][thisCount] == silver)
			|| (G.deck[thisPlayer][thisCount] == copper))
			{
				treasureCount++;
			}
			else
			{
				discard++;
			}
			thisCount--;
		}	

		printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
		printf("\n---- RANDOM VARIABLES USING ----\n");
		printf("Seed is: %d\n", seed);
		printf("The number of players is: %d\n", numPlayers);
		printf("This player's number is: %d\n", thisPlayer);
		printf("The other player's number is: %d\n", otherPlayer);

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		// TEST: COMPARES HAND COUNT BEFORE AND AFTER ADVENTURER CARD USED-------
		int discardDeck = G.discardCount[thisPlayer] + discard;
		int testDiscardDeck = testG.discardCount[thisPlayer];
		printf("\n---- TESTING DISCARD DECK COUNT ----\n");
		if (discardDeck != testDiscardDeck)			
		{
			printf("FAILED DISCARD COUNT TEST:\n");
			printf("discard count = %d, expected = %d\n", discardDeck, testDiscardDeck);
			errors++;
		}
		else
		{
			printf("SUCCESS: DISCARD COUNT TEST PASSED!\n");	
		}

		// TEST: COMPARES HAND COUNT BEFORE AND AFTER ADVENTURER CARD USED-------
		printf("\n---- TESTING HAND COUNT ----\n");
		if (discardDeck != testHand)
		{
			printf("FAILED HAND COUNT TEST:\n");
			printf("hand count = %d, expected = %d\n", testHand, thisHand);
			errors++;
		}
		else
		{
			printf("SUCCESS: HAND COUNT TEST PASSED!\n");	
		}

		// TEST: CHECKS TO SEE THAT ONLY MONETARY CARDS WERE ADDED-------
		printf("\n---- TESTING DRAWN TREASURE CARDS ----\n");
		int thisCard;
		for (x = 0; x < 2; x++)
		{
			thisCard = testG.hand[thisPlayer][testG.handCount[thisPlayer] - x];
			if ((thisCard != copper) || (thisCard != gold) || (thisCard != silver))
			{
				printf("FAILED DRAWN TREASURE TEST:\n");
				printf("number of card drawn = %d, card number = %d\n", x, thisCard);
				errors++;
			}
			else
			{
				printf("SUCCESS: DRAWN TREASURE TEST PASSED!\n");	
			}
		}

		// TEST: COMPARES DECK COUNT BEFORE AND AFTER ADVENTURE CARD USED----------
		thisDeck = G.deckCount[thisPlayer] - newCards + shuffledCards - discard;
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

		// TEST: COMPARES BUY COUNT BEFORE AND AFTER ADVENTURER CARD USED--------
		thisBuy = G.numBuys + newBuys;
		testBuy = testG.numBuys;
		printf("\n---- TESTING BUY COUNT ----\n");
		if (thisBuy != testBuy)
		{
			printf("FAILED BUY COUNT TEST:\n");
			printf("buy count = %d, expected = %d\n", testBuy, thisBuy);
			errors++;
		}
		else
		{
			printf("SUCCESS: BUY COUNT TEST PASSED!\n");	
		}

		// TEST: COMPARES ACTION COUNT BEFORE AND AFTER ADVENTURER CARD USED-----
		thisAction = G.numActions + newActions;
		testAction = testG.numActions;
		printf("\n---- TESTING ACTION COUNT ----\n");
		if (thisAction != testAction)
		{
			printf("FAILED ACTION COUNT TEST:\n");
			printf("hand count = %d, expected = %d\n", testAction, thisAction);
			errors++;
		}
		else
		{
			printf("SUCCESS: ACTION COUNT TEST PASSED!\n");	
		}

		// TEST: COMPARES COIN COUNT BEFORE AND AFTER ADVENTURER CARD USED-------
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
				errors++;
			}
		}
		printf(" KINGDOM CARD TEST COMPLETE WITH %d ERRORS \n", j);
		printf("\nNUMBER OF ERRORS FOUND: %d \n", errors);
		printf("\n >>>>> %s TEST COMPLETE <<<<<\n", TESTCARD);
	}
	// END TESTS---------------------------------------------------------------
	printf("\n\nThe number of tests run was: %d\n\n", m);
	return 0;
}
/*****************************************************************************/
