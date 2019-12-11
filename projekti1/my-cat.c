#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 80

int main(int argc, char *argv[]){

    if(argc == 1){
        return 0;
    }

    for(int i = 1; i < argc; i++){
        FILE *fp = fopen(argv[i], "r");
        if(fp==NULL){
            printf("my-cat: cannot open file\n");
            exit(1);
        }
        char line[80];
        while(fgets(line, N, fp) != NULL){
        printf("%s", line); 
        }
    }

    return 0;
}
//Lähteet:
//http://cprogrammingwithlinux.blogspot.com/2011/10/c-program-to-simulate-linux-cat-command.html