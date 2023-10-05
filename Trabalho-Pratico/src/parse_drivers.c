#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <strings.h>
#include "parse_drivers.h"




typedef struct driver{
    char* id;
    char* name;
    char* birth_date;
    char* gender;
    char* class;
    char* plate;
    char* city;
    char* account_creation;
    char* status;
} Driver;

/*
|------------------------------------------------|
|PREÇO POR CLASSE                                |
|                                                |
| – Basic: Tarifa mínima = 3.25€ + 0.62€/km      |
| – Green: Tarifa mínima = 4.00€ + 0.79€/km      |
| – Premium: Tarifa mínima = 5.20€ + 0.94€/km    |
|------------------------------------------------|

*/

/*
----------------------------------------------------------------------------------------------------------
"driver_create" ---> função sem argumentos que cria uma estrutura de Driver com tudo a NULL
----------------------------------------------------------------------------------------------------------
*/

Driver* driver_create(){
    Driver* d = malloc(sizeof(struct driver));
    d->id = NULL;
    d->name = NULL;
    d->birth_date = NULL;
    d->gender = NULL;
    d->class = NULL;
    d->plate = NULL;
    d->city = NULL;
    d->account_creation = NULL;
    d->status = NULL;
}


void free_driver(gpointer data){
    Driver *driver = (Driver *) data;
    if (driver->id != NULL) free(driver->id);
    if (driver->name != NULL) free(driver->name);
    if (driver->birth_date != NULL) free(driver->birth_date);
    if (driver->gender != NULL) free(driver->gender);
    if (driver->class != NULL) free(driver->class);
    if (driver->plate != NULL) free(driver->plate);
    if (driver->city != NULL) free(driver->city);
    if (driver->account_creation != NULL) free(driver->account_creation);
    if (driver->status != NULL) free(driver->status);
    free(driver);
}

/*
----------------------------------------------------------------------------------------------------------
"printDriver" ---> função que imprime uma estrutura de Driver 
----------------------------------------------------------------------------------------------------------
*/

void printDriver(Driver* d){
    printf("------DRIVER INFO------\n");
    printf("ID: %s\n", d->id);
    printf("NAME: %s\n", d->name);
    printf("BIRTH DATE: %s\n", d->birth_date);
    printf("GENDER: %s\n", d->gender);
    printf("CLASS: %s\n", d->class);
    printf("PLATE: %s\n", d->plate);
    printf("CITY: %s\n", d->city);
    printf("ACCOUNT CREATION DATE: %s\n", d->account_creation);
    printf("STATUS: %s\n", d->status);
    printf("\n");
}

/*
----------------------------------------------------------------------------------------------------------
"printFuncHash_User" ---> converte printUser em GFunc da Glib
----------------------------------------------------------------------------------------------------------
*/

void printFuncHash_Driver (void* key, void* value, void* data){

    Driver* d = (Driver*)value;
    FILE* fp = (FILE*)data;

    fprintf(fp, "------DRIVER INFO------\n");
    fprintf(fp, "ID: %s\n", d->id);
    fprintf(fp, "NAME: %s\n", d->name);
    fprintf(fp, "BIRTH DATE: %s\n", d->birth_date);
    fprintf(fp, "GENDER: %s\n", d->gender);
    fprintf(fp, "CLASS: %s\n", d->class);
    fprintf(fp, "PLATE: %s\n", d->plate);
    fprintf(fp, "CITY: %s\n", d->city);
    fprintf(fp, "ACCOUNT CREATION DATE: %s\n", d->account_creation);
    fprintf(fp, "STATUS: %s\n", d->status);

}

/*
----------------------------------------------------------------------------------------------------------
"drivers_getID" ---> função que devolve o ID de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getID(Driver* d){
    char* copia = d->id;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"drivers_getName" ---> função que devolve o nome de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getName(Driver* d){
    char* copia = d->name;
    return copia;
}
 
/*

/*
----------------------------------------------------------------------------------------------------------
"drivers_getBirthDate" ---> função que devolve a data de nascimento de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getBirthDate(Driver* d){
    char* copia = d->birth_date;
    return copia;
}

/*

/*
----------------------------------------------------------------------------------------------------------
"drivers_getGender" ---> função que devolve o género de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getGender(Driver* d){
    char* copia = d->gender;
    return copia;
}

/*

/*
----------------------------------------------------------------------------------------------------------
"drivers_getClass" ---> função que devolve a class do carro de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getClass(Driver* d){
    char* copia = d->class;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"drivers_getAccDate" ---> função que devolve a data de criação da conta de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getAccDate(Driver* d){
    char* copia = d->account_creation;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"drivers_getStatus" ---> função que devolve o status da conta de um Driver (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* drivers_getStatus(Driver* d){
    char* copia = d->status;
    return copia;
}



//Funções de verificação

/*
----------------------------------------------------------------------------------------------------------
"d_verifyDate ---> Verifica se uma data é válida"
----------------------------------------------------------------------------------------------------------
*/
int d_verifyDate(char* date){ //devolve 1 se a data for válida
    if(((isdigit(date[0])) >0) && ((isdigit(date[1])) >0) && ((isdigit(date[3])) >0) && ((isdigit(date[4])) >0) && ((isdigit(date[6])) >0) && ((isdigit(date[7])) >0) && ((isdigit(date[8])) >0) && ((isdigit(date[9])) >0) && (date[2]=='/') && (date[5]=='/')){
        int dia = (date[0] - '0')*10 + (date[1] - '0')*1;
        int mes = (date[3] - '0')*10 + (date[4] - '0')*1;
        if (dia>=1 && dia<=31 && mes>=1 && mes<=12) return 1; else return 0;
    } 
    else return 0;
}

/*
----------------------------------------------------------------------------------------------------------
"d_verifyClass ---> Verifica se uma class é válida"
----------------------------------------------------------------------------------------------------------
*/
int d_verifyClass(char* class){
    if (strcasecmp(class, "basic") == 0 || strcasecmp(class, "green") == 0 || strcasecmp(class, "premium") == 0) return 1;
    else return 0;
}


/*
----------------------------------------------------------------------------------------------------------
"d_verifyAccStatus ---> Verifica se o status da conta é válido"
----------------------------------------------------------------------------------------------------------
*/
int d_verifyAccStatus(char* accStatus){
    int len = strlen(accStatus);
    
    if (strncasecmp(accStatus, "inactive\n", len) == 0 || strncasecmp(accStatus, "active\n", len) == 0){
        return 1;
    }
   

    else return 0;

}


/*
----------------------------------------------------------------------------------------------------------
"parse_file_drivers" ---> função que recebe como argumento um ficheiro (neste caso drivers.csv). Ela extrai
                          uma linha do csv e cria uma nova instancia de Driver, colocando os elementos extraidos
                          pelo parse nessa estrutura. 
                          De seguida imprime a estrutura Driver como comprovativo de que esta foi de facto criada.
----------------------------------------------------------------------------------------------------------
*/

GHashTable* parse_file_drivers(FILE* fp, GHashTable* t){
    // faz o parse no ficheiro dos drivers.csv
    int count = 0;
    while(!feof(fp)){
        char* line = NULL;
        ssize_t read;
        size_t len; // Será definido pela funçao getline quando alocar espaço para a string
        while ((read = getline(&line, &len, fp)) != -1) {
            Driver* d = driver_create();

            //-------------------------------------------------
            //ESTE PEDAÇO DE CODIGO COLOCA A INFORMAÇÃO EXTRAIDA
            //DA LINHA NUMA ESTRUTURA DE RIDER

            char* token = NULL;
            char *line2 = line;
            int i = 0;
            char* arr[9];
            while ((token = strsep(&line2, ";")) != NULL){
                arr[i] = token;
                i++;
            }

            if(
                (strlen(arr[0]) >0) &&
                (strlen(arr[1]) >0) &&
                (d_verifyDate(arr[2]) == 1) && (strlen(arr[2]) >0) &&
                (strlen(arr[3]) >0) &&
                (d_verifyClass(arr[4]) == 1) && (strlen(arr[4]) >0) &&
                (strlen(arr[5]) >0) &&
                (strlen(arr[6]) >0) &&
                (d_verifyDate(arr[7]) == 1) && (strlen(arr[7]) >0) &&
                (d_verifyAccStatus(arr[8]) == 1) && (strlen(arr[8]) >0)){ 


                d->id = strdup(arr[0]);
                d->name = strdup(arr[1]);
                d->birth_date = strdup(arr[2]);
                d->gender = strdup(arr[3]);
                d->class = strdup(arr[4]);
                d->plate = strdup(arr[5]);
                d->city = strdup(arr[6]);
                d->account_creation = strdup(arr[7]);
                d->status = strdup(arr[8]);

                //-------------------------------------------------

                g_hash_table_insert (t, d->id, d); 
                count++;
            }
        }
        free(line); // É preciso libertar a memória alocada
    } 
    //printf("Drivers criados = %d\n", count);
    //printf("\n");
    return t;
}