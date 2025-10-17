#pragma once // подключаем заголовок только один раз

int text_compare(const char *a, const char *b); // сравниваем две строки лексикографически
int text_equals(const char *a, const char *b); // проверяем строки на равенство
int text_length(const char *text); // считаем длину строки в символах
void text_copy(char *dest, const char *src); // копируем строку из src в dest

