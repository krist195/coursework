#pragma once

#include "zapisi.h"

struct parent *find_parent(struct parent *parents, int parent_count, int parent_id);
void show_records(struct record *records, int record_count, struct parent *parents, int parent_count);