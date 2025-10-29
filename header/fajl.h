#pragma once

#include "zapisi.h"

int read_parents(struct parent *parents, int max_parents);
int read_records(struct record *records, int max_records);
int write_records(struct record *records, int record_count);
