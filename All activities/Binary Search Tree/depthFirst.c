#include <stdio.h>
#include <stdlib.h>

#define MAX 9
#define VISITED -1
#define UNVISITED 100

typedef struct node{
    int elem;
    struct node* link;
} *ptr, Node;

typedef ptr Graph[MAX];

void DFSUtil(Graph G, int v, int visited[MAX]){
    visited[v] = VISITED;
    printf("%d", v);

    ptr trav = G[v];
    while(trav != NULL){
        if(visited[trav->elem] == UNVISITED){
            DFSUtil(G, trav->elem, visited);
        }
        trav = trav->link;
    }
}

void DFS(Graph G, int start){
    int visited[MAX];
    for(int i = 0; i < MAX; ++i){
        visited[i] = UNVISITED;

        DFSUtil(G, start, visited);
    }
}