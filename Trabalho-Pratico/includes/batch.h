#ifndef BATCH_H
#define BATCH_H

#include "parse_users.h"
#include "parse_drivers.h"
#include "parse_rides.h"
#include "querys.h"
#include <glib.h>

GHashTable* catalogoUsers(char **argv, GHashTable* t);
GHashTable* catalogoDrivers(char **argv, GHashTable* t);
GHashTable* catalogoRides(char **argv, GHashTable* t);
void parse_BATCH(FILE* fp, GHashTable* t1, GHashTable* t2, GHashTable* t3);

#endif