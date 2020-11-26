#include <stdio.h>

void get_avgsum(int arr[], int num, int *avg, int *max){

    int t_max=0;
    int t_avg=0;
    for(int i=0; i<num; i++){
        t_avg+=arr[i];
        if(t_max<arr[i]){
            t_max=arr[i];
        }
    }
    t_avg/=num;
    *avg=t_avg;
    *max=t_max;

}

void rotate(int *a, int *b, int *c){
    int temp=*a;
    *a=*c;
    *c=*b;
    *b=temp;
}
int main(){
    int arr[10] = {10,20,30,40,50,60,70,80,90,100};

    int avg, max;

    get_avgsum(arr, 10, &avg, &max);

    rotate(&arr[2], &arr[3], &arr[4]);

    printf("Array: ");

    for(int i=0; i<10; i++){
        printf("%d ", arr[i]);
    }
   
    printf ("\nAvg: %d, Max: %d\n", avg, max);
    return 0;
}
