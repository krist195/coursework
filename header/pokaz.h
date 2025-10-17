#pragma once // подключаем заголовок один раз

#include "zapisi.h" // подключаем структуры record и parent

struct parent *find_parent(struct parent *parents, int parent_count, int parent_id); // ищем родителя по номеру
void show_records(struct record *records, int record_count, struct parent *parents, int parent_count); // выводим таблицу учеников

