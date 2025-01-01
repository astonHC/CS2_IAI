/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING DFS */

/* NESTED INCLUDES */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 128

typedef struct NODE 
{
    int VERTEX;
    struct NODE* NEXT;

} DFS_NODE;

typedef struct GRAPH
{
    int VERTICES;
    DFS_NODE** ADJ;
    int* VISITED;

} DFS_GRAPH;

DFS_NODE* INIT_NODE(int VERTEX) 
{
    DFS_NODE* NEW_NODE = (DFS_NODE*)malloc(sizeof(DFS_NODE));
    NEW_NODE->NEXT = NULL;
    NEW_NODE->VERTEX = VERTEX;
    return NEW_NODE;
}

DFS_GRAPH* INIT_GRAPH(int VERTICES) 
{
    DFS_GRAPH* NEW_GRAPH = (DFS_GRAPH*)malloc(sizeof(DFS_GRAPH));
    NEW_GRAPH->ADJ = (DFS_NODE**)malloc(VERTICES * sizeof(DFS_NODE*));
    NEW_GRAPH->VISITED = (int*)malloc(VERTICES * sizeof(int));
    NEW_GRAPH->VERTICES = VERTICES;

    for (int i = 0; i < VERTICES; i++) 
    {
        NEW_GRAPH->ADJ[i] = NULL;
        NEW_GRAPH->VISITED[i] = 0;
    }

    return NEW_GRAPH;
}

void ADD_EDGE(DFS_GRAPH* GRAPH, int SRC, int DEST) 
{
    DFS_NODE* NEW_NODE = INIT_NODE(DEST);
    NEW_NODE->NEXT = GRAPH->ADJ[SRC];
    GRAPH->ADJ[SRC] = NEW_NODE;
}

void DFS(DFS_GRAPH* GRAPH, int VERTEX) 
{
    DFS_NODE* TEMP = GRAPH->ADJ[VERTEX];

    GRAPH->VISITED[VERTEX] = 1;
    printf("%d", VERTEX);

    while (TEMP != NULL) 
    {
        int CONNECTED_VERTEX = TEMP->VERTEX;
        if (GRAPH->VISITED[CONNECTED_VERTEX] == 0) 
        {
            DFS(GRAPH, CONNECTED_VERTEX);
        }
        
        TEMP = TEMP->NEXT;
    }
}

int main(void) 
{
    int VERTS = 5;

    DFS_GRAPH* G = INIT_GRAPH(VERTS);

    ADD_EDGE(G, 0, 1);
    ADD_EDGE(G, 0, 2);
    ADD_EDGE(G, 1, 2);
    ADD_EDGE(G, 1, 3);
    ADD_EDGE(G, 2, 4);

    printf("DFS traversal starting from vertex 0:\n");
    DFS(G, 0);

    return 0;
}
