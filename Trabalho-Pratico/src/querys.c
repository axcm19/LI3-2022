#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <ctype.h> // toupper
#include <stdbool.h>
#include "querys.h"
#include <sys/stat.h>
#include <sys/types.h>

typedef struct driver_q2{ //estrutura para drivers usada na q2
    char* id;
    double score_total;
    double nr_rides;
    char* ride_recente;
} Driver_q2;

Driver_q2* driver_create_q2(){
    Driver_q2* d = malloc(sizeof(struct driver_q2));
    d->id = NULL;
    d->score_total = 0;
    d->nr_rides = 0;
    d->ride_recente = NULL;
}

void free_driver_q2(Driver_q2* d){
    if (d->id != NULL) free(d->id);
    if (d->ride_recente != NULL) free(d->ride_recente);
    free(d);
}

typedef struct user_q3{ //estrutura para users usada na q3
    char* username;
    double distance;
    char* ride_recente;
} User_q3;

User_q3* user_create_q3(){
    User_q3* u = malloc(sizeof(struct user_q3));
    u->username = NULL;
    u->distance = 0;
    u->ride_recente = NULL;
}

typedef struct driver_q7{ //estrutura para drivers usada na q7
    char* id;
    double score_total;
    double nr_rides;
} Driver_q7;

Driver_q7* driver_create_q7(){
    Driver_q7* d = malloc(sizeof(struct driver_q7));
    d->id = NULL;
    d->score_total = 0;
    d->nr_rides = 0;
}


typedef struct driver_user_q8{ //estrutura para drivers usada na q8
    char* driver_id;
    char* driver_name;
    char* driver_acc_creation;
    char* user_username;
    char* user_name;
    char* user_acc_creation;
    char* ride_id;
} Driver_user_q8;

Driver_user_q8* driver_user_create_q8(){
    Driver_user_q8* du = malloc(sizeof(struct driver_user_q8));
    du->driver_id = NULL;
    du->driver_name = NULL;
    du->driver_acc_creation = NULL;
    du->user_username = NULL;
    du->user_name = NULL;
    du->user_acc_creation = NULL;
    du->ride_id;
}

void free_Driver_user_q8(Driver_user_q8* d){
    if(d){
        if(d->driver_id) free(d->driver_id);
        if(d->driver_name) free(d->driver_name);
        if(d->driver_acc_creation) free(d->driver_acc_creation);
        if(d->user_username) free(d->user_username);
        if(d->user_name) free(d->user_name);
        if(d->user_acc_creation) free(d->user_acc_creation);
        if(d->ride_id) free(d->ride_id);
        free(d);
    }
}

typedef struct ride_q9{ //estrutura para rides usada na q9
    char* ride_id;
    char* ride_date;
    char* ride_distance;
    char* ride_city;
    char* ride_tip;
} Ride_q9;

Ride_q9* ride_create_q9(){
    Ride_q9* r = malloc(sizeof(struct ride_q9));
    r->ride_id = NULL;
    r->ride_date = NULL;
    r->ride_distance = NULL;
    r->ride_city = NULL;
    r->ride_tip = NULL;
}


/*
--------------------------------------------------------------------------------------------------------------
"compara3Datas" ---> função auxiliar para determinar se uma certa data está dentro do intervalo de tempo dado
--------------------------------------------------------------------------------------------------------------
*/


int compara3Datas(int dia, int mes, int ano, int diaA, int mesA, int anoA, int diaB, int mesB, int anoB){
    int data = dia + mes*100 + ano*2000;
    int dataA = diaA + mesA*100 + anoA*2000; 
    int dataB = diaB + mesB*100 + anoB*2000;

    if(data>=dataA && data<=dataB) return 1; else return 0; 
}


/*
----------------------------------------------------------------------------------------------------------
"compara2Datas" ---> função auxiliar para determinar, entre duas datas, qual a mais recente
----------------------------------------------------------------------------------------------------------
*/


int compara2Datas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2){ //devolve 1 se a data1 for mais recente do que a data 2; devolve -1 se as datas forem iguais; devolve 0 caso a data1 for mais antiga do que a data2
    if (ano1 > ano2) return 1;
    if (ano1 < ano2) return 0;

    if (mes1 > mes2) return 1;
    if (mes1 < mes2) return 0;

    if (dia1 > dia2) return 1;
    if (dia1 < dia2) return 0;

    return -1;
}


/*
----------------------------------------------------------------------------------------------------------
"xOuMaisAnos" ---> função auxiliar para determinar, se uma conta criada em (dia,mes,ano) tem x ou mais anos
----------------------------------------------------------------------------------------------------------
*/


int xOuMaisAnos(int dia, int mes, int ano, int x){ //devolve 1 se a conta tiver x ou mais anos
    
    if ((2022 - ano > x) || (2022-ano == x && mes<10) || (2022-ano == x && mes==10 && dia<=9)) return 1;
    else return 0;
        
}


/*
----------------------------------------------------------------------------------------------------------
"calculaIdade" ---> função auxiliar para calcular a idade de alguém
----------------------------------------------------------------------------------------------------------
*/


int calculaIdade(char* birthDate){ 
    int dia = (birthDate[0] - '0')*10 + (birthDate[1] - '0');
    int mes = (birthDate[3] - '0')*10 + (birthDate[4] - '0');
    int ano = (birthDate[6] - '0')*1000 + (birthDate[7] - '0')*100 + (birthDate[8] - '0')*10 + (birthDate[9] - '0');

    if (mes>10 || mes==10 && dia > 9) return 2022-ano-1;
    else return 2022-ano;
}


/*
----------------------------------------------------------------------------------------------------------
"query_1" ---> função realtiva à 1ª query.
----------------------------------------------------------------------------------------------------------
*/


void query_1(char* ID, int command, GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides){ 
    printf("Executou Query 1 ---> parâmetros: %s\n", ID);
    
    GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList *lista_rides_start = lista_rides;
    //GList* lista_rides_copy = g_list_copy(lista_rides);

    if (((ID[0] == '0') || (ID[0] == '1') || (ID[0] == '2') || (ID[0] == '3') || (ID[0] == '4') || (ID[0] == '5') || (ID[0] == '6') || (ID[0] == '7') || (ID[0] == '8') || (ID[0] == '9')) 
    && (g_hash_table_lookup(t_drivers, ID) != NULL) 
    && (strcasecmp((drivers_getStatus(g_hash_table_lookup(t_drivers, ID))),"active\n")==0)){ //se for um driver com conta ativa na database

        char idade[3];
        int idd  = calculaIdade(drivers_getBirthDate(g_hash_table_lookup(t_drivers, ID))); 
        sprintf(idade, "%d", idd);
        double nr = 0;
        double total_score = 0;
        double preco = 0;
        char* class = drivers_getClass(g_hash_table_lookup(t_drivers, ID)); 
        
        for(; lista_rides != NULL; lista_rides = lista_rides->next){  
            double dist_ride;
            if (strcmp(rides_getDriver(lista_rides->data),ID) == 0){
                nr++;
                dist_ride = atoi(rides_getDistance(lista_rides->data));
                total_score += atoi(rides_getScoreDriver(lista_rides->data));
                if(strcasecmp(class,"basic") == 0) preco += (3.25 + 0.62*dist_ride);
                else if(strcasecmp(class,"green") == 0) preco += (4.00 + 0.79*dist_ride);
                else if(strcasecmp(class,"premium") == 0) preco += (5.20 + 0.94*dist_ride);
                preco += atof(rides_getTip(lista_rides->data));
            } 
        }

        double score = total_score/nr;
        char av_score[10]; 
        sprintf(av_score, "%.3f", score);   
        char total_viagens[10]; 
        sprintf(total_viagens, "%.0f", nr);
        char total_auferido[10]; 
        sprintf(total_auferido, "%.3f", preco);  
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp;
        fp = fopen(output, "w+");
        fputs(drivers_getName(g_hash_table_lookup(t_drivers, ID)), fp);
        fputs(";", fp);
        fputs(drivers_getGender(g_hash_table_lookup(t_drivers, ID)), fp);
        fputs(";", fp);
        fputs(idade, fp);
        fputs(";", fp);
        fputs(av_score, fp);
        fputs(";", fp);
        fputs(total_viagens, fp);
        fputs(";", fp);
        fputs(total_auferido, fp);
        fputs("\n", fp);

        free(output);
        fclose(fp);
        g_list_foreach(lista_rides, (GFunc) free_ride, NULL);

    }
    
    else if ((g_hash_table_lookup(t_users, ID) != NULL) 
        && (strcasecmp((users_getStatus(g_hash_table_lookup(t_users, ID))),"active\n")==0)){ //se for um user com conta ativa na database
            
            char idade[3];
            int idd  = calculaIdade(users_getBirthDate(g_hash_table_lookup(t_users, ID))); 
            sprintf(idade, "%d", idd);
            double nr = 0;
            double gasto = 0;
            double total_score = 0;

            for(; lista_rides != NULL; lista_rides = lista_rides->next){  
                if (strcmp(rides_getUser(lista_rides->data),ID) == 0){
                    nr++;
                    char* driver_id = rides_getDriver(lista_rides->data);
                    char* class = drivers_getClass(g_hash_table_lookup(t_drivers, driver_id)); 
                    double dist_ride = atoi(rides_getDistance(lista_rides->data));
                    total_score += atoi(rides_getScoreUser(lista_rides->data));
                    if(strcasecmp(class,"basic") == 0) gasto += (3.25 + 0.62*dist_ride);
                    else if(strcasecmp(class,"green") == 0) gasto += (4.00 + 0.79*dist_ride);
                    else if(strcasecmp(class,"premium") == 0) gasto += (5.20 + 0.94*dist_ride);
                    gasto+= atof(rides_getTip(lista_rides->data));
                } 
            }

            double score = total_score/nr;

            char av_score[10]; 
            sprintf(av_score, "%.3f", score);   
            char total_viagens[10]; 
            sprintf(total_viagens, "%.0f", nr);
            char total_gasto[10]; 
            sprintf(total_gasto, "%.3f", gasto);  
            char* output = malloc(100);
            sprintf(output, "./Resultados/command%d_output.txt", command);

            FILE *fp;
            fp = fopen(output, "w+");
            fputs(users_getName(g_hash_table_lookup(t_users, ID)), fp);
            fputs(";", fp);
            fputs(users_getGender(g_hash_table_lookup(t_users, ID)), fp);
            fputs(";", fp);
            fputs(idade, fp);
            fputs(";", fp);
            fputs(av_score, fp);
            fputs(";", fp);
            fputs(total_viagens, fp);
            fputs(";", fp);
            fputs(total_gasto, fp);
            fputs("\n", fp);

            fclose(fp);
            free(output);
            g_list_foreach(lista_rides, (GFunc) free_ride, NULL);
        }
        
    else{
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);
        FILE *fp;
        fp = fopen(output, "w+"); 
        fclose(fp);
        free(output);
    }   

    printf("-------------------------------------------------------------------------\n");

    //lista_rides = lista_rides_start;
    //g_list_foreach(lista_rides_copy, (GFunc) free_ride, NULL);
    lista_rides = lista_rides_start;
    g_list_free(lista_rides);
}


//queries 2, 3, 7 e 8 estão certas, mas só funcionam quando os ficheiros são pequenos


/*
----------------------------------------------------------------------------------------------------------
"compara_2" ---> função auxiliar relativa à 2ª query. 
----------------------------------------------------------------------------------------------------------
*/


int compara_2(Driver_q2* driver_info_A, Driver_q2* driver_info_B){ //função para ordenar as rides, segundo os critérios do enunciado

    int diaA = ((driver_info_A->ride_recente)[0] - '0')*10 + ((driver_info_A->ride_recente)[1] - '0'); 
    int mesA = ((driver_info_A->ride_recente)[3] - '0')*10 + ((driver_info_A->ride_recente)[4] - '0');
    int anoA = ((driver_info_A->ride_recente)[6] - '0')*1000 + ((driver_info_A->ride_recente)[7] - '0')*100 + ((driver_info_A->ride_recente)[8] - '0')*10 + ((driver_info_A->ride_recente)[9] - '0');

    int diaB = ((driver_info_B->ride_recente)[0] - '0')*10 + ((driver_info_B->ride_recente)[1] - '0'); 
    int mesB = ((driver_info_B->ride_recente)[3] - '0')*10 + ((driver_info_B->ride_recente)[4] - '0');
    int anoB = ((driver_info_B->ride_recente)[6] - '0')*1000 + ((driver_info_B->ride_recente)[7] - '0')*100 + ((driver_info_B->ride_recente)[8] - '0')*10 + ((driver_info_B->ride_recente)[9] - '0');

    double score_total_A = driver_info_A->score_total;
    double score_total_B = driver_info_B->score_total;

    double nr_rides_A = driver_info_A->nr_rides;
    double nr_rides_B = driver_info_B->nr_rides;

    double av_media_A = score_total_A/nr_rides_A;
    double av_media_B = score_total_B/nr_rides_B;

    if((av_media_A>av_media_B) 
        || ((av_media_A==av_media_B) && ((compara2Datas(diaA,mesA,anoA,diaB,mesB,anoB)) == 1))
        || ((av_media_A==av_media_B) && ((compara2Datas(diaA,mesA,anoA,diaB,mesB,anoB)) == -1) && ((atoi(driver_info_A->id)) < (atoi(driver_info_B->id))))
    ) return -1 ;
    else return 1;
}


/*
----------------------------------------------------------------------------------------------------------
"query_2" ---> função relativa à 2ª query.
----------------------------------------------------------------------------------------------------------
*/


void query_2(char* N, int command, GHashTable* t_drivers, GHashTable* t_rides){
    printf("Executou Query 2 ---> parâmetros: %s\n", N);

    if (strcmp(N, "0")!=0){ 
        GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
        GList *lista_rides_start = lista_rides;
        GList *lista_nova = NULL;
        GList *lista_nova_start = lista_nova;
        int Ntotal = atoi(N);

        GHashTable* driver_info_table = g_hash_table_new(g_str_hash, g_str_equal);
        for(; lista_rides != NULL; lista_rides=lista_rides->next){
            char* driver_id = rides_getDriver(lista_rides->data);
            char* driver_status  = drivers_getStatus(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(driver_status, "active\n") == 0){
                double score_driver = atoi(rides_getScoreDriver(lista_rides->data));
                char* ride_date = rides_getDate(lista_rides->data);
                int diaA = (ride_date[0] - '0')*10 + (ride_date[1] - '0');
                int mesA = (ride_date[3] - '0')*10 + (ride_date[4] - '0');
                int anoA = (ride_date[6] - '0')*1000 + (ride_date[7] - '0')*100 + (ride_date[8] - '0')*10 + (ride_date[9] - '0');

                if ((g_hash_table_lookup(driver_info_table, driver_id)) == NULL){
                    Driver_q2* driver_info = driver_create_q2();
                    driver_info->id = driver_id;
                    driver_info->score_total = score_driver;
                    driver_info->ride_recente = ride_date;  
                    driver_info->nr_rides = 1;
                    g_hash_table_insert(driver_info_table, driver_id, driver_info);
                }
                else{
                    //ir buscar os valores que tavam lá
                    Driver_q2* driver_info = driver_create_q2();
                    driver_info = g_hash_table_lookup(driver_info_table, driver_id);
                    //modificá-los
                    driver_info->score_total += score_driver;
                    driver_info->nr_rides += 1;
                    char* ride_date_B = driver_info->ride_recente;
                    int diaB = (ride_date_B[0] - '0')*10 + (ride_date_B[1] - '0');
                    int mesB = (ride_date_B[3] - '0')*10 + (ride_date_B[4] - '0');
                    int anoB = (ride_date_B[6] - '0')*1000 + (ride_date_B[7] - '0')*100 + (ride_date_B[8] - '0')*10 + (ride_date_B[9] - '0');
                    if (compara2Datas(diaA, mesA, anoA, diaB, mesB, anoB) == 1) driver_info->ride_recente = ride_date;
                    g_hash_table_insert(driver_info_table, driver_id, driver_info);
                }
            }
        }

        GList* lista_driver_info = g_hash_table_get_values(driver_info_table);
        GList* lista_driver_info_start = lista_driver_info;

        for(; lista_driver_info != NULL; lista_driver_info=lista_driver_info->next){
            if ((strcmp(((struct driver_q2*)lista_driver_info->data)->id, "driver"))!=0){

                //ver se a length é menor q N. se sim, inserir. se n: 
                //comparar com o último membro da lista sorted
                //se sim, inserir

                if(g_list_length(lista_nova) < Ntotal){
                    lista_nova = g_list_insert_sorted(lista_nova, lista_driver_info->data, (GCompareFunc)compara_2);
                }
                else{
                    if((compara_2(lista_driver_info->data, (g_list_last(lista_nova))->data)) == -1){
                        lista_nova = g_list_delete_link(lista_nova, g_list_last(lista_nova)); // o remove não está a funcionar
                        lista_nova = g_list_insert_sorted(lista_nova, lista_driver_info->data, (GCompareFunc)compara_2);
                    }
                }
            }
        }

        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp;                                                  
        fp = fopen (output, "w+");

        for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
            Driver_q2* driver_info = driver_create_q2();
            driver_info = lista_nova->data;
            double av_media = (driver_info->score_total)/(driver_info->nr_rides);
            char av_score[10];
            sprintf(av_score, "%.3f", av_media);  
            fputs(driver_info->id, fp);
            fputs(";", fp);
            fputs(drivers_getName(g_hash_table_lookup(t_drivers, driver_info->id)), fp);
            fputs(";", fp);
            fputs(av_score, fp);
            fputs("\n", fp); 
            //free_driver_q2(driver_info);
        }  
        fclose(fp);
        free(output);
        printf("-------------------------------------------------------------------------\n");

        g_hash_table_destroy(driver_info_table);

        lista_rides = lista_rides_start;
        g_list_free(lista_rides);

        lista_driver_info = lista_driver_info_start;
        g_list_free(lista_driver_info);

        lista_nova = lista_nova_start;
        g_list_free(lista_nova);
    }

    else{
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);
        FILE *fp;                                                  
        fp = fopen (output, "w+");
        fclose(fp);
        free(output);
        printf("-------------------------------------------------------------------------\n");
    }
}


/*
----------------------------------------------------------------------------------------------------------
"compara_3" ---> função auxiliar relativa à 3ª query. 
----------------------------------------------------------------------------------------------------------
*/


int compara_3(User_q3* user_info_A, User_q3* user_info_B){ //função para ordenar as rides, segundo os critérios do enunciado

    int diaA = ((user_info_A->ride_recente)[0] - '0')*10 + ((user_info_A->ride_recente)[1] - '0'); 
    int mesA = ((user_info_A->ride_recente)[3] - '0')*10 + ((user_info_A->ride_recente)[4] - '0');
    int anoA = ((user_info_A->ride_recente)[6] - '0')*1000 + ((user_info_A->ride_recente)[7] - '0')*100 + ((user_info_A->ride_recente)[8] - '0')*10 + ((user_info_A->ride_recente)[9] - '0');

    int diaB = ((user_info_B->ride_recente)[0] - '0')*10 + ((user_info_B->ride_recente)[1] - '0'); 
    int mesB = ((user_info_B->ride_recente)[3] - '0')*10 + ((user_info_B->ride_recente)[4] - '0');
    int anoB = ((user_info_B->ride_recente)[6] - '0')*1000 + ((user_info_B->ride_recente)[7] - '0')*100 + ((user_info_B->ride_recente)[8] - '0')*10 + ((user_info_B->ride_recente)[9] - '0');

    if(((user_info_A->distance) > (user_info_B->distance)) 
        || (((user_info_A->distance) == (user_info_B->distance)) && ((compara2Datas(diaA,mesA,anoA,diaB,mesB,anoB)) == 1))
        || (((user_info_A->distance) == (user_info_B->distance)) && ((compara2Datas(diaA,mesA,anoA,diaB,mesB,anoB)) == -1) && (user_info_A->username < user_info_B->username))
    ) return -1 ;
    else return 1;
}


/*
----------------------------------------------------------------------------------------------------------
"query_3" ---> função relativa à 3ª query.
----------------------------------------------------------------------------------------------------------
*/


void query_3(char* N, int command, GHashTable* t_users, GHashTable* t_rides){
    printf("Executou Query 3 ---> parâmetros: %s\n", N);

    if (strcmp(N, "0")!=0){ 
        GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides;  
        GList *lista_rides_start = lista_rides;  
        GList* lista_nova = NULL; 
        GList* lista_nova_start = lista_nova;
        int Ntotal = atoi(N);

        GHashTable* user_info_table = g_hash_table_new(g_str_hash, g_str_equal);
        for(; lista_rides != NULL; lista_rides=lista_rides->next){
            char* username = rides_getUser(lista_rides->data);
            char* user_status = users_getStatus(g_hash_table_lookup(t_users, username));
            if(strcasecmp(user_status, "active\n") == 0){
                double distance = atoi(rides_getDistance(lista_rides->data));
                char* ride_date = rides_getDate(lista_rides->data);
                int diaA = (ride_date[0] - '0')*10 + (ride_date[1] - '0');
                int mesA = (ride_date[3] - '0')*10 + (ride_date[4] - '0');
                int anoA = (ride_date[6] - '0')*1000 + (ride_date[7] - '0')*100 + (ride_date[8] - '0')*10 + (ride_date[9] - '0');

                if ((g_hash_table_lookup(user_info_table, username)) == NULL){
                    User_q3* user_info = user_create_q3();
                    user_info->username = username;
                    user_info->distance = distance;
                    user_info->ride_recente = ride_date;  
                    g_hash_table_insert(user_info_table, username, user_info);
                }
                else{
                    //ir buscar os valores que tavam lá
                    User_q3* user_info = user_create_q3();
                    user_info = g_hash_table_lookup(user_info_table, username);
                    //modificá-los
                    user_info->distance += distance;
                    char* ride_date_B = user_info->ride_recente;
                    int diaB = (ride_date_B[0] - '0')*10 + (ride_date_B[1] - '0');
                    int mesB = (ride_date_B[3] - '0')*10 + (ride_date_B[4] - '0');
                    int anoB = (ride_date_B[6] - '0')*1000 + (ride_date_B[7] - '0')*100 + (ride_date_B[8] - '0')*10 + (ride_date_B[9] - '0');
                    if (compara2Datas(diaA, mesA, anoA, diaB, mesB, anoB) == 1) user_info->ride_recente = ride_date;
                    g_hash_table_insert(user_info_table, username, user_info);
                }
            }
        }

        GList* lista_info_user = g_hash_table_get_values(user_info_table);
        GList* lista_info_user_start = lista_info_user;
        g_hash_table_destroy(user_info_table);

        for(; lista_info_user != NULL; lista_info_user=lista_info_user->next){
            User_q3* user_info = user_create_q3();
            user_info = lista_info_user->data;

            if ((strcmp(user_info->username, "user"))!=0){

                //ver se a length é menor q N. se sim, inserir. se n: 
                //comparar com o último membro da lista sorted
                //se sim, inserir

                if(g_list_length(lista_nova) < Ntotal){
                    lista_nova = g_list_insert_sorted(lista_nova, user_info, (GCompareFunc)compara_3);
                }
                else{
                    if((compara_3(user_info, (g_list_last(lista_nova))->data)) == -1){
                        lista_nova = g_list_delete_link(lista_nova, g_list_last(lista_nova));
                        lista_nova = g_list_insert_sorted(lista_nova, user_info, (GCompareFunc)compara_3);
                    }
                }
            }
        }

        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp;                                                  
        fp = fopen (output, "w+");
        for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
            User_q3* user_info = user_create_q3();
            user_info = lista_nova->data;
            
            char distancia[10]; 
            sprintf(distancia, "%.0f", user_info->distance);  
            fputs(user_info->username, fp);
            fputs(";", fp);
            fputs(users_getName(g_hash_table_lookup(t_users, user_info->username)), fp);
            fputs(";", fp);
            fputs(distancia, fp);
            fputs("\n", fp);
        } 
        fclose(fp);
        free(output);
        printf("-------------------------------------------------------------------------\n");

        lista_rides = lista_rides_start;
        g_list_free(lista_rides);
        lista_nova = lista_nova_start;
        g_list_free(lista_nova);
        lista_info_user = lista_info_user_start;
        g_list_free(lista_info_user);
    }
    else{
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);
        FILE *fp;                                                  
        fp = fopen (output, "w+");    
        fclose(fp);
        free(output);
        printf("-------------------------------------------------------------------------\n");
    }
}


/*
----------------------------------------------------------------------------------------------------------
"query_4" ---> função relativa à 4ª query. 
----------------------------------------------------------------------------------------------------------
*/


void query_4(char* city, int command, GHashTable* t_rides, GHashTable* t_drivers){ 
    
    printf("Executou Query 4 ---> parâmetros: %s\n", city); 

    double preco = 0;
    double nr = 0;
    
    GList *lista_4 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList *lista_4_start = lista_4;
    
    for(; lista_4 != NULL; lista_4 = lista_4->next){  
        char* cityRide = rides_getCity(lista_4->data);
        if ((strcmp(cityRide, city)) == 0){      
            char* driver_id = rides_getDriver(lista_4->data);
            char* class = drivers_getClass(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(class,"basic") == 0) preco += (3.25 + 0.62*atoi(rides_getDistance(lista_4->data)));
            if(strcasecmp(class,"green") == 0) preco += (4.00 + 0.79*atoi(rides_getDistance(lista_4->data)));
            if(strcasecmp(class,"premium") == 0) preco += (5.20 + 0.94*atoi(rides_getDistance(lista_4->data)));
            nr++;
        }
    }
    
    if (nr>0){
        double preco_medio = preco/nr;

        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        char buf[10]; 
        sprintf(buf, "%.3f", preco_medio);     
        
        FILE *fp3;                         
        fp3 = fopen (output, "w+");          
        fputs(buf, fp3);
        fputs("\n", fp3);
        fclose(fp3);
        free(output);
        printf("-------------------------------------------------------------------------\n");

        //lista_4 = lista_4_start;
    }

    else{
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);
        
        FILE *fp3;                         
        fp3 = fopen (output, "w+");          
        fclose(fp3);
        free(output);
        printf("-------------------------------------------------------------------------\n");
    }

    lista_4 = lista_4_start;
    //g_list_foreach(lista_4, (GFunc) free_ride, NULL);
    g_list_free(lista_4);

}


/*

/*
----------------------------------------------------------------------------------------------------------
"query_5" ---> função relativa à 5ª query. 
----------------------------------------------------------------------------------------------------------
*/


void query_5(char* dataA, char* dataB, int command, GHashTable* t_rides, GHashTable* t_drivers){ 
    
    printf("Executou Query 5 ---> parâmetros: %s %s\n", dataA, dataB); 

    double preco = 0;
    double nr = 0;

    int diaA = (dataA[0] - '0')*10 + (dataA[1] - '0');
    int mesA = (dataA[3] - '0')*10 + (dataA[4] - '0');
    int anoA = (dataA[6] - '0')*1000 + (dataA[7] - '0')*100 + (dataA[8] - '0')*10 + (dataA[9] - '0');

    int diaB = (dataB[0] - '0')*10 + (dataB[1] - '0');
    int mesB = (dataB[3] - '0')*10 + (dataB[4] - '0');
    int anoB = (dataB[6] - '0')*1000 + (dataB[7] - '0')*100 + (dataB[8] - '0')*10 + (dataB[9] - '0');
    
    GList *lista_5 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList* lista_5_start = lista_5;
    
    for(; lista_5 != NULL; lista_5 = lista_5->next){  
        char* date = rides_getDate(lista_5->data);
        int dia = (date[0] - '0')*10 + (date[1] - '0'); 
        int mes = (date[3] - '0')*10 + (date[4] - '0');
        int ano = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + + (date[9] - '0');
        if ((compara3Datas(dia, mes, ano, diaA, mesA, anoA, diaB, mesB, anoB)) == 1){
            char* driver_id = rides_getDriver(lista_5->data);
            char* class = drivers_getClass(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(class,"basic") == 0) preco += (3.25 + 0.62*atoi(rides_getDistance(lista_5->data)));
            if(strcasecmp(class,"green") == 0) preco += (4.00 + 0.79*atoi(rides_getDistance(lista_5->data)));
            if(strcasecmp(class,"premium") == 0) preco += (5.20 + 0.94*atoi(rides_getDistance(lista_5->data)));
            nr++;
        }
    }

    if (nr>0){
        double preco_medio = preco/nr;

        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        char buf[10]; 
        sprintf(buf, "%.3f", preco_medio);   
        
        FILE *fp3;                         
        fp3 = fopen (output, "w+");          
        fputs(buf, fp3);
        fputs("\n", fp3);
        fclose(fp3);
        free(output);
        printf("-------------------------------------------------------------------------\n");  
    }

    else{

        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp3;                         
        fp3 = fopen (output, "w+");          
        fclose(fp3);
        free(output);
        printf("-------------------------------------------------------------------------\n");  
    }
    lista_5 = lista_5_start;
    g_list_free(lista_5);


}


/*
----------------------------------------------------------------------------------------------------------
"query_6" ---> função relativa à 6ª query. 
----------------------------------------------------------------------------------------------------------
*/


void query_6(char* city, char* dataA, char* dataB, int command, GHashTable* t_rides){
    printf("Executou Query 6 ---> parâmetros: %s %s %s\n", city, dataA, dataB); 

    double dist = 0;
    double nr = 0;
    
    int diaA = (dataA[0] - '0')*10 + (dataA[1] - '0');
    int mesA = (dataA[3] - '0')*10 + (dataA[4] - '0');
    int anoA = (dataA[6] - '0')*1000 + (dataA[7] - '0')*100 + (dataA[8] - '0')*10 + (dataA[9] - '0');

    int diaB = (dataB[0] - '0')*10 + (dataB[1] - '0');
    int mesB = (dataB[3] - '0')*10 + (dataB[4] - '0');
    int anoB = (dataB[6] - '0')*1000 + (dataB[7] - '0')*100 + (dataB[8] - '0')*10 + (dataB[9] - '0');

    GList *lista_6 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList* lista_6_start = lista_6;
    
    for(; lista_6 != NULL; lista_6 = lista_6->next){  
        char* cityRide = rides_getCity(lista_6->data);
        if ((strcmp(city, cityRide)) == 0){             //verificar se a cidade da viagem corresponde à cidade pedida
            char* date = rides_getDate(lista_6->data);  //converter a data em Int para poder compará-la com as datas-limite
            int dia = (date[0] - '0')*10 + (date[1] - '0'); 
            int mes = (date[3] - '0')*10 + (date[4] - '0');
            int ano = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + + (date[9] - '0');
            if (compara3Datas(dia, mes, ano, diaA, mesA, anoA, diaB, mesB, anoB) == 1){ 
                dist += atoi(rides_getDistance(lista_6->data));
                nr++;
            }
        }
    }
    
    if(nr>0){
        double r = dist/nr;

        char buf[10]; 
        sprintf(buf, "%.3f", r);      
        
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp2;                                           
        fp2 = fopen (output, "w+");          
        fputs(buf, fp2);
        fputs("\n", fp2);

        fclose(fp2);
        free(output);
        printf("-------------------------------------------------------------------------\n");
    }

    else{
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp2;                                           
        fp2 = fopen (output, "w+");          
        fclose(fp2);
        free(output);
        printf("-------------------------------------------------------------------------\n");
    }
    lista_6 = lista_6_start;
    g_list_free(lista_6); 

}

/*


/*
----------------------------------------------------------------------------------------------------------
"compara_7" ---> função auxiliar relativa à 7ª query. 
----------------------------------------------------------------------------------------------------------
*/


int compara_7(Driver_q7* driver_info_A, Driver_q7* driver_info_B){ //função para ordenar as rides, segundo os critérios do enunciado

    double score_total_A = driver_info_A->score_total;
    double score_total_B = driver_info_B->score_total;

    double nr_rides_A = driver_info_A->nr_rides;
    double nr_rides_B = driver_info_B->nr_rides;

    double av_media_A = score_total_A/nr_rides_A;
    double av_media_B = score_total_B/nr_rides_B;

    if((av_media_A>av_media_B) 
        || ((av_media_A==av_media_B) && ((atoi(driver_info_A->id)) > (atoi(driver_info_B->id))))
    ) return -1 ;
    else return 1;
}


/*
----------------------------------------------------------------------------------------------------------
"query_7" ---> função relativa à 7ª query.
----------------------------------------------------------------------------------------------------------
*/


void query_7(char* N, char* city, int command, GHashTable* t_rides, GHashTable* t_drivers){
    printf("Executou Query 7 ---> parâmetros: %s %s\n", N, city);

    if (strcmp(N, "0")!=0){ 
    
        GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
        GList *lista_rides_start = lista_rides;
        GList *lista_nova = NULL;
        GList *lista_nova_start = lista_nova;

        int Ntotal = atoi(N);

        GHashTable* driver_info_table = g_hash_table_new(g_str_hash, g_str_equal);

        for(; lista_rides != NULL; lista_rides=lista_rides->next){
            char* cityRide = rides_getCity(lista_rides->data);
            if ((strcmp(cityRide, city)) == 0){     
                char* driver_id = rides_getDriver(lista_rides->data);
                char* driver_status  = drivers_getStatus(g_hash_table_lookup(t_drivers, driver_id));
                if(strcasecmp(driver_status, "active\n") == 0){
                    double score_driver = atoi(rides_getScoreDriver(lista_rides->data));
                    if ((g_hash_table_lookup(driver_info_table, driver_id)) == NULL){
                        Driver_q7* driver_info = driver_create_q7();
                        driver_info->id = driver_id;
                        driver_info->score_total = score_driver;
                        driver_info->nr_rides = 1;
                        g_hash_table_insert(driver_info_table, driver_id, driver_info);
                    }
                    else{
                        //ir buscar os valores que tavam lá
                        Driver_q7* driver_info = driver_create_q7();
                        driver_info = g_hash_table_lookup(driver_info_table, driver_id);
                        //modificá-los
                        driver_info->score_total += score_driver;
                        driver_info->nr_rides += 1;
                        g_hash_table_insert(driver_info_table, driver_id, driver_info);
                    }
                }
            }
        }

        GList* lista = g_hash_table_get_values(driver_info_table);
        GList* lista_start = lista;
        g_hash_table_destroy(driver_info_table);

        for(; lista != NULL; lista=lista->next){
            Driver_q7* driver_info = driver_create_q7();
            driver_info = lista->data;

            if ((strcmp(driver_info->id, "driver"))!=0){

                //ver se a length é menor q N. se sim, inserir. se n: 
                //comparar com o último membro da lista sorted
                //se sim, inserir

                if(g_list_length(lista_nova) < Ntotal){
                    lista_nova = g_list_insert_sorted(lista_nova, driver_info, (GCompareFunc)compara_7);
                }
                else{
                    if((compara_7(driver_info, (g_list_last(lista_nova))->data)) == -1){
                        lista_nova = g_list_delete_link(lista_nova, g_list_last(lista_nova)); // o remove não está a funcionar
                        lista_nova = g_list_insert_sorted(lista_nova, driver_info, (GCompareFunc)compara_7);
                    }
                }
            }
        }


        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);

        FILE *fp;                                                  
        fp = fopen (output, "w+");
        int i = 0;     
             
        for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
            Driver_q7* driver_info = driver_create_q7();
            driver_info = lista_nova->data;
            double av_media = (driver_info->score_total)/(driver_info->nr_rides);
            char av_score[10];

            sprintf(av_score, "%.3f", av_media);  

            fputs(driver_info->id, fp);
            fputs(";", fp);
            fputs(drivers_getName(g_hash_table_lookup(t_drivers, driver_info->id)), fp);
            fputs(";", fp);
            fputs(av_score, fp);
            fputs("\n", fp);
            
        }
            
        fclose(fp);
        free(output);
        printf("-------------------------------------------------------------------------\n");

        lista_rides = lista_rides_start;
        g_list_free(lista_rides);
        lista_nova = lista_nova_start;
        g_list_free(lista_nova);
        lista = lista_start;
        g_list_free(lista);
    }

    else{
        char* output = malloc(100);
        sprintf(output, "./Resultados/command%d_output.txt", command);
        FILE *fp;                                                  
        fp = fopen (output, "w+");
        fclose(fp);
        free(output);
        printf("-------------------------------------------------------------------------\n");
    }
}


/*
----------------------------------------------------------------------------------------------------------
"compara_8" ---> função auxiliar relativa à 8ª query. 
----------------------------------------------------------------------------------------------------------
*/


int compara_8(Driver_user_q8* driver_user_info_A, Driver_user_q8* driver_user_info_B){ //função para ordenar as rides, segundo os critérios do enunciado
    char* driver_acc_date_A = driver_user_info_A->driver_acc_creation;
    char* user_acc_date_A = driver_user_info_A->user_acc_creation;
    char* driver_acc_date_B = driver_user_info_B->driver_acc_creation;
    char* user_acc_date_B = driver_user_info_B->user_acc_creation;

    char* ride_id_A = driver_user_info_A->ride_id;
    char* ride_id_B = driver_user_info_B->ride_id;

    int driver_diaA = (driver_acc_date_A[0] - '0')*10 + (driver_acc_date_A[1] - '0');
    int driver_mesA = (driver_acc_date_A[3] - '0')*10 + (driver_acc_date_A[4] - '0');
    int driver_anoA = (driver_acc_date_A[6] - '0')*1000 + (driver_acc_date_A[7] - '0')*100 + (driver_acc_date_A[8] - '0')*10 + (driver_acc_date_A[9] - '0');

    int user_diaA = (user_acc_date_A[0] - '0')*10 + (user_acc_date_A[1] - '0');
    int user_mesA = (user_acc_date_A[3] - '0')*10 + (user_acc_date_A[4] - '0');
    int user_anoA = (user_acc_date_A[6] - '0')*1000 + (user_acc_date_A[7] - '0')*100 + (user_acc_date_A[8] - '0')*10 + (user_acc_date_A[9] - '0');

    int driver_diaB = (driver_acc_date_B[0] - '0')*10 + (driver_acc_date_B[1] - '0');
    int driver_mesB = (driver_acc_date_B[3] - '0')*10 + (driver_acc_date_B[4] - '0');
    int driver_anoB = (driver_acc_date_B[6] - '0')*1000 + (driver_acc_date_B[7] - '0')*100 + (driver_acc_date_B[8] - '0')*10 + (driver_acc_date_B[9] - '0');

    int user_diaB = (user_acc_date_B[0] - '0')*10 + (user_acc_date_B[1] - '0');
    int user_mesB = (user_acc_date_B[3] - '0')*10 + (user_acc_date_B[4] - '0');
    int user_anoB = (user_acc_date_B[6] - '0')*1000 + (user_acc_date_B[7] - '0')*100 + (user_acc_date_B[8] - '0')*10 + (user_acc_date_B[9] - '0');

    if (((compara2Datas(driver_diaA, driver_mesA, driver_anoA, driver_diaB, driver_mesB, driver_anoB)) == 0)
        || (((compara2Datas(driver_diaA, driver_mesA, driver_anoA, driver_diaB, driver_mesB, driver_anoB)) == -1) && (((compara2Datas(user_diaA, user_mesA, user_anoA, user_diaB, user_mesB, user_anoB)) == 0)))
        || (((compara2Datas(driver_diaA, driver_mesA, driver_anoA, driver_diaB, driver_mesB, driver_anoB)) == -1) && (((compara2Datas(user_diaA, user_mesA, user_anoA, user_diaB, user_mesB, user_anoB)) == -1)) && (atoi(ride_id_A) < atoi(ride_id_B)))
    ) return -1; else return 1;
}


/*
----------------------------------------------------------------------------------------------------------
"query_8" ---> função relativa à 8ª query. 
----------------------------------------------------------------------------------------------------------
*/


void query_8(char* gender, char* x_years, int command, GHashTable* t_rides, GHashTable* t_drivers, GHashTable* t_users){
    printf("Executou Query 8 ---> parâmetros: %s %s\n", gender, x_years); 

    GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList *lista_rides_start = lista_rides;

    int ano = atoi(x_years);

    GList* lista_nova = NULL;  
    GList* lista_nova_start = lista_nova;
    
    for(; lista_rides != NULL; lista_rides=lista_rides->next){
        char* username = rides_getUser(lista_rides->data);
        char* user_status = users_getStatus(g_hash_table_lookup(t_users, username));
        char* driver_ID =  rides_getDriver(lista_rides->data);
        char* driver_status  = drivers_getStatus(g_hash_table_lookup(t_drivers, driver_ID));
        //comparar os generos
        if(strcmp(username, "user") != 0 && (strcasecmp(user_status, "active\n") == 0) && (strcasecmp(driver_status, "active\n") == 0)){
            char* user_gender = users_getGender(g_hash_table_lookup(t_users,username));   //AQUI
            char* driver_gender =  drivers_getGender(g_hash_table_lookup(t_drivers,driver_ID));
            //comparar idade das contas

            char* user_acc_creation = users_getAccDate(g_hash_table_lookup(t_users,username));
            char* driver_acc_creation = drivers_getAccDate(g_hash_table_lookup(t_drivers,driver_ID));

            int diaU = (user_acc_creation[0] - '0')*10 + (user_acc_creation[1] - '0');
            int mesU = (user_acc_creation[3] - '0')*10 + (user_acc_creation[4] - '0');
            int anoU = (user_acc_creation[6] - '0')*1000 + (user_acc_creation[7] - '0')*100 + (user_acc_creation[8] - '0')*10 + (user_acc_creation[9] - '0');

            int diaD = (driver_acc_creation[0] - '0')*10 + (driver_acc_creation[1] - '0');
            int mesD = (driver_acc_creation[3] - '0')*10 + (driver_acc_creation[4] - '0');
            int anoD = (driver_acc_creation[6] - '0')*1000 + (driver_acc_creation[7] - '0')*100 + (driver_acc_creation[8] - '0')*10 + (driver_acc_creation[9] - '0');
            
            if ((strcmp(user_gender, gender) == 0) && (strcmp(driver_gender, gender) == 0) && (xOuMaisAnos(diaU,mesU,anoU,ano) == 1) && (xOuMaisAnos(diaD,mesD,anoD,ano) == 1)){
                Driver_user_q8* driver_user_info = driver_user_create_q8();
                driver_user_info->driver_id = driver_ID;
                driver_user_info->driver_name = drivers_getName(g_hash_table_lookup(t_drivers,driver_ID));
                driver_user_info->driver_acc_creation = drivers_getAccDate(g_hash_table_lookup(t_drivers,driver_ID));
                driver_user_info->user_username = username;
                driver_user_info->user_name = users_getName(g_hash_table_lookup(t_users,username));
                driver_user_info->user_acc_creation = users_getAccDate(g_hash_table_lookup(t_users,username));
                driver_user_info->ride_id = rides_getID(lista_rides->data);

                lista_nova = g_list_insert_sorted(lista_nova, driver_user_info, (GCompareFunc)compara_8);
            }
        }
        
    }

    char* output = malloc(100);
    sprintf(output, "./Resultados/command%d_output.txt", command);

    FILE *fp;                                                  
    fp = fopen (output, "w+");
    int i = 0;              
    for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
        fputs(((Driver_user_q8*)(lista_nova->data))->driver_id, fp);
        fputs(";", fp);
        fputs(((Driver_user_q8*)(lista_nova->data))->driver_name, fp);
        fputs(";", fp);
        fputs(((Driver_user_q8*)(lista_nova->data))->user_username, fp);
        fputs(";", fp);
        fputs(((Driver_user_q8*)(lista_nova->data))->user_name, fp);
        fputs("\n", fp);
    }
        
    fclose(fp);
    free(output);
    printf("-------------------------------------------------------------------------\n");

    lista_rides = lista_rides_start;
    g_list_free(lista_rides);

    lista_nova = lista_nova_start;
    g_list_foreach(lista_rides, (GFunc) free_Driver_user_q8, NULL);
    g_list_free(lista_nova);   
}


/*
----------------------------------------------------------------------------------------------------------
"compara_9" ---> função auxiliar relativa à 9ª query. 
----------------------------------------------------------------------------------------------------------
*/


int compara_9(Ride_q9* rideA, Ride_q9* rideB){ //função para ordenar as rides, segundo os critérios do enunciado
    char* dateA = rideA->ride_date;
    char* dateB = rideB->ride_date;

    //memcpy(rides_getDate(rideA),dateA,15);
    //memcpy(rides_getDate(rideB),dateB,15);

    int diaA = (dateA[0] - '0')*10 + (dateA[1] - '0'); 
    int mesA = (dateA[3] - '0')*10 + (dateA[4] - '0');
    int anoA = (dateA[6] - '0')*1000 + (dateA[7] - '0')*100 + (dateA[8] - '0')*10 + (dateA[9] - '0');

    int diaB = (dateB[0] - '0')*10 + (dateB[1] - '0'); 
    int mesB = (dateB[3] - '0')*10 + (dateB[4] - '0');
    int anoB = (dateB[6] - '0')*1000 + (dateB[7] - '0')*100 + (dateB[8] - '0')*10 + (dateB[9] - '0');

    if( (atoi(rideA->ride_distance) > atoi(rideB->ride_distance))  
        || ((atoi(rideA->ride_distance) == atoi(rideB->ride_distance)) && ((compara2Datas(diaA, mesA, anoA, diaB, mesB, anoB)== 1)))
        || ((atoi(rideA->ride_distance) == atoi(rideB->ride_distance)) && ((compara2Datas(diaA, mesA, anoA, diaB, mesB, anoB)== -1)) && (atoi(rideA->ride_id) > atoi(rideB->ride_id)))
    ) return -1; 
    else return 1; 
}


/*
----------------------------------------------------------------------------------------------------------
"query_9" ---> função relativa à 9ª query. 
----------------------------------------------------------------------------------------------------------
*/


void query_9(char* dataA, char* dataB,  int command, GHashTable* t_rides){ 
    printf("Executou Query 9 ---> parâmetros: %s %s\n", dataA, dataB); 

    int diaA = (dataA[0] - '0')*10 + (dataA[1] - '0'); //converter as datas em int de forma a poder compará-las
    int mesA = (dataA[3] - '0')*10 + (dataA[4] - '0');
    int anoA = (dataA[6] - '0')*1000 + (dataA[7] - '0')*100 + (dataA[8] - '0')*10 + (dataA[9] - '0');

    int diaB = (dataB[0] - '0')*10 + (dataB[1] - '0');
    int mesB = (dataB[3] - '0')*10 + (dataB[4] - '0');
    int anoB = (dataB[6] - '0')*1000 + (dataB[7] - '0')*100 + (dataB[8] - '0')*10 + (dataB[9] - '0');

    GList *lista_9 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList *lista_9_start = lista_9;
    GList *lista_nova_9 = NULL; //criar uma lista onde serão inseridas as rides que corresponderem aos parâmetros
    GList *lista_nova_9_start = lista_nova_9;

    for(; lista_9 != NULL; lista_9 = lista_9->next){  
        char* tip = rides_getTip(lista_9->data);
        if ((strcmp(tip, "0.0")) != 0){                      //verificar se houve tip
            char* date =
             rides_getDate(lista_9->data);       //converter a data em Int para poder compará-la com as datas limite
            int dia = (date[0] - '0')*10 + (date[1] - '0'); 
            int mes = (date[3] - '0')*10 + (date[4] - '0');
            int ano = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + + (date[9] - '0');
            if (compara3Datas(dia, mes, ano, diaA, mesA, anoA, diaB, mesB, anoB) == 1){   //se estiver dentro das datas limite, adicionar à lista_nova_9
                Ride_q9* ride_info = ride_create_q9();
                ride_info->ride_id = rides_getID(lista_9->data);
                ride_info->ride_date = date;
                ride_info->ride_distance = rides_getDistance(lista_9->data);
                ride_info->ride_city = rides_getCity(lista_9->data);
                ride_info->ride_tip = tip;

                lista_nova_9 = g_list_insert_sorted(lista_nova_9, ride_info, (GCompareFunc)compara_9);
            }
        }
    }


    char* output = malloc(100);
    sprintf(output, "./Resultados/command%d_output.txt", command);

    FILE *fp2;                                                  
    fp2 = fopen (output, "w+");              
    for(; lista_nova_9 != NULL; lista_nova_9 = lista_nova_9->next){ 
        fputs(((Ride_q9*)lista_nova_9->data)->ride_id, fp2);
        fputs(";", fp2);
        fputs(((Ride_q9*)lista_nova_9->data)->ride_date, fp2);
        fputs(";", fp2);
        fputs(((Ride_q9*)lista_nova_9->data)->ride_distance, fp2);
        fputs(";", fp2);
        fputs(((Ride_q9*)lista_nova_9->data)->ride_city, fp2);
        fputs(";", fp2);
        fputs(((Ride_q9*)lista_nova_9->data)->ride_tip, fp2);
        if((strlen(((Ride_q9*)lista_nova_9->data)->ride_tip)) == 3) fputs("00",fp2);        //para manter as casas decimais certas
        else if ((strlen(((Ride_q9*)lista_nova_9->data)->ride_tip)) == 4) fputs("0",fp2);   
        fputs("\n", fp2);
    }
        
    fclose(fp2);
    free(output);

    printf("-------------------------------------------------------------------------\n");

    lista_9 = lista_9_start;
    g_list_free(lista_9);
    lista_nova_9 = lista_nova_9_start;
    g_list_free(lista_nova_9);
}
















/*
#############################################################################################################################################
                                                        QUERYS PARA MODO INTERATIVO
#############################################################################################################################################
*/
















/*
----------------------------------------------------------------------------------------------------------
"query_1_INTERATIVA" ---> função realtiva à 1ª query no modo interativo.
----------------------------------------------------------------------------------------------------------
*/


void query_1_INTERATIVA(char* ID, GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides){
    printf("-------------------------------------------------------------------------\n"); 
    printf("Executou Query 1 ---> parâmetros: %s\n", ID);
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    
    
    GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides

    if (((ID[0] == '0') || (ID[0] == '1') || (ID[0] == '2') || (ID[0] == '3') || (ID[0] == '4') || (ID[0] == '5') || (ID[0] == '6') || (ID[0] == '7') || (ID[0] == '8') || (ID[0] == '9')) 
    && (g_hash_table_lookup(t_drivers, ID) != NULL) 
    && (strcasecmp((drivers_getStatus(g_hash_table_lookup(t_drivers, ID))),"active\n")==0)){ //se for um driver com conta ativa na database

        char idade[3];
        int idd  = calculaIdade(drivers_getBirthDate(g_hash_table_lookup(t_drivers, ID))); 
        sprintf(idade, "%d", idd);
        double nr = 0;
        double total_score = 0;
        double preco = 0;
        char* class = drivers_getClass(g_hash_table_lookup(t_drivers, ID)); 
        
        for(; lista_rides != NULL; lista_rides = lista_rides->next){  
            double dist_ride;
            if (strcmp(rides_getDriver(lista_rides->data),ID) == 0){
                nr++;
                dist_ride = atoi(rides_getDistance(lista_rides->data));
                total_score += atoi(rides_getScoreDriver(lista_rides->data));
                if(strcasecmp(class,"basic") == 0) preco += (3.25 + 0.62*dist_ride);
                else if(strcasecmp(class,"green") == 0) preco += (4.00 + 0.79*dist_ride);
                else if(strcasecmp(class,"premium") == 0) preco += (5.20 + 0.94*dist_ride);
                preco += atof(rides_getTip(lista_rides->data));
            } 
        }
        
        double score = total_score/nr;
        char av_score[10]; 
        sprintf(av_score, "%.3f", score);   
        char total_viagens[10]; 
        sprintf(total_viagens, "%.0f", nr);
        char total_auferido[10]; 
        sprintf(total_auferido, "%.3f", preco);  
        

        printf("Nome (Condutor) --->  "); puts(drivers_getName(g_hash_table_lookup(t_drivers, ID)));
        printf("Género --->  "); puts(drivers_getGender(g_hash_table_lookup(t_drivers, ID)));
        printf("Idade --->  "); puts(idade);
        printf("Avaliação Média --->  "); puts(av_score);
        printf("Total Viagens --->  "); puts(total_viagens);
        printf("Total Gasto --->  "); puts(total_auferido);
        puts("\n");

    }
    
    else if ((g_hash_table_lookup(t_users, ID) != NULL) 
        && (strcasecmp((users_getStatus(g_hash_table_lookup(t_users, ID))),"active\n")==0)){ //se for um user com conta ativa na database
            
            char idade[3];
            int idd  = calculaIdade(users_getBirthDate(g_hash_table_lookup(t_users, ID))); 
            sprintf(idade, "%d", idd);
            double nr = 0;
            double gasto = 0;
            double total_score = 0;

            for(; lista_rides != NULL; lista_rides = lista_rides->next){  
                if (strcmp(rides_getUser(lista_rides->data),ID) == 0){
                    nr++;
                    char* driver_id = rides_getDriver(lista_rides->data);
                    char* class = drivers_getClass(g_hash_table_lookup(t_drivers, driver_id)); 
                    double dist_ride = atoi(rides_getDistance(lista_rides->data));
                    total_score += atoi(rides_getScoreUser(lista_rides->data));
                    if(strcasecmp(class,"basic") == 0) gasto += (3.25 + 0.62*dist_ride);
                    else if(strcasecmp(class,"green") == 0) gasto += (4.00 + 0.79*dist_ride);
                    else if(strcasecmp(class,"premium") == 0) gasto += (5.20 + 0.94*dist_ride);
                    gasto+= atof(rides_getTip(lista_rides->data));
                } 
            }

            double score = total_score/nr;

            char av_score[10]; 
            sprintf(av_score, "%.3f", score);   
            char total_viagens[10]; 
            sprintf(total_viagens, "%.0f", nr);
            char total_gasto[10]; 
            sprintf(total_gasto, "%.3f", gasto);  

            
            printf("Nome (Utilizador) --->  "); puts(users_getName(g_hash_table_lookup(t_users, ID)));
            printf("Género --->  "); puts(users_getGender(g_hash_table_lookup(t_users, ID)));
            printf("Idade --->  "); puts(idade);
            printf("Avaliação Média --->  "); puts(av_score);
            printf("Total Viagens --->  "); puts(total_viagens);
            printf("Total Gasto --->  "); puts(total_gasto);
            puts("\n");

        }
        
    else{
        puts("ERRO");
    }   

    g_list_free(lista_rides); 

  
}


/*
----------------------------------------------------------------------------------------------------------
"query_2_INTERATIVA" ---> função relativa à 2ª query no modo interativo
----------------------------------------------------------------------------------------------------------
*/


void query_2_INTERATIVA(char* N, GHashTable* t_drivers, GHashTable* t_rides){
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 2 ---> parâmetros: %s\n", N);
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    if (strcmp(N, "0")!=0){ 
        GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
        GList* lista_nova = NULL;
        int Ntotal = atoi(N);
        
        GHashTable* driver_info_table = g_hash_table_new(g_str_hash, g_str_equal);
        for(; lista_rides != NULL; lista_rides=lista_rides->next){
            char* driver_id = rides_getDriver(lista_rides->data);
            char* driver_status  = drivers_getStatus(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(driver_status, "active\n") == 0){
                double score_driver = atoi(rides_getScoreDriver(lista_rides->data));
                char* ride_date = rides_getDate(lista_rides->data);
                int diaA = (ride_date[0] - '0')*10 + (ride_date[1] - '0');
                int mesA = (ride_date[3] - '0')*10 + (ride_date[4] - '0');
                int anoA = (ride_date[6] - '0')*1000 + (ride_date[7] - '0')*100 + (ride_date[8] - '0')*10 + (ride_date[9] - '0');

                if ((g_hash_table_lookup(driver_info_table, driver_id)) == NULL){
                    Driver_q2* driver_info = driver_create_q2();
                    driver_info->id = driver_id;
                    driver_info->score_total = score_driver;
                    driver_info->ride_recente = ride_date;  
                    driver_info->nr_rides = 1;
                    g_hash_table_insert(driver_info_table, driver_id, driver_info);
                }
                else{
                    //ir buscar os valores que tavam lá
                    Driver_q2* driver_info = driver_create_q2();
                    driver_info = g_hash_table_lookup(driver_info_table, driver_id);
                    //modificá-los
                    driver_info->score_total += score_driver;
                    driver_info->nr_rides += 1;
                    char* ride_date_B = driver_info->ride_recente;
                    int diaB = (ride_date_B[0] - '0')*10 + (ride_date_B[1] - '0');
                    int mesB = (ride_date_B[3] - '0')*10 + (ride_date_B[4] - '0');
                    int anoB = (ride_date_B[6] - '0')*1000 + (ride_date_B[7] - '0')*100 + (ride_date_B[8] - '0')*10 + (ride_date_B[9] - '0');
                    if (compara2Datas(diaA, mesA, anoA, diaB, mesB, anoB) == 1) driver_info->ride_recente = ride_date;
                    g_hash_table_insert(driver_info_table, driver_id, driver_info);
                }
            }
        }

        GList* lista_driver_info = g_hash_table_get_values(driver_info_table);
        for(; lista_driver_info != NULL; lista_driver_info=lista_driver_info->next){
            Driver_q2* driver_info = driver_create_q2();
            driver_info = lista_driver_info->data;

            if ((strcmp(driver_info->id, "driver"))!=0){

                //ver se a length é menor q N. se sim, inserir. se n: 
                //comparar com o último membro da lista sorted
                //se sim, inserir

                if(g_list_length(lista_nova) < Ntotal){
                    lista_nova = g_list_insert_sorted(lista_nova, driver_info, (GCompareFunc)compara_2);
                }
                else{
                    if((compara_2(driver_info, (g_list_last(lista_nova))->data)) == -1){

                        lista_nova = g_list_delete_link(lista_nova, g_list_last(lista_nova)); // o remove não está a funcionar
                        lista_nova = g_list_insert_sorted(lista_nova, driver_info, (GCompareFunc)compara_2);
                    }
                }
            }
        }

        
        for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
            Driver_q2* driver_info = driver_create_q2();
            driver_info = lista_nova->data;
            double av_media = (driver_info->score_total)/(driver_info->nr_rides);
            char av_score[10];
            sprintf(av_score, "%.3f", av_media); 
            
            printf("ID (Condutor) --->  "); puts(driver_info->id);
            printf("Nome --->  "); puts(drivers_getName(g_hash_table_lookup(t_drivers, driver_info->id)));
            printf("Avaliação Média --->  "); puts(av_score);
            puts("\n"); 
        }  

        g_list_free(lista_rides);
        g_list_free(lista_nova);
        g_list_free(lista_driver_info);
    }

    else{
        puts("ERRO");
    }
}


/*
----------------------------------------------------------------------------------------------------------
"query_3_INTERATIVA" ---> função relativa à 3ª query no modo interativo
----------------------------------------------------------------------------------------------------------
*/


void query_3_INTERATIVA(char* N, GHashTable* t_users, GHashTable* t_rides){
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 3 ---> parâmetros: %s\n", N);
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    if (strcmp(N, "0")!=0){ 
        GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides;    
        GList* lista_nova = NULL; 
        int Ntotal = atoi(N);

        GHashTable* user_info_table = g_hash_table_new(g_str_hash, g_str_equal);
        for(; lista_rides != NULL; lista_rides=lista_rides->next){
            char* username = rides_getUser(lista_rides->data);
            char* user_status = users_getStatus(g_hash_table_lookup(t_users, username));
            if(strcasecmp(user_status, "active\n") == 0){
                double distance = atoi(rides_getDistance(lista_rides->data));
                char* ride_date = rides_getDate(lista_rides->data);
                int diaA = (ride_date[0] - '0')*10 + (ride_date[1] - '0');
                int mesA = (ride_date[3] - '0')*10 + (ride_date[4] - '0');
                int anoA = (ride_date[6] - '0')*1000 + (ride_date[7] - '0')*100 + (ride_date[8] - '0')*10 + (ride_date[9] - '0');

                if ((g_hash_table_lookup(user_info_table, username)) == NULL){
                    User_q3* user_info = user_create_q3();
                    user_info->username = username;
                    user_info->distance = distance;
                    user_info->ride_recente = ride_date;  
                    g_hash_table_insert(user_info_table, username, user_info);
                }
                else{
                    //ir buscar os valores que tavam lá
                    User_q3* user_info = user_create_q3();
                    user_info = g_hash_table_lookup(user_info_table, username);
                    //modificá-los
                    user_info->distance += distance;
                    char* ride_date_B = user_info->ride_recente;
                    int diaB = (ride_date_B[0] - '0')*10 + (ride_date_B[1] - '0');
                    int mesB = (ride_date_B[3] - '0')*10 + (ride_date_B[4] - '0');
                    int anoB = (ride_date_B[6] - '0')*1000 + (ride_date_B[7] - '0')*100 + (ride_date_B[8] - '0')*10 + (ride_date_B[9] - '0');
                    if (compara2Datas(diaA, mesA, anoA, diaB, mesB, anoB) == 1) user_info->ride_recente = ride_date;
                    g_hash_table_insert(user_info_table, username, user_info);
                }
            }
        }

        GList* lista_info_user = g_hash_table_get_values(user_info_table);
        for(; lista_info_user != NULL; lista_info_user=lista_info_user->next){
            User_q3* user_info = user_create_q3();
            user_info = lista_info_user->data;

            if ((strcmp(user_info->username, "user"))!=0){

                //ver se a length é menor q N. se sim, inserir. se n: 
                //comparar com o último membro da lista sorted
                //se sim, inserir

                if(g_list_length(lista_nova) < Ntotal){
                    lista_nova = g_list_insert_sorted(lista_nova, user_info, (GCompareFunc)compara_3);
                }
                else{
                    if((compara_3(user_info, (g_list_last(lista_nova))->data)) == -1){
                        lista_nova = g_list_delete_link(lista_nova, g_list_last(lista_nova));
                        lista_nova = g_list_insert_sorted(lista_nova, user_info, (GCompareFunc)compara_3);
                    }
                }
            }
        }

        for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
            User_q3* user_info = user_create_q3();
            user_info = lista_nova->data;
            
            char distancia[10]; 
            sprintf(distancia, "%.0f", user_info->distance); 

            printf("Username --->  "); puts(user_info->username);
            printf("Nome --->  "); puts(users_getName(g_hash_table_lookup(t_users, user_info->username)));
            printf("Distância Total --->  "); puts(distancia);
            puts("\n");
        } 

        g_list_free(lista_rides);
        g_list_free(lista_nova);
        g_list_free(lista_info_user);
    }
    else{
        puts("ERRO");
    }
}


/*
----------------------------------------------------------------------------------------------------------
"query_4_INTERATIVA" ---> função relativa à 4ª query para o modo interativo
----------------------------------------------------------------------------------------------------------
*/


void query_4_INTERATIVA(char* city, GHashTable* t_rides, GHashTable* t_drivers){ 
    
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 4 ---> parâmetros: %s\n", city); 
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    double preco = 0;
    double nr = 0;
    
    GList *lista_4 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    
    for(; lista_4 != NULL; lista_4 = lista_4->next){  
        char* cityRide = rides_getCity(lista_4->data);
        if ((strcmp(cityRide, city)) == 0){      
            char* driver_id = rides_getDriver(lista_4->data);
            char* class = drivers_getClass(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(class,"basic") == 0) preco += (3.25 + 0.62*atoi(rides_getDistance(lista_4->data)));
            if(strcasecmp(class,"green") == 0) preco += (4.00 + 0.79*atoi(rides_getDistance(lista_4->data)));
            if(strcasecmp(class,"premium") == 0) preco += (5.20 + 0.94*atoi(rides_getDistance(lista_4->data)));
            nr++;
        }
    }
    
    if (nr>0){
        double preco_medio = preco/nr;

        char buf[10]; 
        sprintf(buf, "%.3f", preco_medio);     
        
                  
        printf("Preço Médio --->  "); puts(buf);
        puts("\n");
            

        g_list_free(lista_4);
    }

    else{
        puts("ERRO");
        g_list_free(lista_4);
    }


}


/*
----------------------------------------------------------------------------------------------------------
"query_5_INTERATIVA" ---> função relativa à 5ª query no modo interativo
----------------------------------------------------------------------------------------------------------
*/


void query_5_INTERATIVA(char* dataA, char* dataB, GHashTable* t_rides, GHashTable* t_drivers){ 

    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 5 ---> parâmetros: %s %s\n", dataA, dataB); 
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    double preco = 0;
    double nr = 0;

    int diaA = (dataA[0] - '0')*10 + (dataA[1] - '0');
    int mesA = (dataA[3] - '0')*10 + (dataA[4] - '0');
    int anoA = (dataA[6] - '0')*1000 + (dataA[7] - '0')*100 + (dataA[8] - '0')*10 + (dataA[9] - '0');

    int diaB = (dataB[0] - '0')*10 + (dataB[1] - '0');
    int mesB = (dataB[3] - '0')*10 + (dataB[4] - '0');
    int anoB = (dataB[6] - '0')*1000 + (dataB[7] - '0')*100 + (dataB[8] - '0')*10 + (dataB[9] - '0');
    
    GList *lista_5 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    
    for(; lista_5 != NULL; lista_5 = lista_5->next){  
        char* date = rides_getDate(lista_5->data);
        int dia = (date[0] - '0')*10 + (date[1] - '0'); 
        int mes = (date[3] - '0')*10 + (date[4] - '0');
        int ano = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + + (date[9] - '0');
        if ((compara3Datas(dia, mes, ano, diaA, mesA, anoA, diaB, mesB, anoB)) == 1){
            char* driver_id = rides_getDriver(lista_5->data);
            char* class = drivers_getClass(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(class,"basic") == 0) preco += (3.25 + 0.62*atoi(rides_getDistance(lista_5->data)));
            if(strcasecmp(class,"green") == 0) preco += (4.00 + 0.79*atoi(rides_getDistance(lista_5->data)));
            if(strcasecmp(class,"premium") == 0) preco += (5.20 + 0.94*atoi(rides_getDistance(lista_5->data)));
            nr++;
        }
    }

    if (nr>0){
        double preco_medio = preco/nr;

        

        char buf[10]; 
        sprintf(buf, "%.3f", preco_medio);   
        
                 
        printf("Preço Médio --->  "); puts(buf);
        puts("\n");

        g_list_free(lista_5);
    }

    else{
        puts("ERRO");
        g_list_free(lista_5);
    }

}


/*
----------------------------------------------------------------------------------------------------------
"query_6_INTERATIVA" ---> função relativa à 6ª query no modo interativo 
----------------------------------------------------------------------------------------------------------
*/


void query_6_INTERATIVA(char* city, char* dataA, char* dataB, GHashTable* t_rides){
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 6 ---> parâmetros: %s %s %s\n", city, dataA, dataB); 
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    double dist = 0;
    double nr = 0;
    
    int diaA = (dataA[0] - '0')*10 + (dataA[1] - '0');
    int mesA = (dataA[3] - '0')*10 + (dataA[4] - '0');
    int anoA = (dataA[6] - '0')*1000 + (dataA[7] - '0')*100 + (dataA[8] - '0')*10 + (dataA[9] - '0');

    int diaB = (dataB[0] - '0')*10 + (dataB[1] - '0');
    int mesB = (dataB[3] - '0')*10 + (dataB[4] - '0');
    int anoB = (dataB[6] - '0')*1000 + (dataB[7] - '0')*100 + (dataB[8] - '0')*10 + (dataB[9] - '0');

    GList *lista_6 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    
    for(; lista_6 != NULL; lista_6 = lista_6->next){  
        char* cityRide = rides_getCity(lista_6->data);
        if ((strcmp(city, cityRide)) == 0){             //verificar se a cidade da viagem corresponde à cidade pedida
            char* date = rides_getDate(lista_6->data);  //converter a data em Int para poder compará-la com as datas-limite
            int dia = (date[0] - '0')*10 + (date[1] - '0'); 
            int mes = (date[3] - '0')*10 + (date[4] - '0');
            int ano = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + + (date[9] - '0');
            if (compara3Datas(dia, mes, ano, diaA, mesA, anoA, diaB, mesB, anoB) == 1){ 
                dist += atoi(rides_getDistance(lista_6->data));
                nr++;
            }
        }
    }
    
    if(nr>0){
        double r = dist/nr;

        char buf[10]; 
        sprintf(buf, "%.3f", r);      
                  
        printf("Distância Média --->  "); puts(buf);
        puts("\n");

        g_list_free(lista_6);
    }

    else{
        puts("ERRO");
        g_list_free(lista_6); 
    }

}


/*
----------------------------------------------------------------------------------------------------------
"query_7_INTERATIVA" ---> função relativa à 7ª query no modo interativo
----------------------------------------------------------------------------------------------------------
*/


void query_7_INTERATIVA(char* N, char* city, GHashTable* t_rides, GHashTable* t_drivers){
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 7 ---> parâmetros: %s %s\n", N, city);
    printf("-------------------------------------------------------------------------\n");
    printf("\n");
    
    GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    
    GList* lista_nova = NULL;

    int Ntotal = atoi(N);

    GHashTable* driver_info_table = g_hash_table_new(g_str_hash, g_str_equal);

    for(; lista_rides != NULL; lista_rides=lista_rides->next){
        char* cityRide = rides_getCity(lista_rides->data);
        if ((strcmp(cityRide, city)) == 0){     
            char* driver_id = rides_getDriver(lista_rides->data);
            char* driver_status  = drivers_getStatus(g_hash_table_lookup(t_drivers, driver_id));
            if(strcasecmp(driver_status, "active\n") == 0){
                double score_driver = atoi(rides_getScoreDriver(lista_rides->data));
                if ((g_hash_table_lookup(driver_info_table, driver_id)) == NULL){
                    Driver_q7* driver_info = driver_create_q7();
                    driver_info->id = driver_id;
                    driver_info->score_total = score_driver;
                    driver_info->nr_rides = 1;
                    g_hash_table_insert(driver_info_table, driver_id, driver_info);
                }
                else{
                    //ir buscar os valores que tavam lá
                    Driver_q7* driver_info = driver_create_q7();
                    driver_info = g_hash_table_lookup(driver_info_table, driver_id);
                    //modificá-los
                    driver_info->score_total += score_driver;
                    driver_info->nr_rides += 1;
                    g_hash_table_insert(driver_info_table, driver_id, driver_info);
                }
            }
        }
    }

    GList* lista = g_hash_table_get_values(driver_info_table);
    g_hash_table_destroy(driver_info_table);

    for(; lista != NULL; lista=lista->next){
        Driver_q7* driver_info = driver_create_q7();
        driver_info = lista->data;

        if ((strcmp(driver_info->id, "driver"))!=0){

            //ver se a length é menor q N. se sim, inserir. se n: 
            //comparar com o último membro da lista sorted
            //se sim, inserir

            if(g_list_length(lista_nova) < Ntotal){
                lista_nova = g_list_insert_sorted(lista_nova, driver_info, (GCompareFunc)compara_7);
            }
            else{
                if((compara_7(driver_info, (g_list_last(lista_nova))->data)) == -1){
                    lista_nova = g_list_delete_link(lista_nova, g_list_last(lista_nova)); // o remove não está a funcionar
                    lista_nova = g_list_insert_sorted(lista_nova, driver_info, (GCompareFunc)compara_7);
                }
            }
        }
    }


    int i = 0;     
         
    for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
        Driver_q7* driver_info = driver_create_q7();
        driver_info = lista_nova->data;
        double av_media = (driver_info->score_total)/(driver_info->nr_rides);
        char av_score[10];

        sprintf(av_score, "%.3f", av_media);  

        printf("ID (Condutor) --->  "); puts(driver_info->id);
        printf("Nome --->  ");puts(drivers_getName(g_hash_table_lookup(t_drivers, driver_info->id)));
        printf("Avaliação Média --->  ");puts(av_score);
        puts("\n");
        
    }

    g_list_free(lista_rides);
    g_list_free(lista_nova);
    g_list_free(lista);
}


/*
----------------------------------------------------------------------------------------------------------
"query_8_INTERATIVA" ---> função relativa à 8ª query no modo interativo
----------------------------------------------------------------------------------------------------------
*/


void query_8_INTERATIVA(char* gender, char* x_years, GHashTable* t_rides, GHashTable* t_drivers, GHashTable* t_users){
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 8 ---> parâmetros: %s %s\n", gender, x_years); 
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    GList *lista_rides = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides

    int ano = atoi(x_years);

    GList* lista_nova = NULL;  
    
    for(; lista_rides != NULL; lista_rides=lista_rides->next){

        char* username = rides_getUser(lista_rides->data);
        char* user_status = users_getStatus(g_hash_table_lookup(t_users, username));
        char* driver_ID =  rides_getDriver(lista_rides->data);
        char* driver_status  = drivers_getStatus(g_hash_table_lookup(t_drivers, driver_ID));
        //comparar os generos
        if(strcmp(username, "user") != 0 && (strcasecmp(user_status, "active\n") == 0) && (strcasecmp(driver_status, "active\n") == 0)){
            char* user_gender = users_getGender(g_hash_table_lookup(t_users,username));   //AQUI
            char* driver_gender =  drivers_getGender(g_hash_table_lookup(t_drivers,driver_ID));
            //comparar idade das contas

            char* user_acc_creation = users_getAccDate(g_hash_table_lookup(t_users,username));
            char* driver_acc_creation = drivers_getAccDate(g_hash_table_lookup(t_drivers,driver_ID));


            int diaU = (user_acc_creation[0] - '0')*10 + (user_acc_creation[1] - '0');
            int mesU = (user_acc_creation[3] - '0')*10 + (user_acc_creation[4] - '0');
            int anoU = (user_acc_creation[6] - '0')*1000 + (user_acc_creation[7] - '0')*100 + (user_acc_creation[8] - '0')*10 + (user_acc_creation[9] - '0');

            int diaD = (driver_acc_creation[0] - '0')*10 + (driver_acc_creation[1] - '0');
            int mesD = (driver_acc_creation[3] - '0')*10 + (driver_acc_creation[4] - '0');
            int anoD = (driver_acc_creation[6] - '0')*1000 + (driver_acc_creation[7] - '0')*100 + (driver_acc_creation[8] - '0')*10 + (driver_acc_creation[9] - '0');
            
            if ((strcmp(user_gender, gender) == 0) && (strcmp(driver_gender, gender) == 0) && (xOuMaisAnos(diaU,mesU,anoU,ano) == 1) && (xOuMaisAnos(diaD,mesD,anoD,ano) == 1)){
                Driver_user_q8* driver_user_info = driver_user_create_q8();
                driver_user_info->driver_id = driver_ID;
                driver_user_info->driver_name = drivers_getName(g_hash_table_lookup(t_drivers,driver_ID));
                driver_user_info->driver_acc_creation = drivers_getAccDate(g_hash_table_lookup(t_drivers,driver_ID));
                driver_user_info->user_username = username;
                driver_user_info->user_name = users_getName(g_hash_table_lookup(t_users,username));
                driver_user_info->user_acc_creation = users_getAccDate(g_hash_table_lookup(t_users,username));
                driver_user_info->ride_id = rides_getID(lista_rides->data);

                lista_nova = g_list_insert_sorted(lista_nova, driver_user_info, (GCompareFunc)compara_8);

            }
        }
        
    }



    //lista_nova = g_list_sort(lista_nova, (GCompareFunc)compara_8);

    int i = 0;              
    for(; lista_nova != NULL; lista_nova = lista_nova->next){ 
        Driver_user_q8* driver_user_info = driver_user_create_q8();
        driver_user_info = lista_nova->data;

        printf("ID (Condutor) --->  "); puts(driver_user_info->driver_id);
        printf("Nome (Condutor) --->  "); puts(driver_user_info->driver_name);
        printf("ID (Utilizador) --->  "); puts(driver_user_info->user_username);
        printf("Nome (Utilizador) --->  ");puts(driver_user_info->user_name);
        puts("\n");
        
    }

    g_list_free(lista_rides);
    g_list_free(lista_nova);    
    
}


/*
----------------------------------------------------------------------------------------------------------
"query_9_INTERATIVA" ---> função relativa à 9ª query no modo interativo 
----------------------------------------------------------------------------------------------------------
*/


void query_9_INTERATIVA(char* dataA, char* dataB, GHashTable* t_rides){ 
    printf("-------------------------------------------------------------------------\n");
    printf("Executou Query 9 ---> parâmetros: %s %s\n", dataA, dataB); 
    printf("-------------------------------------------------------------------------\n");
    printf("\n");

    int diaA = (dataA[0] - '0')*10 + (dataA[1] - '0'); //converter as datas em int de forma a poder compará-las
    int mesA = (dataA[3] - '0')*10 + (dataA[4] - '0');
    int anoA = (dataA[6] - '0')*1000 + (dataA[7] - '0')*100 + (dataA[8] - '0')*10 + (dataA[9] - '0');

    int diaB = (dataB[0] - '0')*10 + (dataB[1] - '0');
    int mesB = (dataB[3] - '0')*10 + (dataB[4] - '0');
    int anoB = (dataB[6] - '0')*1000 + (dataB[7] - '0')*100 + (dataB[8] - '0')*10 + (dataB[9] - '0');

    GList *lista_9 = g_hash_table_get_values(t_rides); //obter uma lista com todas as rides
    GList* lista_nova_9 = NULL; //criar uma lista onde serão inseridas as rides que corresponderem aos parâmetros

    for(; lista_9 != NULL; lista_9 = lista_9->next){  
        char* tip = rides_getTip(lista_9->data);
        if ((strcmp(tip, "0.0")) != 0){                      //verificar se houve tip
            char* date =
             rides_getDate(lista_9->data);       //converter a data em Int para poder compará-la com as datas limite
            int dia = (date[0] - '0')*10 + (date[1] - '0'); 
            int mes = (date[3] - '0')*10 + (date[4] - '0');
            int ano = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + + (date[9] - '0');
            if (compara3Datas(dia, mes, ano, diaA, mesA, anoA, diaB, mesB, anoB) == 1){   //se estiver dentro das datas limite, adicionar à lista_nova_9
                Ride_q9* ride_info = ride_create_q9();
                ride_info->ride_id = rides_getID(lista_9->data);
                ride_info->ride_date = date;
                ride_info->ride_distance = rides_getDistance(lista_9->data);
                ride_info->ride_city = rides_getCity(lista_9->data);
                ride_info->ride_tip = tip;

                lista_nova_9 = g_list_insert_sorted(lista_nova_9, ride_info, (GCompareFunc)compara_9);
            }
        }
    }
            
    for(; lista_nova_9 != NULL; lista_nova_9 = lista_nova_9->next){ 
        Ride_q9* ride_info = ride_create_q9();
        ride_info = lista_nova_9->data;

        printf("ID (Viagem) --->  "); puts(ride_info->ride_id);
        printf("Data da viagem --->  "); puts(ride_info->ride_date);
        printf("Distância --->  "); puts(ride_info->ride_distance);
        printf("Cidade --->  "); puts(ride_info->ride_city);
        printf("Gorjeta --->  "); printf("%s", ride_info->ride_tip);

        if((strlen(ride_info->ride_tip)) == 3){
            printf("00");        //para manter as casas decimais certas
        }
        else if ((strlen(ride_info->ride_tip)) == 4){ 
            printf("0");   
        }
        puts("\n");
    }

    g_list_free(lista_9);
    g_list_free(lista_nova_9);
}
