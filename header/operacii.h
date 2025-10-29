#pragma once

#include "zapisi.h"

int add_record(struct record *records, int record_count, int max_records, struct record new_record); // добавляем запись об ученике
int remove_record_by_phone(struct record *records, int record_count, const char *phone); // удаляем запись по номеру телефона
int filter_by_group(struct record *records, int record_count, const char *group, struct record *result); // выбираем учеников по группе
int filter_by_parent(struct record *records, int record_count, int parent_id, struct record *result); // выбираем учеников по родителю
