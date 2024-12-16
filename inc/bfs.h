/* COPYRIGHT (C) HARRY CLARK 2024 */
/* CS2_IAI STUDY MATERIAL */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING BFS */

#ifndef BFS_H
#define BFS_H

/* NESTED INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define         MAX_NUM         100

typedef struct BFS
{
    int QUEUE[MAX_NUM];
    struct BFS* FRONT;
    struct BFS* REAR;

    int CURRENT;

} BFS;

void BFS_SEARCH(int ADJ[MAX_NUM][MAX_NUM], int VERTEX, int SRC);
void ADD_VERTEX(int ADJ[MAX_NUM][MAX_NUM], int *VERTEX, int MAX_VERTEX, int CONNECTIONS[]);
int BFS_MAIN(void);

#endif