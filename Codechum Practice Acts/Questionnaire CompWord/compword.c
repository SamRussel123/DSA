#include <stdio.h>
#include <stdbool.h>
#include "compword.h"

// write your functions here...

#define QCOUNT 10

void setAnswer(CompWord* profile, int index, int val){
    if(index < 0 || index >= QCOUNT) return;
    
    short mask = 1 << index;
    if(val){
        *profile |= mask;
    } else {
        *profile &= ~mask;
    }
}

int getAnswer(CompWord profile, int index){
    if(index < 0 || index >= QCOUNT) return 0;
    
    short mask = 1 << index;
    if((profile & mask) != 0){
        return 1;
    } else {
        return 0;
    }
}

int countYesAnswers(CompWord profile){
    int count = 0;
    for(int i = 0; i < QCOUNT; ++i){
        if(getAnswer(profile, i) == 1) {
            count++;
        }
    }
    return count++;
}

void printAnswers(CompWord profile) {
    for(int i = QCOUNT - 1; i >= 0; --i){
        printf("%d", getAnswer(profile, i));
    }
    printf("\n");
}

int compareProfiles(CompWord a, CompWord b){
    CompWord diff = a ^ b;
    int mismatches = countYesAnswers(diff);
    return QCOUNT - mismatches;
}

CompWord unionProfiles(CompWord a, CompWord b){
    return a | b;
}

CompWord intersectProfiles(CompWord a, CompWord b){
    return a & b;
}

CompWord differenceProfiles(CompWord a, CompWord b){
    return a & ~b;
}