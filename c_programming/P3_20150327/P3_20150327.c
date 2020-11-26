#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*R_MAX = row , C_MAX = column*/
#define R_MAX 6 
#define C_MAX 7
#define MAP_STARTX 0
#define MAP_STARTY 4
#define ERR 99

char map[R_MAX][C_MAX];

void gotoxy(int x, int y){
    printf("\033[%d;%df",y,x);
    fflush(stdout);
}

void clear_borad(){
    for(int i=0; i<R_MAX; i++){
        for(int j=0; j<C_MAX; j++){
            map[i][j]='_';
        }
    }
}

void next_player(int *player, char *data){
    if(*player ==2){
        *data='0';
        *player-=1;
    }
    else if(*player ==1){
        *data='@';
        *player+=1;
    }
}


int print_msg(int player, int finish ){
    int c_num;
    if(finish == 0){
        printf("P1's marler is 0, P2's marker is @\n");
        printf("P%d's turn, Enter the column number : ", player);
        scanf(" %d", &c_num);
        
        return c_num;
    }
    else if(finish == 1){
        printf("P%d Win\n", player);
        return 0;
    }
    else{
        printf("Game ended in a draw.\n");
        return 0;
    }
}

void draw_borad(){
    int X, Y;
    int i, j;
    for(i=0; i<R_MAX+1; i++){
        for(j=0; j<C_MAX; j++){
            X=MAP_STARTX+(j*5);
            Y=MAP_STARTY+i;
            if(i==0){
                gotoxy(X,Y);
                printf("  %d  ", j+1);
            }
            else{
                gotoxy(X, Y);
                printf("|_%c_|", map[i-1][j]);
            }
        }
        printf("\n");
    }

}
int insert_data(int number, char data){
    for(int i=R_MAX-1; i>=0; i--){
        if(map[i][number-1] == '_'){
            map[i][number-1] = data;
            return i;
        }
    }
    return ERR;
}
              
int check_board(char arr[R_MAX][C_MAX], int col_number, int row_number, char *data){
    int count=0;
    int x, y;
  //  printf("x : %d y : %d", col_number, row_number);
    
    //col
    x=col_number;
    y=row_number;
    count =0;
    while(arr[y][x-1]== *data && x>0)
        x--;
    while(arr[y][x++] == *data && x<=C_MAX){
        count++;
  //      printf("count : %d , x: %d, y: %d", count, x, y);
    }
    if(count >=4)
        return 1;

    //row
    x=col_number-1;
    y=row_number;
   // printf("y : %d ",y);
    count =0;
    while(arr[y-1][x]== *data && y>0) {
        y--;
    }
    while(arr[y++][x] == *data && y<=R_MAX){ 
          count++;
//        printf("count : %d , x: %d, y: %d", count, x, y);
    }
    if(count >=4) return 1;


    //diagonal
    x=col_number-1;
    y=row_number;
   // printf("x : %d , y : %d ", x, y);
    count =0;
    while(arr[y+1][x-1]== *data && x>0 && y<=R_MAX){
        y++;
        x--;
    }
    while(arr[y--][x++] == *data && x<=C_MAX && y>=0){
    //    printf("count : %d , x: %d, y: %d", count, x, y);
        count++;
    }
    if(count >=4)
        return 1;

    x=col_number-1;
    y=row_number;
   // printf("x : %d , y : %d ", x, y);
    count =0;
    while(arr[y-1][x-1]== *data && x>0 && y>0){
        x--;
        y--;
    }
    while(arr[y++][x++] == *data && x<=C_MAX && y<=R_MAX){
        count++;
//        printf("count : %d , x: %d, y: %d", count, x, y);
    }
    if(count >=4)
        return 1;


    return 0;
}
void add_block(){
    int block_number;
    char data='X';
    while(1){
        printf("For initalization ,add block : ");
        scanf(" %d", &block_number);
        if(block_number == 0){
            printf("Game started.\n");
            break;
        }
        else{
            insert_data(block_number, data);
        }
    }
}


int check_draw(){
    char temp_p1[R_MAX][C_MAX];
    char temp_p2[R_MAX][C_MAX];
    char data_p1='0';
    char data_p2='@';
    int draw_count_p1=0;
    int draw_count_p2=0;
    for(int i=0; i<R_MAX; i++){
        for(int j=0; j<C_MAX; j++){
            temp_p1[i][j]=map[i][j];
            temp_p2[i][j]=map[i][j];
        }
    }
   
    for(int i=0; i<R_MAX; i++){
        for(int j=0; j<C_MAX; j++){
            if(temp_p1[i][j] == '_'){
                temp_p1[i][j]= data_p1;
            }
            if(temp_p2[i][j] == '_'){
                temp_p2[i][j] = data_p2;
            }
        }
    }

    for(int y=0; y<R_MAX; y++){
        for(int x=0; x<C_MAX; x++){
            int p=x+1;
            if(temp_p1[y][x] == '0'){
//                printf("check temp[%d][%d] = %c ", y, x, temp_p1[y][x]);
                if(check_board(temp_p1, p, y, &data_p1) == 1){
                    draw_count_p1=1;
                }
            }
            if(temp_p2[y][x] == '@'){
                if(check_board(temp_p2, p, y, &data_p2) == 1){
                    draw_count_p2=1;
                }
            }
        }
    }

//    printf("dc_p1 = %d , dc_p2 = %d", draw_count_p1, draw_count_p2);

    if(draw_count_p1 == 0 && draw_count_p2 == 0) return 2;

    return 0;
}
 

int main(){
    int col_number;
    int row_number;
    int player=1;
    char data='0';
    int finish=0;
    clear_borad();
    add_block();
    while(1){

        system("clear");
        draw_borad();
        if(finish==1 || finish==2){
            next_player(&player, &data);
            print_msg(player, finish);
            return 0;
        }
        
        col_number=print_msg(player, finish);
        row_number = insert_data(col_number, data);
        finish=check_board(map, col_number, row_number, &data);
        
        if(finish==0){
            finish=check_draw();
        }
        next_player(&player, &data);
    }
    return 0;
}

