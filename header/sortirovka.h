#pragma once

#include "zapisi.h" // подключаем структуры record и parent

void bubble_sort_records(struct record *records, int record_count, const char *field_name); // сортируем массив записей по указанному полю
