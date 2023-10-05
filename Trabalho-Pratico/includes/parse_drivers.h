#ifndef DRIVERS_H
#define DRIVERS_H
#include <glib.h>

/*
ESTRUTURA TALVEZ PARA O FUTURO

typedef struct driver{
    long id;
    char* name;
    time_t birth_date;
    gender;
    class;
    plate;
    char* city;
    time_t account_creation;
    int status;
} Driver;

enum status {Active, Inactive};
enum class {Green, Basic, Premium};

typedef enum status Status;
typedef enum class Class;

*/

typedef struct driver Driver;


Driver* driver_create();
void free_key(gpointer data);
void free_driver(gpointer data);
void printDriver(Driver* d);
void printFuncHash_Driver (void* key, void* value, void* data);
char* drivers_getID(Driver* d);
char* drivers_getName(Driver* d);
char* drivers_getBirthDate(Driver* d);
char* drivers_getGender(Driver* d);
char* drivers_getClass(Driver* d);
char* drivers_getAccDate(Driver* d);
char* drivers_getStatus(Driver* d);
int d_verifyDate(char* date);
int d_verifyClass(char* class);
int d_verifyAccStatus(char* accStatus);
GHashTable* parse_file_drivers(FILE* fp, GHashTable* t);

#endif