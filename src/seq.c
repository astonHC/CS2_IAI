// COPYRIGHT (C) HARRY CLARK 2024
// CS2_IAI SEQUENCE INTEGRATION

// I HAVE LOST THE FUCKING PLOT, BY THE GRACE OF GOD I WILL MAKE IT TO THE 8TH
// I CANNOT WAIT FOR EXAMS TO BE OVER

// NESTED INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BIG ENDIAN BIT SHIFTERS FOR COMBINING LITERALS

#define         A           'A'
#define         B           'B'
#define         C           'C'
#define         E           'E'

#define         CHAR_AC         (A << 8 | C)
#define         CHAR_AB         (A << 8 | B)
#define         CHAR_BB         (B << 8 | B)
#define         MAX_LEN         100

typedef struct SEQ
{
    char* SEQUENCE;
    size_t LEN;

} SEQ;

SEQ* INIT_SEQ(char* INPUT)
{
    SEQ* S = (SEQ*)malloc(sizeof(SEQ));
    S->SEQUENCE = (char*)malloc((strlen(INPUT) + 1) * sizeof(char));

    S->LEN = strlen(INPUT);
    strcpy(S->SEQUENCE, INPUT);
    return S;
}

void GET_SEQUENCE(SEQ* S)
{
    char* RESULT = (char*)malloc((2 * S->LEN + 1));
    if(RESULT == NULL)
    {
        fprintf(stderr, "Memory allocation failed for transformation");
        return;
    }
    
    int NEW_LEN = 0;
    
    // FOR EVERY SUBSEQUENT VALUE IN THE SEQUENCE STRING
    // ITERATE THROUGH BASED ON THE PROVIDED LEN

    for(size_t INDEX = 0; INDEX < S->LEN; ++INDEX)
    {
        // BIT SHIFT ACCORDINGLY TO ASSERT A VALID PAIR
        if(INDEX + 1 < S->LEN)
        {
            int PAIR = (S->SEQUENCE[INDEX] << 8) | S->SEQUENCE[INDEX + 1];
            switch (PAIR)
            {
                case CHAR_AC:
                    RESULT[NEW_LEN++] = E;
                    INDEX++;
                    break;
                    
                case CHAR_AB:
                    RESULT[NEW_LEN++] = B;
                    RESULT[NEW_LEN++] = C;
                    INDEX++;
                    break;
                    
                case CHAR_BB:
                    RESULT[NEW_LEN++] = E;
                    INDEX++;
                    break;
                    
                default:
                    RESULT[NEW_LEN++] = S->SEQUENCE[INDEX];
                    break;
            }
        }
        else
        {
            RESULT[NEW_LEN++] = S->SEQUENCE[INDEX];
        }
    }
    
    RESULT[NEW_LEN] = '\0';
    free(S->SEQUENCE);
    S->SEQUENCE = RESULT;
    S->LEN = NEW_LEN;
}

void PRINT_SEQ(SEQ* S)
{
    printf("Current Sequence: %s\n", S->SEQUENCE);
}

int main(void)
{
    SEQ* S = INIT_SEQ("ABABAECCEC");
    char PREV[MAX_LEN];
    
    PRINT_SEQ(S);
    
    do
    {
        strcpy(PREV, S->SEQUENCE);
        GET_SEQUENCE(S);
        PRINT_SEQ(S);
    } while(strcmp(PREV, S->SEQUENCE) != 0 && S->LEN > 1);

    printf("Final Sequence: %s\n", S->SEQUENCE);
    
    free(S->SEQUENCE);
    free(S);
    return 0;
}