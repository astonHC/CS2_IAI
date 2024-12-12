/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */

/* THIS FILE PERTAINS TOWARDS THE DECLARATION TO THE METHODS SURROUNDING THE PEAS SUBJECT */

/* NESTED INCLUDES */

#include "peas.h"

static int GET_RINGS(struct ENV* ENV_BASE) { return ENV_BASE->RINGS; }
static void COLLECT_RINGS(struct ENV* ENV_BASE, int VALUE) { ENV_BASE->RINGS += VALUE; }

/* ACCESS THE CURRENT RINGS BEING COLLECTED */
/* IF THE RING COUNT IS LESS THAN THE MAX, INCREMENT WITH EACH ITERATION */

void RING_AGENT(ENV* ENV_BASE)
{
    int RING = ENV_BASE->RING_AMOUNT(ENV_BASE);
    
    if(RING < MAX_RINGS)
    {
        printf("Collecting Rings\n");
        ENV_BASE->ADJUST_RINGS(ENV_BASE, RING_BASE);
    }

    printf("Ring Target Achieved\n");
}

/* DEFINE THE BASE BY WHICH THESE METHODS ARE ACCESSED */
/* THIS WILL DEFINE THE RINGS BASED ON HOW MANY ARE CURRENTLY AVAILABLE */

int RING_MAIN(void)
{
    printf("HARRY CLARK - PEAS STUDY MATERIAL\n");

    int INDEX = 0;

    ENV ENV_BASE = 
    { 
        .RINGS = 0, .RING_AMOUNT = GET_RINGS,
        .ADJUST_RINGS = COLLECT_RINGS 
    };

    for(INDEX = 0; INDEX < MAX_RINGS; INDEX++)
    {
        RING_AGENT(&ENV_BASE);
        printf("Rings Collected: %d\n", ENV_BASE.RINGS);
    }

    return 0;
}
