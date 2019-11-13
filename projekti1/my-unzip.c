#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 80

int main(int argc, char *argv[]){

    if(argc == 1){
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for(int i = 1; i < argc; i++){
    FILE *fp = fopen(argv[i], "rb");
    if(fp==NULL){
        printf("my-unzip: cannot open file\n");
        exit(1);
    }
    char curCh;
    int curInt;
    while(fread(&curInt, sizeof(int), 1, fp)) {        
        fread(&curCh, sizeof(char), 1, fp);

        for(int i = 0; i < curInt; i++){
            printf("%c", curCh);
        }
    }
        fclose(fp); 

    }
        return 0;
}