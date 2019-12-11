#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 80


int main(int argc, char *argv[]){

    if(argc == 1){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    if(argc == 2){ 
        size_t n = N;
        char *buffer = (char *)malloc(n * sizeof(char));
        getline(&buffer, &n, stdin);
        if(strstr(buffer, argv[1]) != NULL){
            printf("%s", buffer);
            exit(0);
        }
    }
    else {
        size_t n = N;
        char *buffer = (char *)malloc(n * sizeof(char));

        for(int i = 2; i < argc; i++){
            FILE *fp = fopen(argv[i], "r");
            if(fp==NULL){
                printf("my-grep: cannot open file\n");
                exit(1);
            }
            while(getline(&buffer, &n, fp) != -1) {
            if(strstr(buffer, argv[1]) != NULL){
            printf("%s", buffer);
            }
            }
        }
    }
    return 0;
}

//Lähteet:
//https://c-for-dummies.com/blog/?p=1112
//http://codetrays.blogspot.com/2015/09/implementation-of-grep-command-in-c.html
//https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm