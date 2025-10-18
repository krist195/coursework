#include <stdio.h>
#include "pokaz.h"

struct parent *find_parent(struct parent *parents, int parent_count, int parent_id) // ищем родителя по идентификатору
{
    int i; // индекс цикла
    for (i = 0; i < parent_count; i++) // двигаемся по массиву родителей
    {
        if (parents[i].id == parent_id) // сравниваем идентификатор
        {
            return &parents[i]; // если совпало, возвращаем указатель на родителя
        }
    }
    return NULL; // если никого не нашли, возвращаем NULL
}

void show_records(struct record *records, int record_count, struct parent *parents, int parent_count) // печатаем таблицу учеников
{
    int i; // индекс по ученикам
    printf(" # | %-12s | %-12s | %-13s | %-24s | %-10s | %-12s | %-12s | %-20s\n", "Name", "Surname", "PersonalCode", "Email", "Group", "Phone", "Birthday", "Parent"); // печатаем шапку таблицы
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"); // печатаем разделительную линию
    for (i = 0; i < record_count; i++) // идем по всем ученикам
    {
        struct parent *parent_info = find_parent(parents, parent_count, records[i].parent_id); // ищем информацию о родителе
        char parent_text[200]; // массив для записи текста о родителе
        char birthday_text[20]; // массив для записи даты рождения
        if (parent_info) // если родитель найден
        {
            snprintf(parent_text, sizeof(parent_text), "%s %s", parent_info->name, parent_info->surname); // собираем имя и фамилию родителя
        }
        else // если родитель не найден
        {
            snprintf(parent_text, sizeof(parent_text), "%s", "N/A"); // записываем текст N/A
        }
        snprintf(birthday_text, sizeof(birthday_text), "%02d.%02d.%04d", records[i].birth_day, records[i].birth_month, records[i].birth_year); // собираем дату рождения из чисел
        printf("%2d | %-12s | %-12s | %-13s | %-24s | %-10s | %-12s | %-12s | %-20s\n", i + 1, records[i].name, records[i].surname, records[i].personal_code, records[i].email, records[i].group, records[i].phone, birthday_text, parent_text); // выводим строку таблицы
    }
} 
