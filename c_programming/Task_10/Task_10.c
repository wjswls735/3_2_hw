#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(){
    
    FILE *fp;
    fp=fopen("list.txt", "r");
    char words[30][100];
    int num[30];
    for(int k=0; k<30; k++){
        num[k]=0;
    }
    int i=0;
    while(1){
        bool flag=false;
        char temp[10];
        if(fscanf(fp, "%s", temp) ==EOF){
            fclose(fp);
            break;
        }
        for(int k=0; k<10; k++){
           if(strcmp(words[k], temp)==0){
               num[k]+=1;
               flag=true;
               break;
           }
        }
        if(flag ==false){
            strcpy(words[i], temp);
            num[i]+=1;
        }
        i++;
    }
    int j=0;
    while(num[j]!=0){
        printf("%s : %d\n", words[j], num[j]);
        j+=1;
    }
    return 0;
}
