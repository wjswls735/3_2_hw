#include <stdio.h>
#include <stdlib.h>
int main(){
    float DM, PL, DS;
    float average;
    char* grade;

    printf("Put the discrete math score : ");
    scanf(" %f", &DM);
    
    printf("Put the programming language score : ");
    scanf(" %f", &PL);

    printf("Put the data structure score : ");
    scanf(" %f", &DS);

    average=(DM+PL+DS)/3;
    grade=malloc(sizeof(char)*3);
    if(average>95) grade="A+\0";
    else if(average >90 && average <95) grade="A0\0";
    else if(average >85 && average <90) grade="B+\0";
    else if(average >80 && average <85) grade="B0\0";
    else if(average >75 && average <80) grade="C+\0";
    else if(average >70 && average <75) grade="C0\0";
    else grade="F\0";
    printf("The average score is %.2f and the gradis %s\n", average, grade);
    return 0;
}
