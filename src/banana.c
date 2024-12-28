// COPYRIGHT (C) HARRY CLARK 2024
// CS2_IAI MAZE INTEGRATION

// I HAVE LOST THE FUCKING PLOT, BY THE GRACE OF GOD I WILL MAKE IT TO THE 8TH
// I CANNOT WAIT FOR EXAMS TO BE OVER

// NESTED INCLUDES

#include <stdio.h>
#include <stdlib.h>

typedef struct BOXES 
{
    int* NUM;       
    int BANANAS;    
    int INCREMENTER;

} BOXES;

BOXES* INIT_BOXES(int NUM) 
{
    BOXES* B = malloc(sizeof(BOXES));

    if (B == NULL) 
    {
        fprintf(stderr, "Memory Allocation failed for Boxes %p\n", (void*)B);
        exit(EXIT_FAILURE);
    }

    B->NUM = (int*)calloc(NUM, sizeof(int));

    B->BANANAS = 0;
    B->INCREMENTER = NUM;
    B->NUM[0] = 1;  
    return B;
}

void UNLOCK_BOXES(BOXES* B) 
{
    for (int I = 0; I < B->INCREMENTER - 1; ++I) 
    {
        if (B->NUM[I] == 1)
        {
            B->NUM[I + 1] = 1;  
        }
    }
    
    B->BANANAS = B->NUM[B->INCREMENTER - 1];
}

int main(void) 
{
    int AMOUNT = 6;  
    BOXES* B = INIT_BOXES(AMOUNT);

    UNLOCK_BOXES(B);

    printf("Banana Obtained: %d\n", B->BANANAS);
    return 0;
}