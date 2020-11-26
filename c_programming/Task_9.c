#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
    bool flag=false;
    for(int i=1; argv[i]!=NULL; i++){
        for(int j=0; j<9; j++){
           if(strncmp(argv[i], planets[j], strlen(planets[j]))==0){
              flag=true;
           }
        }
        if(flag==true){
            printf("%s is a planet\n", argv[i]);
        }
        else
            printf("%s is NOT a planet\n", argv[i]);

        flag=false;
    }
    
    return 0;
}
