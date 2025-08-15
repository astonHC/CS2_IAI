/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */
/* THIS FILE PERTAINS TOWARDS THE UTILITY AND FUNCTIONALITY OF THE NEURAL NETWORK */

/* COMPILE USING gcc nn.c -o main -lm */

/* NESTED INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define         MAX_IO              50
#define         MAX_STRING          20
#define         LEARN_RATE          0.1f
#define         EPOCHS              1000

typedef struct NEURAL
{
    float* WEIGHTS;
    float* NEURON_OUTPUT;
    float* BIASES;
    unsigned TOTAL_NEURONS;
    unsigned TOTAL_WEIGHTS;
    unsigned INPUTS;
    unsigned OUTPUTS;
    
} NEURAL;

static NEURAL* NEURAL_BASE;

static const char* EXAMPLES[4] =
{
    "MAMA",
    "PAPA",
    "DADA",
    "SPAGHETTI"
};

// GLIBC DOESNT HAVE THE FUNCTIONALITY I NEED FOR THIS
// I WANT TO BE ABLE TO ACTUALLY DEFINE TRHE LENGTH AND ASSERT AS SUCH

// THIS WILL ALLOW ME TO RETURN A PROPER VALUE AS OPPOSED TO A CHAR WHICH WILL NULL

float CHAR_TO_FLOAT(char CHARACTER)
{
    return (float)(CHARACTER - 'A') / 26.0f;
}

float* STRING_TO_FLOAT(const char* STRING, int LENGTH)
{
    float* RESULT = malloc(LENGTH * sizeof(float));
    
    for (int i = 0; i < LENGTH; i++)
    {
        RESULT[i] = STRING[i] ? CHAR_TO_FLOAT(STRING[i]) : 0.0f;
    }
    
    return RESULT;
}

NEURAL* NEURAL_INIT(unsigned INPUT_SIZE, unsigned OUTPUT_SIZE)
{
    NEURAL_BASE = (NEURAL*)malloc(sizeof(NEURAL));
    
    if(NEURAL_BASE == NULL)
    {
        fprintf(stderr, "Memory Allocation failed for Neural Network %p", (void*)NEURAL_BASE);    
        exit(EXIT_FAILURE);
    }

    NEURAL_BASE->INPUTS = INPUT_SIZE;
    NEURAL_BASE->OUTPUTS = OUTPUT_SIZE;
    NEURAL_BASE->TOTAL_NEURONS = OUTPUT_SIZE;
    NEURAL_BASE->TOTAL_WEIGHTS = INPUT_SIZE * OUTPUT_SIZE;

    NEURAL_BASE->WEIGHTS = (float*)malloc(NEURAL_BASE->TOTAL_WEIGHTS * sizeof(float));
    NEURAL_BASE->NEURON_OUTPUT = (float*)malloc(NEURAL_BASE->TOTAL_NEURONS * sizeof(float));

    for (unsigned i = 0; i < NEURAL_BASE->TOTAL_WEIGHTS; i++)
    {
        NEURAL_BASE->WEIGHTS[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    }

    return NEURAL_BASE;
}

void NEURAL_FORWARD(const char* INPUT_STRING)
{
    if (NEURAL_BASE == NULL)
    {
        fprintf(stderr, "Neural Network not initialized\n");
        exit(EXIT_FAILURE);
    }

    float* INPUT_VALUES = STRING_TO_FLOAT(INPUT_STRING, NEURAL_BASE->INPUTS);

    for (unsigned i = 0; i < NEURAL_BASE->OUTPUTS; i++)
    {
        float SUM = 0.0f;
        
        for (unsigned j = 0; j < NEURAL_BASE->INPUTS; j++)
        {
            SUM += INPUT_VALUES[j] * NEURAL_BASE->WEIGHTS[i * NEURAL_BASE->INPUTS + j];
        }
        
        NEURAL_BASE->NEURON_OUTPUT[i] = tanh(SUM);
    }

    free(INPUT_VALUES);
}

void NEURAL_FREE()
{
    if (NEURAL_BASE != NULL)
    {
        free(NEURAL_BASE->WEIGHTS);
        free(NEURAL_BASE->NEURON_OUTPUT);
        free(NEURAL_BASE);
        NEURAL_BASE = NULL;
    }
}

int main(void)
{
    unsigned INPUT_SIZE = MAX_STRING;
    unsigned OUTPUT_SIZE = 4;

    NEURAL* NETWORK = NEURAL_INIT(INPUT_SIZE, OUTPUT_SIZE);
    
    printf("PROCESSING -> %s\n", EXAMPLES[0]);
    NEURAL_FORWARD(EXAMPLES[0]);

    printf("Neural Network Outputs:\n");
    
    for (unsigned i = 0; i < NEURAL_BASE->OUTPUTS; i++)
    {
        printf("Corresponding Value in Array for: %s: %d\n", EXAMPLES[0], i);
        printf("Output %d: %f\n", i + 1, NEURAL_BASE->NEURON_OUTPUT[i]);
    }

    NEURAL_FREE();
    return 0;
}
