#include "batch.h"



GHashTable* catalogoUsers(char **argv, GHashTable* t_users){
    char* open_users = malloc(sizeof(strlen(argv[1]) + strlen("users.csv") +1));
    sprintf(open_users, "%s/users.csv", argv[1]);
    FILE* file_users = fopen(open_users, "r");
    t_users = parse_file_users(file_users, t_users);          
    fclose(file_users);
    free(open_users);
    return t_users;
}

GHashTable* catalogoDrivers(char **argv, GHashTable* t_drivers){
    char* open_drivers = malloc(sizeof(strlen(argv[1]) + strlen("drivers.csv") +1));
    sprintf(open_drivers, "%s/drivers.csv", argv[1]);
    FILE* file_drivers = fopen(open_drivers, "r");
    t_drivers = parse_file_drivers(file_drivers, t_drivers);
    fclose(file_drivers);
    free(open_drivers);
    return t_drivers;
}

GHashTable* catalogoRides(char **argv, GHashTable* t_rides){
    char* open_rides = malloc(sizeof(strlen(argv[1]) + strlen("rides.csv") +1));
    sprintf(open_rides, "%s/rides.csv", argv[1]);
    FILE* file_rides = fopen(open_rides, "r");
    t_rides = parse_file_rides(file_rides, t_rides);
    fclose(file_rides);
    free(open_rides);
    return t_rides;
}

void parse_BATCH(FILE* fp, GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides){
    // faz o parse num ficheiro com imputs (exemplo input.txt ou input2.txt)

    //FILE* f_OUTPUT = fopen("./OUTPUTS/batch_OUTPUT.txt", "w");


    while(!feof(fp)){
        char* line = NULL;
        ssize_t read;
        size_t len; // Será definido pela funçao getline quando alocar espaço para a string
        int command = 1;
        while ((read = getline(&line, &len, fp)) != -1) {
            //-------------------------------------------------
            //ESTE PEDAÇO DE CODIGO COLOCA A INFORMAÇÃO EXTRAIDA
            //DA LINHA NUM ARRAY 

            char* token = NULL;
            char* line2 = line;
            int i = 0;
            char* arr[4];
            while ((token = strsep(&line2, " \n")) != NULL){
                arr[i] = token;
                i++;
                //printf("%s\n", token);
            }
            
            
            if(strcmp(arr[0], "1") == 0){
                query_1(arr[1], command, t_users, t_drivers, t_rides);
            }

             if(strcmp(arr[0], "2") == 0){
                query_2(arr[1], command, t_drivers, t_rides);
            }

            else if(strcmp(arr[0], "3") == 0){
                query_3(arr[1], command, t_users, t_rides);
            }

            else if(strcmp(arr[0], "4") == 0){
                query_4(arr[1], command, t_rides, t_drivers);
            }

            else if(strcmp(arr[0], "5") == 0){
                query_5(arr[1], arr[2], command, t_rides, t_drivers);
            }

            else if(strcmp(arr[0], "6") == 0){

                query_6(arr[1], arr[2], arr[3], command, t_rides);
            }

            else if(strcmp(arr[0], "7") == 0){
                query_7(arr[1], arr[2], command, t_rides, t_drivers);
            }

            else if(strcmp(arr[0], "8") == 0){
                query_8(arr[1], arr[2], command, t_rides, t_drivers, t_users);
            }

            else if(strcmp(arr[0], "9") == 0){
                query_9(arr[1], arr[2], command, t_rides);
            }

            command++;
        }

        free(line); // É preciso libertar a memória alocada
    } 

    //fclose(f_OUTPUT);
}