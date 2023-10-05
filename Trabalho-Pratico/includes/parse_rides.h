#ifndef RIDES_H
#define RIDES_H
#include <glib.h>


/*
ESTRUTURA PARA FUTURA IMPLEMENTAÇÃO

#include "users.h"
#include "drivers.h"

typedef struct ride{
    long id;
    time_t date;
    Driver driver;
    User user;
    char* city;
    long distance;
    int score_user;
    int score_driver;
    int tip;
    char* comment;
} Ride;

*/

//typedef struct ride* Ride;

typedef struct ride Ride;

Ride* ride_create();
void free_key(gpointer data);
void free_ride(gpointer data);
void printRide(Ride* r);
void printFuncHash_Ride (void* key, void* value, void* data);
char* rides_getID(Ride* r);
char* rides_getDate(Ride* r);
char* rides_getDriver(Ride* r);
char* rides_getUser(Ride* r);
char* rides_getCity(Ride* r);
char* rides_getDistance(Ride* r);
char* rides_getScoreUser(Ride* r);
char* rides_getScoreDriver(Ride* r);
char* rides_getTip(Ride* r);
int r_verifyDate(char* date);
int r_verifyDistance(char* distance);
int r_verifyScoreOrTIp(char* score);
GHashTable* parse_file_rides(FILE* fp, GHashTable* t);
int open_file_rides();

#endif