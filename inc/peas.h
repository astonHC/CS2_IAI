/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */

/* THIS FILE PERTAINS TOWARDS THE DECLARATION TO THE METHODS SURROUNDING THE PEAS SUBJECT */

#ifndef PEAS
#define PEAS

/* SYSTEM INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define         MAX_RINGS       50
#define         RING_BASE        1

typedef struct ENV
{
    int RINGS;
    int(*RING_AMOUNT)(struct ENV* ENV_BASE);
    void(*ADJUST_RINGS)(struct ENV* ENV_BASE, int VALUE);

} ENV;

void RING_AGENT(ENV* ENV_BASE);
int RING_MAIN(void);

#endif