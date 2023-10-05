#ifndef USERS_H
#define USERS_H
#include <glib.h>
#include <stdio.h>



/*
ESTRUTURA TALVEZ PARA O FUTURO 

enum gender {F, M}; 
enum payment {Credit, Debit, Cash};
enum status {Active, Inactive};

typedef enum gender Gender;
typedef enum status Status;
typedef enum payment Payment;

typedef struct user{
    char* username;
    char* name;
    time_t birth_date;
    time_t account_creation;
    Gender gender;
    Payment pay_method;
    Status account_status;
} User;

*/

typedef struct user User;

User* user_create();
void free_user(gpointer data);
User* user_clone(User* u);
void printUser(User* u);
void printFuncHash_User (void* key, void* value, void* data);
char* users_getUsername(User* u);
char* users_getName(User* u);
char* users_getGender(User* u);
char* users_getBirthDate(User* u);
char* users_getAccDate(User* u);
char* users_getStatus(User* u);
int u_verifyDate(char* date);
int u_verifyAccStatus(char* accStatus);
GHashTable* parse_file_users(FILE* fp, GHashTable* t);


#endif
