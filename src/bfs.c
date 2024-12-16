/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING BFS */

/* NESTED INCLUDES */

#include "bfs.h"

// INITIALISE THE BFS STRUCTURE

BFS* INIT_BFS()
{
    BFS* BFS_BASE = malloc(sizeof(struct BFS));

    if(BFS_BASE == NULL)
    {
        perror("Memory allocation failed for BFS\n");
        exit(1);
    }

    memset(BFS_BASE->QUEUE, 0, sizeof(BFS_BASE->QUEUE));
    BFS_BASE->FRONT = NULL;
    BFS_BASE->REAR = NULL;

    return BFS_BASE;
}

void BFS_SEARCH(int ADJ[MAX_NUM][MAX_NUM], int VERTEX, int SRC)
{   
    BFS* B = INIT_BFS();
    int FRONT = 0, REAR = 0;

    int VISITED[MAX_NUM] = {0};

    // ENQUEUE THE SOURCE NODE
    // ENSURING THAT IT INCREASES IN SIZE FROM THE REAR

    B->QUEUE[REAR++] = SRC;
    VISITED[SRC] = 1;

    while(FRONT < REAR)
    {
        B->CURRENT = B->QUEUE[FRONT++];
        printf("Visited Node %d\n", B->CURRENT);

        for(int INDEX = 0; INDEX < VERTEX; INDEX++)
        {
            if(ADJ[B->CURRENT][INDEX] == 1 && !VISITED[INDEX])
            {
                B->QUEUE[REAR++] = INDEX;
                VISITED[INDEX] = 1;
            }
        }
    }

    printf("Traversal Complete\n");
    free(B);
}

// ADD THE NECESSARY VERTEX'S TO THE NODE GRAPH
// THIS WILL ALLOW FOR THE TRAVERSAL OF NODES FROM EACH RESPECTIVE VISIT

void ADD_VERTEX(int ADJ[MAX_NUM][MAX_NUM], int *VERTEX, int MAX_VERTEX, int CONNECTIONS[])
{
    if (*VERTEX >= MAX_VERTEX)
    {
        printf("Error: Maximum number of vertices reached.\n");
        return;
    }

    // ADD A NEW VERTEX

    int NEW_VERTEX = (*VERTEX)++;
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        ADJ[NEW_VERTEX][i] = 0;
        ADJ[i][NEW_VERTEX] = 0;
    }

    // DYNAMICALLY DETERMINE THE NUMBER OF CONNECTIONS

    int NUM_CONNECTIONS = 0;
    while (CONNECTIONS[NUM_CONNECTIONS] != 0)
    {

        // DETERMINE WHICH VERTEX NEEDS TO BE ADDED TO
        // THE CONCURRENT VERTEX 

        // CREATE AND ESTABLISH A NEW VERTEX
        // AND CONNECTION

        int CONNECT_TO = CONNECTIONS[NUM_CONNECTIONS];
        if (CONNECT_TO >= 0 && CONNECT_TO < *VERTEX)
        {
            ADJ[NEW_VERTEX][CONNECT_TO] = 1;
            ADJ[CONNECT_TO][NEW_VERTEX] = 1;
        }
        NUM_CONNECTIONS++;
    }

    printf("Vertex %d added with %d connections.\n", NEW_VERTEX, NUM_CONNECTIONS);
}

int BFS_MAIN(void)
{
    int ADJACENT[MAX_NUM][MAX_NUM] = {0};
    int VERTEX_COUNT = 5;

    int INITIAL_MATRIX[5][5] =
    {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };

    // DOUBLE NESTED LOOP TO CONCATENATE
    // EACH SIDE OF THE MATRIX

    for (int i = 0; i < VERTEX_COUNT; i++)
        for (int j = 0; j < VERTEX_COUNT; j++)
            ADJACENT[i][j] = INITIAL_MATRIX[i][j];

    BFS_SEARCH(ADJACENT, VERTEX_COUNT, 0);

    // ESTABLISH THE SIZE OF EACH CONNECTION ON ADJACENT ENDS
    // ADD THE CORRESPONDING INFORMATION

    int NEW_CONNECTIONS[] = {3, 3};
    ADD_VERTEX(ADJACENT, &VERTEX_COUNT, MAX_NUM, NEW_CONNECTIONS);

    BFS_SEARCH(ADJACENT, VERTEX_COUNT, 0);

    return 0;
}
