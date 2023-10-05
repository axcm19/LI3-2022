#ifndef QUERYS_H
#define QUERYS_H
#include <glib.h>
#include "parse_users.h"
#include "parse_rides.h"
#include "parse_drivers.h"

/*
NÃO É USADA NEM DEVIA ESTAR AQUI

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;
*/

typedef struct driver_q2 Driver_q2;

typedef struct ride_q9 Ride_q9;


#define DATA_REFERENCIA "09/10/2022"

void inicia_data(char* data);
int compara3Datas(int dia, int mes, int ano, int diaA, int mesA, int anoA, int diaB, int mesB, int anoB);
int compara2Datas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);
int calculaIdade(char* birthDate);
void query_1(char* ID, int command, GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides);
void query_2(char* N, int command, GHashTable* t_drivers, GHashTable* t_rides);
void query_3(char* N, int command, GHashTable* t_users, GHashTable* t_rides);
void query_4(char* city, int command, GHashTable* t1, GHashTable* t2);
void query_5(char* dataA, char* dataB, int command, GHashTable* t1, GHashTable* t2);
void query_6(char* city, char* dataA, char* dataB, int command, GHashTable* t1);
void query_7(char* N, char* city, int command, GHashTable* t_rides, GHashTable* t_drivers);
void query_8(char* gender, char* x_years, int command, GHashTable* t_rides, GHashTable* t_drivers, GHashTable* t_users);
int compara_9(Ride_q9* rideA, Ride_q9* rideB);
void query_9(char* dataA, char* dataB, int command, GHashTable* t1);
void query_1_INTERATIVA(char* ID, GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides);
void query_2_INTERATIVA(char* N, GHashTable* t_drivers, GHashTable* t_rides);
void query_3_INTERATIVA(char* N, GHashTable* t_users, GHashTable* t_rides);
void query_4_INTERATIVA(char* city, GHashTable* t_rides, GHashTable* t_drivers);
void query_5_INTERATIVA(char* dataA, char* dataB, GHashTable* t_rides, GHashTable* t_drivers);
void query_6_INTERATIVA(char* city, char* dataA, char* dataB, GHashTable* t_rides);
void query_7_INTERATIVA(char* N, char* city, GHashTable* t_rides, GHashTable* t_drivers);
void query_8_INTERATIVA(char* gender, char* x_years, GHashTable* t_rides, GHashTable* t_drivers, GHashTable* t_users);
void query_9_INTERATIVA(char* dataA, char* dataB, GHashTable* t_rides);

#endif