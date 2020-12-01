#include <stdio.h>

typedef struct xy{
    int x1;
    int y1;
    int x2;
    int y2;
}XY;

enum Shape {
   LINE = 1,
   RECT = 2
};

int main(){
    enum Shape shape;
    XY Line;
    XY RECT;
    int num;
    while(1){
        printf("Put figure shape (1:Line, 2:RECT, 0:PRINT): ");
        scanf("%d", &shape);
        if(shape ==0){
            break;
        }
        else if(shape ==1){
            printf("Put the coordinate of Point1: ");
            scanf("%d %d", &Line.x1, &Line.y1);

            printf("Put the coordinate of Point2: ");
            scanf("%d %d", &Line.x2, &Line.y2);
        }
        else{
            printf("Put the coordinate of Point1: ");
            scanf("%d %d", &RECT.x1, &RECT.y1);

            printf("Put the coordinate of Point2: ");
            scanf("%d %d", &RECT.x2, &RECT.y2);
        }
    }

    printf("Figure 1: a line from (%d, %d), to (%d, %d)\n", Line.x1, Line.y1, Line.x2, Line.y2);
    printf("Figure 2: a line from (%d, %d), to (%d, %d)\n", RECT.x1, RECT.y1, RECT.x2, RECT.y2);
    return 0;
}



