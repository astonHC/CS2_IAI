/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */

/*==========================================================================================*/
                                    /* EXERCISE 1 */
/*==========================================================================================*/

/* CONSIDER THE PROBLEM FACED BY AN INFANT LEARNING TO 
SPEAK AND UNDERSTAND A LANGUAGE. EXPLAIN HOW THIS PROCESS FITS INTO THE GENERAL LEARNING MODEL. 
DESCRIBE THE PERCEPTS AND ACTIONS OF THE INFANT, AND THE TYPES OF LEARNING THE INFANT MUST DO. 
DESCRIBE THE SUBFUNCTIONS THE INFANT IS TRYING TO LEARN IN TERMS OF INPUTS AND OUTPUTS, AND AVAILABLE EXAMPLE DATA. */

/* NESTED INCLUDES */

#include <stdio.h>
#include <stdlib.h>

#define         MAX_INPUT           50

typedef struct LEARN
{
    char INPUT[MAX_INPUT];
    char OUTPUT[MAX_INPUT];
    int COUNT;

} LEARN;

static LEARN* LEARN_BASE;

// THIS INVOKES THE GENERAL LEARNING MODEL BY PROVIDING PERCEPTS FOR INPUT AND OUTPUT

static const LEARN EXAMPLES[4] = 
{
    {"MAMA", "MAMA"},
    {"PAPA", "PAPA"},
    {"DADA", "DADA"},
    {"SPAGHETTI", "SPAGHETTI"}
};

// ITERATES THROUGH THE ARRAY OF OPTIONS PROVIDED AS PER THE INPUT AND OUTPUT
// DETERMINES WHAT THE FIRST CHAR OF EACH SECTION IS

void LEARN_LANG(int COUNT)
{
    for (int i = 0; i < COUNT; i++)
    {
        printf("Input %s -> Learned Output: %s\n", EXAMPLES[i].INPUT, EXAMPLES[i].OUTPUT);
    }
}

int main(void)
{   
    LEARN_BASE = malloc(sizeof(LEARN));

    LEARN_BASE->COUNT = sizeof(EXAMPLES) / sizeof(EXAMPLES[0]);
    LEARN_LANG(LEARN_BASE->COUNT);

    free(LEARN_BASE);

    return 0;
}