#include <stdio.h>
#define ERR -2147483644
float operation(char o, float a, float b){
    int answer;
    switch(o){
        case '+': 
            answer=a+b;
            break;
        case '-':
            answer=a-b;
            break;
        case '*':
            answer=a*b;
            break;
        case '/':
            if(b==0){
                printf("cannot be divided by Zero\n");
                answer=ERR;
                return answer;
            }
            else{
                answer=a/b;
                break;
            }
        default : 
            printf("unknow operator\n");
            break;
    }
    return answer;
}
int main()
{
    int type;
    printf("Enter the calculator mode (1:Normal, 2: Extended):");
    scanf("%d", &type);
    
    if(type==1){
        int a, b;
        char o;
        float answer=0;
        printf("Put two integers : ");
        scanf("%d, %d", &a, &b);
        printf("Put the operator : ");
        scanf(" %c", &o);
        answer=operation(o, (float)a, (float)b); 
        if(answer == ERR) return 0;
        printf("The result is %.3f\n", answer);
        return 0;
    }
    if(type==2){
        int a[3];
        char o[2];
        int integer_temp;
        float answer=0;
        printf("Put three integers : ");
        scanf("%d, %d, %d", &a[0], &a[1], &a[2]);
        printf("Put two operator : ");
        scanf(" %c, %c", &o[0], &o[1]);
        if((o[1] == '*' || o[1] =='/') && (o[0]=='+' || o[0]=='-')){
            integer_temp=operation( o[1], (float)a[1], (float)a[2]);
            if(integer_temp == ERR) return 0;
            answer=operation( o[0], (float)a[0], (float)integer_temp);
            if(answer == ERR) return 0;
        }
        else{
            integer_temp=operation(o[0], (float)a[0], (float)a[1]);
            if(integer_temp == ERR) return 0;
            answer=operation(o[1], (float)integer_temp, (float)a[2]);
            if(answer == ERR) return 0;
        }

        printf("The result is %.3f\n", answer);
        return 0;
    }
}


