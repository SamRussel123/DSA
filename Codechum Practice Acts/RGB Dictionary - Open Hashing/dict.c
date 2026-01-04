#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int hashFunction(int rgb[3]) {
    int weightedSum = (rgb[0] * 3) + (rgb[1] * 5) + (rgb[2] * 7);
    return weightedSum % PALETTE_SIZE;
}

void createDictionary(Dictionary *dict) {
    for(int i = 0; i < PALETTE_SIZE; ++i){
        dict->buckets[i] = NULL;
    }
}

Node* createNode(Color newColor) {
    Node* newNode = malloc(sizeof(Node));
    if(newNode != NULL){
        newNode->data = newColor;
        newNode->next = NULL;
    }
    
    return newNode;
}

void insertColor(Dictionary *dict, Color newColor) {
    int index = hashFunction(newColor.RGBVal);
    Node* newNode = createNode(newColor);
    if(newNode == NULL){
        printf("Error");
        return;
    }
    
    newNode->next = dict->buckets[index];
    dict->buckets[index] = newNode;
    
    printf("-> Inserted '%s' (RGB: %d, %d, %d) into bucket [%d].\n", 
            newColor.colorName,
            newColor.RGBVal[0],
            newColor.RGBVal[1],
            newColor.RGBVal[2],
            index);
}

Color* searchColor(Dictionary *dict, int rgb[3]) {
    int index = hashFunction(rgb);
    printf("Searching for RGB (%d, %d, %d) in bucket [%d]...\n",
           rgb[0], rgb[1], rgb[2], index);
    Node* curr = dict->buckets[index];
    while(curr != NULL){
        if(curr->data.RGBVal[0] == rgb[0] &&
           curr->data.RGBVal[1] == rgb[1] && 
           curr->data.RGBVal[2] == rgb[2]){
               return &(curr->data);
           }
           curr = curr->next;
    }
    
    
    return NULL;
}