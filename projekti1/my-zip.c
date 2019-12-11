#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    if(argc == 1){
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    char curCh, preCh;
    int count = 1;
    for(int i = 1; i < argc; i++){
    FILE *fp = fopen(argv[i], "r");
    if(fp==NULL){
        printf("my-zip: cannot open file\n");
        exit(1);
    }
    preCh = getc(fp); 
    while((curCh = getc(fp)) != EOF)
    {
        if(preCh == curCh) {
            count = count + 1;
   }
   
   else {
       fwrite(&count, sizeof(int), 1, stdout);
       fwrite(&preCh, sizeof(char), 1, stdout);
       count = 1;
   }
        preCh = curCh;
    }
        fclose(fp);
    }

}
//Lähteet:
//https://www.tutorialspoint.com/c_standard_library/c_function_getc.htm
