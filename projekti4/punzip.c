#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;
int j;

//Funktio jonka kukin thread suorittaa funktion parametrina thread saa purettavan tiedoston nimen.
void *do_process(void* file)
{
    char *filename = file;
    FILE *fp = fopen(filename, "rb");
    if(fp==NULL){
        printf("punzip: cannot open file\n");
        exit(1);
    }
    char curCh;
    int curInt;
    char* charList;
    charList = malloc(sizeof(char));
    if (charList == NULL) {
            printf("Memory allocation failed");
            exit(1);
    }
    int position = 0;

    while(fread(&curInt, sizeof(int), 1, fp)) {        
        fread(&curCh, sizeof(char), 1, fp);

        for(int i = 0; i < curInt; i++){
            charList = realloc(charList, sizeof(char)* (position + 1));
            charList[position] = curCh;
            position = position + 1;
        }
    }
        fclose(fp); 

    //Lukitaan thread sen ajaksi, kun purettu lopputulos tulostetaan stdout:iin
    pthread_mutex_lock(&lock);
    for(int i = 0; i < position; i++){
        printf("%c", charList[i]);
    }
    free(charList);
    pthread_mutex_unlock(&lock);
    return NULL;
    }

//Luodaan oma thread jokaiselle parametrina annetulle tiedostolle
int main(int argc, char *argv[])
{
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }
    
    for(int i = 1; i < argc; i++){
        pthread_t thread;
        pthread_create(&thread, NULL, do_process, argv[i]);
        pthread_join(thread, NULL);
    }

    return 0;
}