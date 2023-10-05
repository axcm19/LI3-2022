#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "parse_rides.h"



typedef struct ride{
    char* id;
    char* date;
    char* driver;
    char* user; 
    char* city;
    char* distance;
    char* score_user;
    char* score_driver;
    char* tip;
    char* comment;
} Ride;



/*
----------------------------------------------------------------------------------------------------------
"ride_create" ---> função sem argumentos que cria uma estrutura de Ride com tudo a NULL
----------------------------------------------------------------------------------------------------------
*/

Ride* ride_create(){
    Ride* r = malloc(sizeof(struct ride));
    r->id = NULL;
    r->date = NULL;
    r->driver = NULL;
    r->user = NULL;
    r->city = NULL;
    r->distance = NULL;
    r->score_user = NULL;
    r->score_driver = NULL;
    r->tip = NULL;
    r->comment = NULL;
}

void free_key(gpointer data){
}

void free_ride(gpointer data){
    Ride *ride = (Ride *) data;
    if (ride->id != NULL)free(ride->id);
    if (ride->date != NULL) free(ride->date);
    if (ride->driver != NULL) free(ride->driver);
    if (ride->user != NULL) free(ride->user);
    if (ride->city != NULL) free(ride->city);
    if (ride->distance != NULL) free(ride->distance);
    if (ride->score_user != NULL) free(ride->score_user);
    if (ride->score_driver != NULL) free(ride->score_driver);
    if (ride->tip != NULL) free(ride->tip);
    if (ride->comment != NULL) free(ride->comment);
    free(ride);
}


/*
----------------------------------------------------------------------------------------------------------
"printRide" ---> função que imprime uma estrutura de Ride
----------------------------------------------------------------------------------------------------------
*/

void printRide(Ride* r){
    printf("------RIDE INFO------\n");
    printf("ID: %s\n", r->id);
    printf("DATE: %s\n", r->date);
    printf("DRIVER: %s\n", r->driver);
    printf("USER: %s\n", r->user);
    printf("CITY: %s\n", r->city);
    printf("DISTANCE: %s\n", r->distance);
    printf("SCORE USER: %s\n", r->score_user);
    printf("SCORE DRIVER: %s\n", r->score_driver);
    printf("TIP: %s\n", r->tip);
    printf("COMMENT: %s\n", r->comment);
    printf("\n");
}

/*
----------------------------------------------------------------------------------------------------------
"printFuncHash_Ride" ---> converte printRide em GFunc da Glib
----------------------------------------------------------------------------------------------------------
*/

void printFuncHash_Ride (void* key, void* value, void* data){

    Ride* r = (Ride*)value;
    FILE* fp = (FILE*)data;

    fprintf(fp, "------RIDE INFO------\n");
    fprintf(fp, "ID: %s\n", r->id);
    fprintf(fp, "DATE: %s\n", r->date);
    fprintf(fp, "DRIVER: %s\n", r->driver);
    fprintf(fp, "USER: %s\n", r->user);
    fprintf(fp, "CITY: %s\n", r->city);
    fprintf(fp, "DISTANCE: %s\n", r->distance);
    fprintf(fp, "SCORE USER: %s\n", r->score_user);
    fprintf(fp, "SCORE DRIVER: %s\n", r->score_driver);
    fprintf(fp, "TIP: %s\n", r->tip);
    fprintf(fp, "COMMENT: %s\n", r->comment);

}

/*
----------------------------------------------------------------------------------------------------------
"rides_getID" ---> função que devolve o ID de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getID(Ride* r){
    char* copia = r->id;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getID" ---> função que devolve o date de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getDate(Ride* r){
    char* copia = r->date;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getDriver ---> função que devolve o driver de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getDriver(Ride* r){
    char* copia = r->driver;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getUser ---> função que devolve o user de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getUser(Ride* r){
    char* copia = r->user;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getCity ---> função que devolve a city de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getCity(Ride* r){
    char* copia = r->city;
    return copia;
}


/*
----------------------------------------------------------------------------------------------------------
"rides_getDistance ---> função que devolve a distance de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getDistance(Ride* r){
    char* copia = r->distance;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getScoreUser ---> função que devolve o score user de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getScoreUser(Ride* r){
    char* copia = r->score_user;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getScoreDriver ---> função que devolve o score driver de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getScoreDriver(Ride* r){
    char* copia = r->score_driver;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"rides_getTip ---> função que devolve o tip de uma Ride (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* rides_getTip(Ride* r){
    char* copia = r->tip;
    return copia;
}

//Funções de verificação

/*
----------------------------------------------------------------------------------------------------------
"r_verifyDate ---> Verifica se uma data é válida"
----------------------------------------------------------------------------------------------------------
*/
int r_verifyDate(char* date){ //devolve 1 se a data for válida
    if(((isdigit(date[0])) >0) && ((isdigit(date[1])) >0) && ((isdigit(date[3])) >0) && ((isdigit(date[4])) >0) && ((isdigit(date[6])) >0) && ((isdigit(date[7])) >0) && ((isdigit(date[8])) >0) && ((isdigit(date[9])) >0) && (date[2]=='/') && (date[5]=='/')){
        int dia = (date[0] - '0')*10 + (date[1] - '0')*1;
        int mes = (date[3] - '0')*10 + (date[4] - '0')*1;
        if (dia>=1 && dia<=31 && mes>=1 && mes<=12) return 1; else return 0;
    } 
    else return 0;
}

/*
----------------------------------------------------------------------------------------------------------
"r_verifyDistance ---> Verifica se um valor de distância é válido"
----------------------------------------------------------------------------------------------------------
*/
int r_verifyDistance(char* distance){
    for (int i=0; distance[i] != '\0'; i++) {
        if (!isdigit(distance[i]))
            return 0;
    }

    int num = atoi(distance);
    if (num>0) return 1; else return 0;

}

/*
----------------------------------------------------------------------------------------------------------
"r_verifyScoreOrTip ---> Verifica se um valor de score ou tip é válido"
----------------------------------------------------------------------------------------------------------
*/
int r_verifyScoreOrTIp(char* score){
    if (strlen(score) <= 0 || strlen(score) > 3) return 0;
    int dotCounter = 0;
    for (int i=0; score[i] != '\0'; i++) {
        if (!isdigit(score[i]) && score[i] != '.')
            return 0;
        if(score[i] == '.') dotCounter++;
    }

    if (dotCounter>1) return 0;

    double num = strtod(score, NULL);
    if (num>0) return 1; else return 0;
}

/*
----------------------------------------------------------------------------------------------------------
"parse_file_rides" ---> função que recebe como argumento um ficheiro (neste caso rides.csv). Ela extrai
                        uma linha do csv e cria uma nova instancia de Ride, colocando os elementos extraidos
                        pelo parse nessa estrutura. 
                        De seguida imprime a estrutura Ride como comprovativo de que esta foi de facto criada.
----------------------------------------------------------------------------------------------------------
*/

GHashTable* parse_file_rides(FILE* fp, GHashTable* t){
    // faz o parse no ficheiro dos rides.csv
    int count = 0;
    while(!feof(fp)){
        char* line = NULL;
        ssize_t read;
        size_t len; //Será definido pela funçao getline quando alocar espaço para a string
        while ((read = getline(&line, &len, fp)) != -1) {
            Ride* r = ride_create();

            //-------------------------------------------------
            //ESTE PEDAÇO DE CODIGO COLOCA A INFORMAÇÃO EXTRAIDA
            //DA LINHA NUMA ESTRUTURA DE RIDER

            char* token = NULL;
            char *line2 = line;
            int i = 0;
            char* arr[10];
            while ((token = strsep(&line2, ";")) != NULL){
                arr[i] = token;
                i++;
            }

            if(
                (strlen(arr[0]) >0) &&
                (r_verifyDate(arr[1]) == 1) && (strlen(arr[1]) >0) &&
                (strlen(arr[2]) >0) &&
                (strlen(arr[3]) >0) &&
                (strlen(arr[4]) >0) &&
                (r_verifyDistance(arr[5]) == 1) && (strlen(arr[5]) >0) &&
                (r_verifyScoreOrTIp(arr[6]) == 1) && (strlen(arr[6]) >0) &&
                (r_verifyScoreOrTIp(arr[7]) == 1) && (strlen(arr[7]) >0) &&
                (r_verifyScoreOrTIp(arr[8]) == 1) && (strlen(arr[8]) >0)){

                r->id = strdup(arr[0]);
                r->date = strdup(arr[1]);
                r->driver = strdup(arr[2]);
                r->user = strdup(arr[3]);
                r->city = strdup(arr[4]);
                r->distance = strdup(arr[5]);
                r->score_user = strdup(arr[6]);
                r->score_driver = strdup(arr[7]);
                r->tip = strdup(arr[8]);
                r->comment = strdup(arr[9]);

                //-------------------------------------------------

                g_hash_table_insert (t, r->id, r); 
                count++;
            }
        }
        free(line); // É preciso libertar a memória alocada
    } 
    //printf("Rides criados = %d\n", count);
    //printf("\n");
    return t;
}
