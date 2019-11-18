#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;
int j;

//Funktio jonka kukin thread suorittaa funktion parametrina thread saa pakattavan tiedoston nimen.
void *do_process(void* file)
{
    char *filename = file;
    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        printf("pzip: cannot open file\n");
        exit(1);
    }
    //Luodaa kaksi dynaamista listaa, joihin tallennetaan pakattavien merkkien toistomäärät ja itse merkit
    int* intList;
    char* charList;
    intList = malloc(sizeof(int));
    charList = malloc(sizeof(char));

    if (intList == NULL || charList == NULL) {
            printf("Memory allocation failed");
            exit(1);
    }

    int position = 0;
    
    char curCh, preCh;
    int count = 1;
    preCh = getc(fp);
    //Käytetään my-zipin pakkauslogiikkaa ja tallennetaan tulokset listoihin.
    while((curCh = getc(fp)) != EOF)
    {
        if(preCh == curCh) {
        count = count + 1;
        }
   
   else {
       intList = realloc(intList, sizeof(int) * (position + 1));
       charList = realloc(charList, sizeof(char)* (position + 1));

        if (intList == NULL || charList == NULL) {
            printf("Memory allocation failed");
            exit(1);
        }

       intList[position] = count;
       charList[position] = preCh;
       position = position + 1;

       count = 1;
    }
        preCh = curCh;
    }
    //Lukitaan thread sen ajaksi, kun pakattu lopputulos tulostetaan stdout:iin
    pthread_mutex_lock(&lock);
    for(int i = 0; i < position; i++){
        fwrite(&intList[i], sizeof(int), 1, stdout);
        fwrite(&charList[i], sizeof(char), 1, stdout);
    }
    fclose(fp);
    free(intList);
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