#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#define X_MAX 9
#define Y_MAX 9

char map[X_MAX][Y_MAX];

struct player{
    int check_win;
    char name;
    char xy[10];
    char p_block[9];
    char my_char;
    bool my_turn;
    bool win_flag;
    bool accept;
    bool total_accept;
};

void printPBlock(struct player *p);

void initPlayer(struct player *O){
    for(int y=0; y<9; y++){
        O->p_block[y]='_';
    }
    O->win_flag=false;
    O->my_turn=true;
    O->check_win=99;
    O->accept = true;
    O->total_accept=true;
}

void drawBoard(){
    printf("   ");
    for(int i=1; i<=9; i++){
        if(i!=9) printf("%d ", i);
        else printf("%d \n", i);
    }
    printf("   ");
    for(int i=1; i<=9; i++){
        if(i!=9) printf("_ ");
        else printf("_ \n");
    }
    for(int y=0; y<9; y++){
        for(int x=0; x<10; x++){
            if(x==0) printf("%d |", y+1);
            else if(x==9) printf("%c|\n", map[y][x-1]);
            else printf("%c|", map[y][x-1]);
        }
    }
    printf("\n");
}

void initBoard(){
    for(int y=0; y<Y_MAX; y++){
        for(int x=0; x<X_MAX; x++){
            map[y][x]='_';
        }
    }
}

int insertPBlock(struct player *p, int args, ...){
    va_list ap;
    va_start(ap, args);
    for(int i=0; i<args; i++){
        int num= va_arg(ap, int);
        p->p_block[num-1]=p->my_char;
    }
    va_end(ap);
    return 0;
}

int drawPBlock(struct player *p){
    //srand((unsigned int)time(NULL));  
    int r = (rand() % 14)+1;     /* Generate a random integer between [0, 13] */
    switch(r){
        case 1:
            insertPBlock(p, 3, 1, 2, 3);
            break;
        case 2:
            insertPBlock(p, 4, 1, 2, 3, 4);
            break;
        case 3:
            insertPBlock(p, 4, 1, 2, 3, 6);
            break;
        case 4:
            insertPBlock(p, 4, 1, 2, 3, 5);
            break;
        case 5:
            insertPBlock(p, 4, 2, 3, 4, 5);
            break;
        case 6:
            insertPBlock(p, 4, 1, 2, 5, 6);
            break;
        case 7:
            insertPBlock(p, 4, 1, 2, 4, 5);
            break;
        case 8:
            insertPBlock(p, 5, 1, 4, 5, 7, 8);
            break;
        case 9:
            insertPBlock(p, 5, 2, 3, 4, 5, 7);
            break;
        case 10:
            insertPBlock(p, 5, 1, 2, 5, 6, 8);
            break;
        case 11:
            insertPBlock(p, 5, 2, 3, 4, 5, 8);
            break;
        case 12:
            insertPBlock(p, 5, 3, 4, 5, 6, 7);
            break;
        case 13:
            insertPBlock(p, 5, 1, 4, 5, 6, 9);
            break;
        case 14:
            insertPBlock(p, 5, 2, 4, 5, 6, 8);
            break;
    }

    printPBlock(p);
    return 0;
}

void *nowPlayer(struct player *A, struct player *B){
    if(A->my_turn == true) return A;
    else return B;
}

void nextPlayer(struct player *A, struct player *B){
    if(A->my_turn == true){
        A->my_turn =false;
        B->my_turn =true;
    }
    else{
        A->my_turn =true;
        B->my_turn =false;
    }
}

void clearPBlock(struct player *p){
    for(int i=0; i<9; i++){
        p->p_block[i]='_';
    }
}

int Rotate(int num){
    switch (num){
        case 0:
            return 6;
        case 1:
            return 3;
        case 2:
            return 0;
        case 3:
            return 7;
        case 4:
            return 4;
        case 5: 
            return 1;
        case 6:
            return 8;
        case 7:
            return 5;
        case 8:
            return 2;
    }
    return 99;
}

void RotateBlock(struct player *p){
    char temp[9];
    
    for(int i=0; i<9; i++){
        temp[i]=p->p_block[Rotate(i)];
    }

    for(int i=0; i<9; i++){
        p->p_block[i] = temp[i];
    }
}
void printPBlock(struct player *p){
    printf("P%c's block:\n", p->name);
    for(int y=0; y<4; y++){
        for(int x=0; x<3; x++){
            if(y==0){
                if(x==2) printf(" _\n");
                else printf(" _");
            }
            else{
                if(x==2) printf("%c|\n", p->p_block[(y-1)*3+x]);
                else if(x==0) printf("|%c|", p->p_block[(y-1)*3+x]);
                else printf("%c|", p->p_block[(y-1)*3+x]);
            }
        }
    }
    printf("\n");
}

void getCoordinate(struct player *p){
    while(1){
        printf("Put your block(y x) or Rotate (0): ");
        gets(p->xy);
        p->xy[3]='\0';
        if(strcmp("0", p->xy)==0 || strcmp(" 0", p->xy)==0 || strcmp(" 0 ", p->xy)==0 || strcmp("0 ", p->xy)==0){
            RotateBlock(p);
            printPBlock(p);
        }
        else    break;
    }
}

int insertBlock(struct player *p){

    int pinY = atoi(strtok(p->xy, " "));
    int pinX = atoi(strtok(NULL, " "));
    int num=0;

    for(int y= pinY-1; y<pinY+2; y++){
        for(int x=pinX-1; x<pinX+2; x++){
            if(p->p_block[num++] != '_'){
                if(map[y][x]!='_'){
                    p->accept=false;
                }
            }
        }
    }
    if(p->accept == false){
        printf("\nP%c is not able to put the block into (%d, %d)\n", p->name, pinY, pinX);
        p->accept=true;
        return 0;
    }
    num=0;
    if(p->accept == true){
        for(int y= pinY-1; y<pinY+2; y++){
            for(int x=pinX-1; x<pinX+2; x++){
                if(map[y][x]=='_'){
                   map[y][x]=p->p_block[num];
                }
                num+=1;
            }
        }
    }
    return 1;
}

void enableEndGame(struct player *p){
    int num=0;
    int count=1;
    int rotate_count=1;
    for(int rotate=0; rotate<4; rotate++){
        for(int j=0; j<=6; j+=1){
            for(int i=0; i<=6; i+=1){
                for(int y=0; y<3; y++){
                    for(int x=0; x<3; x++){
                        if(p->p_block[num++] != '_'){
                            if(map[y+j][x+i]!='_'){
                                p->total_accept=false;
                            }
                        }
                    }
                }
                num=0;
                if(p->total_accept==false){
                    count++;
                    p->total_accept=true;
                }
            }
        }
        if(count==49) rotate_count++;
        RotateBlock(p);
        count=0;
    }
    if(rotate_count==4){
        p->check_win=0;
    }
}


int main(){
    struct player A, B;

    initPlayer(&A);
    A.my_char='0';
    A.name='1';
    initPlayer(&B);
    B.my_char='@';
    B.name='2';
    int ret;
    initBoard();
    while(1){
        drawBoard();
        
        drawPBlock(nowPlayer(&A, &B));
        enableEndGame(nowPlayer(&A, &B));
        if(A.check_win ==0){
            printf("\nP1 fails to put the block, P2 wins!\n");
            break;
        }
        if(B.check_win ==0 ){
            printf("\nP2 fails to put the block, P1 wins!\n");
            break;
        }
        while(1){
            getCoordinate(nowPlayer(&A, &B));
            ret=insertBlock(nowPlayer(&A, &B));
            if(ret !=0){
                break;
            }
        }
        clearPBlock(nowPlayer(&A, &B));
        nextPlayer(&A, &B);
    }
}
