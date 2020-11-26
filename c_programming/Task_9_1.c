#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
    char names[100];
    char one_name[10];
    int i=0;
    int point=0;
    char ch;
    bool flag=false;
    printf("Enter names:");
    while(1){
        ch = getchar();
        if(ch == '\n') break;
        names[i] = ch;
    }
    names[i++]='\0';
    names[i++]='\n';
    while(1){
        int j=0;
        for(i=point; names[i]!='\0'; i++){
            if(names[i]=='\n') break;
            one_name[j]=names[i];
            j+=1;
        }
        if(names[i]=='\n') break;
        point =i;
        for(i =0; planets[i] !=NULL; i++){
            if(strncmp(one_name, planets[i], strlen(planets[i])) == 0){
                flag = true;
            }
        }

        if(flag==true){
            printf("%s is a planet.\n", one_name);
        }
        else
            printf("%s is NOT a planet.\n", one_name);
        flag=false;
        for(j=0; j<10; j++){
            one_name[j]='\0';
        }

    }
    return 0;
}
