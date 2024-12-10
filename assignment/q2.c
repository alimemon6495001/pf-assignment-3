#include <stdio.h>
#include <string.h>

struct player {
    int ballScore[12];
    char playerName[20];
    int totalScore;
};

void playGame(struct player* one) {
    for(int i=0;i<12;i++) {
        printf("enter ball %d score:\t",i+1);
        scanf("%d",&one->ballScore[i]);
    }
}

void validScore(struct player* one) {
    for(int i=0;i<12;i++) {
        if(one->ballScore[i]>6 || one->ballScore[i]<0) {
            one->ballScore[i]=0;
        }
        else {
            one->totalScore+=one->ballScore[i];
        }
    }
}

void findWinner(struct player one,struct player two) {
    if(one.totalScore>two.totalScore) {
        printf("player one won!!\n");
    }
    else if(two.totalScore>one.totalScore) {
        printf("player two won!!\n");
    }
    else {
        printf("it was a draw!!");
    }
}

void displayDetail(struct player one,struct player two) {
    printf("player one name: %s\n",one.playerName);
    printf("ball scores: [");
    for(int i=0;i<12;i++) {
        printf("%d,",one.ballScore[i]);
    }
    printf("]\n");
    printf("total score: %d\n\n",one.totalScore);
    printf("player one name: %s\n",two.playerName);
    printf("ball scores: [");
    for(int i=0;i<12;i++) {
        printf("%d,",two.ballScore[i]);
    }
    printf("]\n");
    printf("total score: %d",two.totalScore);
}
int main() {
    struct player one;
    struct player two;
    char name[20];
    printf("enter player one name:\t");
    scanf(" %[^\n]s",name);
    strcpy(one.playerName,name);
    printf("enter player two name:\t");
    scanf(" %[^\n]s",name);
    strcpy(two.playerName,name);
    one.totalScore=0;
    two.totalScore=0;
    printf("enter scores for player one:\n");
    playGame(&one);
    printf("\nenter scores for player two:\n");
    playGame(&two);
    validScore(&one);
    validScore(&two);
    findWinner(one,two);
    displayDetail(one,two);
}