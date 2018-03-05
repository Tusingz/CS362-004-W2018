/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

/*****************************************************************************/
int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    
    // ARRAYS OF ALL COPPERS, SILVER, AND GOLD
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    // BEGIN TEST
    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                #if (NOISY_TEST == 1)
                    printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                #endif
                
                // CLEAR GAMESTATE, INITIALIZE NEW GAME, SET # HAND CARDS
                memset(&G, 23, sizeof(struct gameState));
                r = initializeGame(numPlayer, k, seed, &G);
                G.handCount[p] = handCount;
                
                // SET ALL CARDS TO COPPER
                memcpy(G.hand[p], coppers, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
                
                // CHECK IF NUMBER OF COINS IS CORRECT
                #if (NOISY_TEST == 1)
                    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
                #endif
                assert(G.coins == handCount * 1 + bonus);

                // SET ALL CARDS TO SILVER
                memcpy(G.hand[p], silvers, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
                
                // CHECK IF NUMBER OF COINS IS CORRECT
                #if (NOISY_TEST == 1)
                    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
                #endif
                assert(G.coins == handCount * 2 + bonus);

                // SET ALL CARDS TO GOLD
                memcpy(G.hand[p], golds, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
                
                // CHECK IF NUMBER OF COINS IS CORRECT
                #if (NOISY_TEST == 1)
                    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
                #endif
                assert(G.coins == handCount * 3 + bonus);
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
