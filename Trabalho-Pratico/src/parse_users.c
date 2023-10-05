#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "parse_users.h"





typedef struct user{
    char* username;
    char* name;
    char* gender;
    char* birth_date;
    char* account_creation;
    char* pay_method;
    char* account_status;
} User;



/*
----------------------------------------------------------------------------------------------------------
"user_create" ---> função sem argumentos que cria uma estrutura de User com tudo a NULL
----------------------------------------------------------------------------------------------------------
*/

User* user_create(){
    User* u = malloc(sizeof(struct user));
    u->username = NULL;
    u->name = NULL;
    u->gender = NULL;
    u->birth_date = NULL;
    u->account_creation = NULL;
    u->pay_method = NULL;
    u->account_status = NULL;
}

void free_user(gpointer data){
    User *user = (User *) data;
    free(user->username);
    free(user->name);
    free(user->gender);
    free(user->birth_date);
    free(user->account_creation);
    free(user->pay_method);
    free(user->account_status);
    free(user);
}

/*
----------------------------------------------------------------------------------------------------------
"user_clone" ---> função que que cria uma estrutura de User através de outra já existente
----------------------------------------------------------------------------------------------------------
*/

User* user_clone(User* u){
    User* clone = malloc(sizeof(struct user));
    clone->username = u->username;
    clone->name = u->name;
    clone->gender = u->gender;
    clone->birth_date = u->birth_date;
    clone->account_creation = u->account_creation;
    clone->pay_method = u->pay_method;
    clone->account_status = u->account_status;
}

/*
----------------------------------------------------------------------------------------------------------
"printUser" ---> função que imprime uma estrutura de User
----------------------------------------------------------------------------------------------------------
*/

void printUser(User* u){
    printf("------USER INFO------\n");
    //printf("USER INFO: %s - %s - %s - %s - %s - %s - %s", u->username, u->name,  u->gender, u->birth_date, u->account_creation, u->pay_method, u->account_status);
    printf("USERNAME: %s\n", u->username);
    printf("NAME: %s\n", u->name);
    printf("GENDER: %s\n", u->gender);
    printf("BIRTH DATE: %s\n", u->birth_date);
    printf("ACCOUNT CREATION DATE: %s\n", u->account_creation);
    printf("PAY METHOD: %s\n", u->pay_method);
    printf("ACCOUNT STATUS: %s\n", u->account_status);
    printf("\n");
}

/*
----------------------------------------------------------------------------------------------------------
"printFuncHash_User" ---> converte printUser em GFunc da Glib
----------------------------------------------------------------------------------------------------------
*/

void printFuncHash_User (void* key, void* value, void* data){

    User* u = (User*)value;
    FILE* fp = (FILE*)data;

    fprintf(fp, "------USER INFO------\n");
    fprintf(fp, "USERNAME: %s\n", u->username);
    fprintf(fp, "NAME: %s\n", u->name);
    fprintf(fp, "GENDER: %s\n", u->gender);
    fprintf(fp, "BIRTH DATE: %s\n", u->birth_date);
    fprintf(fp, "ACCOUNT CREATION DATE: %s\n", u->account_creation);
    fprintf(fp, "PAY METHOD: %s\n", u->pay_method);
    fprintf(fp, "ACCOUNT STATUS: %s\n", u->account_status);

}

/*
----------------------------------------------------------------------------------------------------------
"users_getUsername" ---> função que devolve o username de um User (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* users_getUsername(User* u){
    char* copia = u->username;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"users_getName" ---> função que devolve o nome de um User (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* users_getName(User* u){
    char* copia = u->name;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"users_getGender" ---> função que devolve o gender de um User (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* users_getGender(User* u){
    char* copia = u->gender;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"users_getBirthDate ---> função que devolve a data de nascimento de um User (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* users_getBirthDate(User* u){
    char* copia = u->birth_date;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"users_getAccDate ---> função que devolve a data de criação da conta de um User (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* users_getAccDate(User* u){
    char* copia = u->account_creation;
    return copia;
}

/*
----------------------------------------------------------------------------------------------------------
"users_getStatus ---> função que devolve o status da conta de um User (pode ser necessária em alguma query)
----------------------------------------------------------------------------------------------------------
*/

char* users_getStatus(User* u){
    char* copia = u->account_status;
    return copia;
}

//Funções de verificação

/*
----------------------------------------------------------------------------------------------------------
"u_verifyDate ---> Verifica se uma data é válida"
----------------------------------------------------------------------------------------------------------
*/
int u_verifyDate(char* date){ //devolve 1 se a data for válida
    if(((isdigit(date[0])) >0) && ((isdigit(date[1])) >0) && ((isdigit(date[3])) >0) && ((isdigit(date[4])) >0) && ((isdigit(date[6])) >0) && ((isdigit(date[7])) >0) && ((isdigit(date[8])) >0) && ((isdigit(date[9])) >0) && (date[2]=='/') && (date[5]=='/')){
        int dia = (date[0] - '0')*10 + (date[1] - '0')*1;
        int mes = (date[3] - '0')*10 + (date[4] - '0')*1;
        if (dia>=1 && dia<=31 && mes>=1 && mes<=12) return 1; else return 0;
    } 
    else return 0;
}

/*
----------------------------------------------------------------------------------------------------------
"u_verifyAccStatus ---> Verifica se o status da conta é válido"
----------------------------------------------------------------------------------------------------------
*/
int u_verifyAccStatus(char* accStatus){
    int len = strlen(accStatus);
    if (strncasecmp(accStatus, "inactive\n", len) == 0 || strncasecmp(accStatus, "active\n", len) == 0){
        return 1;
    }
    else return 0;
}

/*
----------------------------------------------------------------------------------------------------------
"parse_file_users" ---> função que recebe como argumento um ficheiro (neste caso users.csv). Ela extrai
                        uma linha do csv e cria uma nova instancia de User, colocando os elementos extraidos
                        pelo parse nessa estrutura. 
                        De seguida imprime a estrutura User como comprovativo de que esta foi de facto criada.
----------------------------------------------------------------------------------------------------------
*/


GHashTable* parse_file_users(FILE* fp, GHashTable* t){
    // faz o parse no ficheiro dos users.csv
    int count = 0;
    while(!feof(fp)){
        char* line = NULL;
        ssize_t read;
        size_t len; // Será definido pela funçao getline quando alocar espaço para a string
        while ((read = getline(&line, &len, fp)) != -1) {
            User* u = user_create();

            //-------------------------------------------------
            //ESTE PEDAÇO DE CODIGO COLOCA A INFORMAÇÃO EXTRAIDA
            //DA LINHA NUMA ESTRUTURA DE USER

            char* token = NULL;
            char *line2 = line;
            int i = 0;
            char* arr[7];
            while ((token = strsep(&line2, ";")) != NULL){
                arr[i] = token;
                i++;
            }

            if(
                (strlen(arr[0]) >0) &&
                (strlen(arr[1]) >0) &&
                (strlen(arr[2]) >0) &&
                (u_verifyDate(arr[3]) == 1) && (strlen(arr[3]) >0) &&
                (u_verifyDate(arr[4]) == 1) && (strlen(arr[4]) >0) &&
                (strlen(arr[5]) >0) && 
                (u_verifyAccStatus(arr[6]) == 1) && (strlen(arr[6]) >0)){ 

                u->username = strdup(arr[0]);
                u->name = strdup(arr[1]);
                u->gender = strdup(arr[2]);
                u->birth_date = strdup(arr[3]);
                u->account_creation = strdup(arr[4]);
                u->pay_method = strdup(arr[5]);
                u->account_status = strdup(arr[6]);

                //-------------------------------------------------

                g_hash_table_insert (t, u->username, u); 
                count++;
            }
        }
        free(line); // É preciso libertar a memória alocada
    } 
    //printf("Users criados = %d\n", count);
    //printf("\n");
    return t;
}
