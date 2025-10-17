#ifndef DB_H
#define DB_H

#include "records.h"

int load_parents(const char *path, struct Parent *parents, int max_parents);
int load_records(const char *path, struct Record *records, int max_records);
int save_records(const char *path, const struct Record *records, int record_count);
int database_exists(const char *path);

#endif /* DB_H */

