/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */
/* THIS FILE PERTAINS TOWARDS THE UTILITY AND FUNCTIONALITY OF THE NEURAL NETWORK */

/* COMPILE USING gcc --std=c99 nn.c -lm */

/* NESTED INCLUDES */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

static const float TARGET_OUTPUTS[4][4] = 
{
    {1.0f, 0.0f, 0.0f, 0.0f},  // MAMA
    {0.0f, 1.0f, 0.0f, 0.0f},  // PAPA
    {0.0f, 0.0f, 1.0f, 0.0f},  // DADA
    {0.0f, 0.0f, 0.0f, 1.0f}   // SPAGHETTI
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

float SIGMOID_DER(float VALUE)
{
    return VALUE * (1.0f - VALUE);
}

NEURAL* NEURAL_INIT(unsigned INPUT_SIZE, unsigned OUTPUT_SIZE)
{
    srand((unsigned int)time(NULL));
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
    NEURAL_BASE->BIASES = (float*)malloc(NEURAL_BASE->TOTAL_NEURONS * sizeof(float));

    for (unsigned i = 0; i < NEURAL_BASE->TOTAL_WEIGHTS; i++)
    {
        NEURAL_BASE->WEIGHTS[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    }

    return NEURAL_BASE;
}

void NEURAL_FORWARD(const char* INPUT_STRING)
{
    float* INPUT_VALUES = STRING_TO_FLOAT(INPUT_STRING, NEURAL_BASE->INPUTS);

    for (unsigned i = 0; i < NEURAL_BASE->OUTPUTS; i++)
    {
        float SUM = NEURAL_BASE->BIASES[i];
        
        for (unsigned j = 0; j < NEURAL_BASE->INPUTS; j++)
        {
            SUM += INPUT_VALUES[j] * NEURAL_BASE->WEIGHTS[i * NEURAL_BASE->INPUTS + j];
        }
        
        // LEVERAGE USING SIGMOID ACTIVATION FOR 
        // BETTER GRADIENT CONTROL FOR EXPONENTIAL NEURON GROWTH
        NEURAL_BASE->NEURON_OUTPUT[i] = 1.0f / (1.0f + expf(-SUM));
    }

    free(INPUT_VALUES);
}

// NOW DO THE SAME AGAINST BACKWARDS PROPAGATION
// THIS WILL PRESUPPOSE THE DERIVATIVE OF THE SIGMOID AGAINST THE NEURONS

void NEURAL_BACKWARD(const char* INPUT_STRING, const float* TARGET, float LEARNING_RATE)
{
    float* INPUT_VALUES = STRING_TO_FLOAT(INPUT_STRING, NEURAL_BASE->INPUTS);
    
    // CALCULATE OUTPUT ERRORS AND UPDATE WEIGHTS
    for (unsigned i = 0; i < NEURAL_BASE->OUTPUTS; i++)
    {
        float ERROR = TARGET[i] - NEURAL_BASE->NEURON_OUTPUT[i];
        float DELTA = ERROR * SIGMOID_DER(NEURAL_BASE->NEURON_OUTPUT[i]);
        
        // UPDATE BIAS
        NEURAL_BASE->BIASES[i] += LEARNING_RATE * DELTA;
        
        // UPDATE WEIGHTS
        for (unsigned j = 0; j < NEURAL_BASE->INPUTS; j++)
        {
            NEURAL_BASE->WEIGHTS[i * NEURAL_BASE->INPUTS + j] += LEARNING_RATE * DELTA * INPUT_VALUES[j];
        }
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

float CALCULATE_LOSS(const float* PREDICTED, const float* TARGET, unsigned SIZE)
{
    float LOSS = 0.0f;
    
    for (unsigned i = 0; i < SIZE; i++)
    {
        float DIFF = TARGET[i] - PREDICTED[i];
        LOSS += DIFF * DIFF;
    }
    
    return LOSS / 2.0f;
}

void NEURAL_TRAIN()
{
    printf("TRAINING NEURAL NETWORK...\n");
    
    for (unsigned EPOCH = 0; EPOCH < EPOCHS; EPOCH++)
    {
        float TOTAL_LOSS = 0.0f;
        
        // TRAIN ON ALL EXAMPLES
        for (unsigned EXAMPLE = 0; EXAMPLE < 4; EXAMPLE++)
        {
            // FORWARD PASS
            NEURAL_FORWARD(EXAMPLES[EXAMPLE]);
            
            // CALCULATE LOSS
            TOTAL_LOSS += CALCULATE_LOSS(NEURAL_BASE->NEURON_OUTPUT, TARGET_OUTPUTS[EXAMPLE], NEURAL_BASE->OUTPUTS);
            
            // BACKWARD PASS
            NEURAL_BACKWARD(EXAMPLES[EXAMPLE], TARGET_OUTPUTS[EXAMPLE], LEARN_RATE);
        }
        
        // PRINT PROGRESS EVERY 100 EPOCHS
        if (EPOCH % 100 == 0)
        {
            printf("EPOCH %d - LOSS: %f\n", EPOCH, TOTAL_LOSS / 4.0f);
        }
    }
    
    printf("TRAINING COMPLETE!\n\n");
}

// PREDICT THE OUTPUT BASED ON THE PRESUPPOSED
// AMOUNT OF OUTPUTS PROVIDED AS NEURONS

// LEVERAGE FORWARD PROPAGATION TO BE ABLE TO COMPARE FIRST AND LAST ELEMENTS

void NEURAL_PREDICT(const char* INPUT_STRING)
{
    NEURAL_FORWARD(INPUT_STRING);
    
    printf("PREDICTION FOR '%s':\n", INPUT_STRING);
    
    // FIND THE OUTPUT WITH HIGHEST VALUE
    unsigned BEST_MATCH = 0;
    float HIGHEST_CONFIDENCE = NEURAL_BASE->NEURON_OUTPUT[0];
    
    for (unsigned i = 0; i < NEURAL_BASE->OUTPUTS; i++)
    {
        printf("  %s: %.4f\n", EXAMPLES[i], NEURAL_BASE->NEURON_OUTPUT[i]);
        
        if (NEURAL_BASE->NEURON_OUTPUT[i] > HIGHEST_CONFIDENCE)
        {
            HIGHEST_CONFIDENCE = NEURAL_BASE->NEURON_OUTPUT[i];
            BEST_MATCH = i;
        }
    }
    
    printf("  BEST MATCH: %s (%.4f CONFIDENCE)\n\n", EXAMPLES[BEST_MATCH], HIGHEST_CONFIDENCE);
}

int main(void)
{
    unsigned INPUT_SIZE = MAX_STRING;
    unsigned OUTPUT_SIZE = 4;

    NEURAL* NETWORK = NEURAL_INIT(INPUT_SIZE, OUTPUT_SIZE);
    
    printf("INITIAL PREDICTIONS (BEFORE TRAINING):\n");
    for (unsigned i = 0; i < 4; i++)
    {
        NEURAL_PREDICT(EXAMPLES[i]);
    }
    
    // TRAIN THE NETWORK
    NEURAL_TRAIN();
    
    printf("FINAL PREDICTIONS (AFTER TRAINING):\n");
    for (unsigned i = 0; i < 4; i++)
    {
        NEURAL_PREDICT(EXAMPLES[i]);
    }
    
    // TEST WITH A NEW INPUT
    printf("TESTING WITH NEW INPUT:\n");
    NEURAL_PREDICT("MAMA");
    NEURAL_PREDICT("TEST");

    NEURAL_FREE();
    return 0;
}
