#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
char map[MAX][MAX];

struct point{
    int x;
    int y;
};
struct server{
    int figure_num;
    struct figure *head;
    struct figure *head_pointer;
};

struct server s;

enum Shape{ Line =1, Rect = 2, Circle =3 };

struct figure{
    int id;
    enum Shape shape;
    struct point p1;
    struct point p2;
    struct figure *next;
    struct figure *prev;
    int r;
};

void drawLine(struct figure *F, char ch){
    double ic; //기울기
    ic =(double)(F->p2.y - F->p1.y)/(double)(F->p2.x - F->p1.x);
/*
    printf("p2.y = %d, p1.y =%d\n", F->p2.y, F->p1.y);
    printf("p2.x = %d, p1.x =%d\n", F->p2.x, F->p1.x);
    
    printf("\n ic : %lf \n", ic);
    */
    if(F->p1.x < F->p2.x){
        for(int i=F->p1.x; i<=F->p2.x; i++){
            double y=(ic*i)-(ic*(F->p1.x))+(F->p1.y);
            if(y - (int)y ==0){
                map[(int)y][i]=ch;
            }
          //  printf("y = %.2lf \n", y);
        }
    }
    else{
        for(int i=F->p2.x; i<=F->p1.x; i++){
            double y=(ic*i)-(ic*(F->p1.x))+(F->p1.y);
            if(y - (int)y ==0){
                map[(int)y][i]=ch;
            }
      //      printf("y = %.2lf \n", y);
        }
    }
}

void drawRect(struct figure *F, char ch){
    if(F->p1.x < F->p2.x){
        for(int i=F->p1.x; i<=F->p2.x; i++){
            map[F->p1.y][i] = ch;
        }
        for(int i=F->p1.x; i<=F->p2.x; i++){
            map[F->p2.y][i] = ch;
        }
    }
    else{

        for(int i=F->p2.x; i<=F->p1.x; i++){
            map[F->p1.y][i] = ch;
        }
        for(int i=F->p2.x; i<=F->p1.x; i++){
            map[F->p2.y][i] = ch;
        }
    }
    if(F->p1.y < F->p2.y){
        for(int i=F->p1.y; i<=F->p2.y; i++){
            map[i][F->p1.x] = ch;
        }
        for(int i=F->p1.y; i<=F->p2.y; i++){
            map[i][F->p2.x] = ch;
        }
    }
    else{

        for(int i=F->p2.y; i<=F->p1.y; i++){
            map[i][F->p1.x] = ch;
        }
        for(int i=F->p2.y; i<=F->p1.y; i++){
            map[i][F->p2.x] = ch;
        }
    }
}

void drawCircle(struct figure *F, char ch){
    for(int y=((F->p1.y)-(F->r)); y<=((F->p1.y)+(F->r)); y++){
        for(int x=((F->p1.x)-(F->r)); x<=((F->p1.x)+(F->r)); x++){
            if((x-F->p1.x)*(x-F->p1.x) + (y-F->p1.y)*(y-F->p1.y) == (F->r)*(F->r)){
                map[y][x] = ch;
            }
        }
    }
}
    

void drawFigure(struct figure *F, char ch){
    switch(F->shape){
        case 1:
            drawLine(F, ch);
            break;
        case 2:
            drawRect(F, ch);
            break;
        case 3:
            drawCircle(F, ch);
            break;
    }
}

void Add(){
    struct figure *F;
    F=(struct figure *)malloc(sizeof(struct figure));
    char *shape;
    
    printf("Enter the figure id : ");
    scanf("%d", &(F->id));
    printf("Enter shape (1: Line, 2: Rect, 3:Circle): ");
    scanf(" %d", &(F->shape));
    if(F->shape !=3){
        printf("Enter the (r,c) coordinate of P1: ");
        scanf(" %d %d", &(F->p1.y), &(F->p1.x));
        printf("Enter the (r,c) coordinate of P2: ");
        scanf(" %d %d", &(F->p2.y), &(F->p2.x));
        
        shape=(char*)malloc(sizeof(char)*6);
        if(F->shape ==1) {
            strncpy(shape, "Line\0", 5);
        }
        else strncpy(shape, "Rect\0", 5);

        printf("%s (id = %d) from (%d, %d) to (%d, %d) is added\n", shape, F->id, F->p1.y, F->p1.x, F->p2.y, F->p2.x);
        free(shape);
    }
    else{
        printf("Enter the (r,c) coordinate of P1: ");
        scanf(" %d %d", &(F->p1.y), &(F->p1.x));
        printf("Enter the R1: ");
        scanf("%d", &(F->r));
        shape=(char*)malloc(sizeof(char)*8);
        strncpy(shape, "Circle\0", 7);
        printf("%s (id = %d) with the center (%d, %d) and the radius (%d) is added\n", shape, F->id, F->p1.y, F->p1.x, F->r);
        free(shape);
    }

    if(s.head == NULL){
        s.head = F;
        s.head_pointer=F;
        s.head->next = F;
        s.head->prev = F;
        s.figure_num=1;
    }
    else{
        F->next = s.head->next;
        s.head->next=F;
        F->prev = s.head;
        F->next->prev=F;
        s.figure_num+=1;
    }
    char *ch=(char *)malloc(sizeof(char));
    *ch='*';
    drawFigure(F, *ch);
    free(ch);
}

void Remove(){
    int rm_id;
   
    char *shape;
    printf("Enter the figure id: ");
    scanf("%d", &rm_id);

    for(int i=0; i<s.figure_num; i++){
        if(s.head_pointer->id == rm_id){
            char *ch=(char *)malloc(sizeof(char));
            *ch=' ';
            drawFigure(s.head_pointer, *ch);
            free(ch);
            shape=(char *)malloc(sizeof(char)*7);
            if(s.head_pointer->shape == 1) strncpy(shape, "Line\0", 5);
            else if(s.head_pointer->shape == 2) strncpy(shape, "Rect\0", 5);
            else strncpy(shape, "Circle\0", 7);

            printf("%s (id = %d) from (%d, %d) to (%d, %d) is removed\n", shape, rm_id, s.head_pointer->p1.y, s.head_pointer->p1.x, s.head_pointer->p2.y, s.head_pointer->p2.x);
            if(s.figure_num==1){
                s.head=NULL;
                free(s.head_pointer);
                s.head_pointer=NULL;
                s.figure_num--;
            }
            else{
                s.head_pointer->prev->next = s.head_pointer->next;
                s.head_pointer->next->prev = s.head_pointer->prev;
                free(s.head_pointer);
                s.figure_num--;
            }
        }
        else{
            s.head_pointer= s.head_pointer->next;
        }
    }
}

void Adjust(){
    int search_id;
    char *name;
    printf("Enter the figure id: ");
    scanf(" %d", &search_id);


    for(int i=0; i<s.figure_num; i++){
        if(s.head_pointer->id == search_id){

            char *ch=(char *)malloc(sizeof(char));
            *ch=' ';
            drawFigure(s.head_pointer, *ch);
            free(ch);

            printf("Enter the (r,c) coordinate of P1: ");
            scanf(" %d %d", &(s.head_pointer->p1.x), &(s.head_pointer->p1.y));
            printf("Enter the (r,c) coordinate of P2: ");
            scanf(" %d %d", &(s.head_pointer->p2.x), &(s.head_pointer->p2.y));
            name = (char*)malloc(sizeof(char)*10);
            if(s.head_pointer->shape ==1) strncpy(name, "Line\0", 5);
            else if(s.head_pointer->shape == 2) strncpy(name, "Rectangle\0", 10);
            else strncpy(name, "Circle\0", 7);
            if(s.head_pointer->id !=3){
                printf("%s (id: %d) from (%d, %d) to (%d, %d) is adjusted.\n", name, s.head_pointer->id, s.head_pointer->p1.y, s.head_pointer->p1.x, s.head_pointer->p2.y, s.head_pointer->p2.x);
            }
            else{
                printf("%s (id: %d) with the center(%d, %d) and radius(%d) is added\n", name, s.head_pointer->id, s.head_pointer->p1.y, s.head_pointer->p1.x, s.head_pointer->r);
            }
            break;
        }
        else{
            s.head_pointer = s.head_pointer->next;
        }
    }
    char *ch=(char *)malloc(sizeof(char));
    *ch='*';
    drawFigure(s.head_pointer, *ch);
    free(ch);
}

void Export(){
    FILE *fd;
    fd= fopen("print.txt", "w");

    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            fputc(map[y][x], fd);
            if(x==MAX-1){
                fputc('\n', fd);
            }
        }
    }
    fclose(fd);
}
void Print(){
    char *shape;
    if(s.figure_num==0){
         printf("Empty\n");
    }
    for(int i=0; i<s.figure_num; i++){
        printf("s.figure_num = %d\n", s.figure_num);
        
        shape=(char*)malloc(sizeof(char)*10);
        if(s.head_pointer->shape == 1){
            strncpy(shape, "Line\0", 5);
            printf("%s (id: %d) from (%d, %d) to (%d, %d).\n", shape, s.head_pointer->id, s.head_pointer->p1.y, s.head_pointer->p1.x, s.head_pointer->p2.y, s.head_pointer->p1.x);

        }
        else if(s.head_pointer->shape ==2){
            strncpy(shape, "Rectangle\0", 10);
            printf("%s (id: %d) from (%d, %d) to (%d, %d).\n", shape, s.head_pointer->id, s.head_pointer->p1.y, s.head_pointer->p1.x, s.head_pointer->p2.y, s.head_pointer->p2.x);
        }
        else{
            strncpy(shape, "Circle\0", 8);
            printf("%s (id: %d) from (%d, %d)and the radius(%d).\n", shape, s.head_pointer->id, s.head_pointer->p1.y, s.head_pointer->p1.x, s.head_pointer->r);
        }
    
        free(shape);
        s.head_pointer=s.head_pointer->next;
    }
}



int main(){

    int command;

    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            map[y][x]=' ';
        }
    }

    while(1){
        printf("Enter a command( 1: Add, 2: Remove, 3: Adjust, 4:Export, 5:Print, 0:Exit): ");
        scanf(" %d", &command);
        if(command == 0){
            break;
        }
        switch(command){
            case 1:
                Add();
                break;
            case 2:
                Remove();
                break;
            case 3:
                Adjust();
                break;
            case 4:
                Export();     
                break;
            case 5:
                Print();
                break;
        }
    }
}


