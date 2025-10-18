#pragma once

#include "zapisi.h" // подключаем структуры record и parent

int read_parents(struct parent *parents, int max_parents); // читаем родителей из файла
int read_records(struct record *records, int max_records); // читаем учеников из файла
int write_records(struct record *records, int record_count); // записываем учеников обратно в файл
