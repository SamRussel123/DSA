#include <stdio.h>
#include <stdbool.h>
#include "bitvector.h"

#define QCOUNT 10

void setAnswer(BitVect* profile, int index, int val){
    if(profile == NULL) return;
    if(index < 0 || index >= QCOUNT) return;
    
    if(val == 1){
        profile->answers[index] = 1;
    } else {
        profile->answers[index] = 0;
    }
}

int getAnswer(BitVect profile, int index){
    if(index < 0 || index >= QCOUNT) return 0;
    
    if(profile.answers[index] != 0){
        return 1;
    } else {
        return 0;
    }
}

int countYesAnswers(BitVect profile) {
    int count = 0;
    int i;
    for(i = 0; i < QCOUNT; ++i){
        if(getAnswer(profile, i) == 1){
            count++;
        }
    }
    return count;
}

void printAnswers(BitVect profile) {
    int i;
    for(i = QCOUNT - 1; i >= 0; --i){
        int bit = getAnswer(profile, i);
        printf("%d", bit);
    }
    printf("\n");
}

int compareProfiles(BitVect a, BitVect b){
    int matches = 0;
    int i;
    for(i = 0; i < QCOUNT; ++i){
        int ai = getAnswer(a, i);
        int bi = getAnswer(b, i);
        if(ai == bi){
            matches++;
        }
    }
    return matches;
}

BitVect unionProfiles(BitVect a, BitVect b){
    BitVect out = {0};
    int i;
    for(i = 0; i < QCOUNT; ++i){
        if(getAnswer(a, i) == 1 || getAnswer(b, i) == 1){
            out.answers[i] = 1;
        } else {
            out.answers[i] = 0;
        }
    }
    return out;
}

BitVect intersectProfiles(BitVect a, BitVect b){
    BitVect out = {0};
    int i;
    for(i = 0; i < QCOUNT; ++i){
        if(getAnswer(a, i) == 1 && getAnswer(b, i) == 1){ 
            out.answers[i] = 1;
        } else {
            out.answers[i] = 0;
        }
    }
    return out;
}

BitVect differenceProfiles(BitVect a, BitVect b) {
    BitVect out = {0};
    int i;
    for(i = 0; i < QCOUNT; ++i){
        if(getAnswer(a, i) == 1 && getAnswer(b, i) == 0){
            out.answers[i] = 1;
        } else {
            out.answers[i] = 0;
        }
    }
    return out;
}