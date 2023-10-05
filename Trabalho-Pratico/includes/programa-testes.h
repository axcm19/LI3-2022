#include <time.h>
#include <stdio.h>
#include <glib.h>
#include "batch.h"
#include <sys/resource.h>

int compareFile(FILE *f1, FILE *f2);
void test_q1(GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides);
void test_q2(GHashTable* t_drivers, GHashTable* t_rides);
void test_q3(GHashTable* t_users, GHashTable* t_rides);
void test_q4(GHashTable* t_rides, GHashTable* t_drivers);
void test_q5(GHashTable* t_rides, GHashTable* t_drivers);
void test_q6(GHashTable* t_rides);
void test_q7(GHashTable* t_rides, GHashTable* t_drivers);
void test_q8(GHashTable* t_rides, GHashTable* t_drivers, GHashTable* t_users);
void test_q9(GHashTable* t_rides);
void teste_queries(GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides);
int main(int argc, char **argv);