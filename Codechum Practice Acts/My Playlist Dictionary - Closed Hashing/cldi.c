#include <stdio.h>
#include <string.h>
#include "cldi.h"

String genreTable[16] = {
    "Ballad", "Pop Rock", "Pop", "R&B", "Rock", "Country Pop", "J-Pop", "K-Pop",
    "Classical", "Theater", "EDM", "OPM", "Reggae", "Dance", "Jazz", "Indie"
};

int hash(String genre){
    for(int i = 0; i < 16; i++){
        if(strcmp(genreTable[i], genre) == 0){
            return i;
        }
    }
    return -1;
}

void insert(VirtualHeap *VH, Song song){
    int index = hash(song.genre);
    if(index == -1) return;

    
    if(strcmp(VH->H[index].elem.genre, "Empty") == 0){
        VH->H[index].elem = song;
        VH->H[index].next = -1;
        return;
    }

    
    int newNode = VH->avail;
    if(newNode == -1) return; 

    VH->avail = VH->H[newNode].next;      
    VH->H[newNode].elem = song;
    VH->H[newNode].next = -1;

    
    int trav = index;
    while(VH->H[trav].next != -1){
        trav = VH->H[trav].next;
    }
    VH->H[trav].next = newNode;
}

void deleteMember(VirtualHeap *VH, Song song){
    int index = hash(song.genre);
    if(index == -1) return;

    if(strcmp(VH->H[index].elem.genre, "Empty") == 0) return;

    int trav = index, prev = -1;

    
    if(strcmp(VH->H[index].elem.songName, song.songName) == 0 &&
       strcmp(VH->H[index].elem.singer, song.singer) == 0){
        if(VH->H[index].next == -1){
            strcpy(VH->H[index].elem.genre, "Empty");
            VH->H[index].elem.songName[0] = '\0';
            VH->H[index].elem.singer[0] = '\0';
        } else {
            int nxt = VH->H[index].next;
            VH->H[index].elem = VH->H[nxt].elem;
            VH->H[index].next = VH->H[nxt].next;
            VH->H[nxt].next = VH->avail;
            VH->avail = nxt;
        }
        return;
    }

    
    prev = index;
    trav = VH->H[index].next;
    while(trav != -1){
        if(strcmp(VH->H[trav].elem.songName, song.songName) == 0 &&
           strcmp(VH->H[trav].elem.singer, song.singer) == 0){
            VH->H[prev].next = VH->H[trav].next;
            VH->H[trav].next = VH->avail;
            VH->avail = trav;
            return;
        }
        prev = trav;
        trav = VH->H[trav].next;
    }
}

int search(VirtualHeap VH, Song song){
    int index = hash(song.genre);
    if(index == -1) return 0;

    int trav = index;
    while(trav != -1){
        if(strcmp(VH.H[trav].elem.songName, song.songName) == 0 &&
           strcmp(VH.H[trav].elem.singer, song.singer) == 0){
            return 1;
        }
        trav = VH.H[trav].next;
    }
    return 0;
}