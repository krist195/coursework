#include <stdio.h>
#include "fajl.h" 

/* Читае родительский бд и бд школьников и так же записываем */

extern char record_file_path[]; // объявляем путь к файлу учеников из другого файла
extern char parent_file_path[]; // объявляем путь к файлу родителей из другого файла

int read_parents(struct parent *parents, int max_parents) // читаем родителей из файла
{
    FILE *file = fopen(parent_file_path, "r"); // открываем файл родителей для чтения
    int count = 0; // создаем счетчик записей
    if (!file) // проверяем удалось ли открыть файл
    {
        return 0; // если открыть не получилось
    }
    while (count < max_parents) // читаем пока есть место
    {
        struct parent temp_parent; // создаем временного родителя
        int read_items = fscanf(file, "%d %99s %99s", &temp_parent.id, temp_parent.name, temp_parent.surname); // читаем одну строку
        if (read_items != 3) // проверяем количество прочитанных значений

        {
            break; // если считали не три значения, выходим из цикла
        }
        parents[count] = temp_parent; // копируем временную структуру в массив
        count++; // увеличиваем количество найденных родителей
    }
    fclose(file); // закрываем файл после чтения

    return count; // возвращаем количество загруженных родителей
}



int read_records(struct record *records, int max_records) // читаем учеников из файла
{
    FILE *file = fopen(record_file_path, "r"); // открываем файл с учениками
    int count = 0; // счетчик записей
    if (!file) // проверяем открытие файла
    {
        return 0; // если файл не открылся, возвращаем 0
    }
    while (count < max_records) // читаем пока есть место
    {
        struct record temp_record; // создаем временного ученика
        int read_items = fscanf(file, "%99s %99s %49s %99s %49s %29s %d %d %d %d", temp_record.name, temp_record.surname, temp_record.personal_code, temp_record.email, temp_record.group, temp_record.phone, &temp_record.parent_id, &temp_record.birth_day, &temp_record.birth_month, &temp_record.birth_year); // читаем строку ученика
        if (read_items != 10) // проверяем количество элементов
        {
            break; // если считали не десять элементов, заканчиваем чтение
        }
        records[count] = temp_record; // сохраняем ученика в массив
        count++; // увеличиваем счетчик
    }
    fclose(file); // закрываем файл
    return count; // возвращаем количество прочитанных учеников
}

int write_records(struct record *records, int record_count) // записываем учеников обратно в файл
{
    FILE *file = fopen(record_file_path, "w"); // открываем файл для записи
    int i; // объявляем индекс цикла
    if (!file) // проверяем открытие файла
    {
        return 0; 
    }
    for (i = 0; i < record_count; i++) // проходим по всем ученикам
    {
        fprintf(file, "%s %s %s %s %s %s %d %d %d %d\n", records[i].name, records[i].surname, records[i].personal_code, records[i].email, records[i].group, records[i].phone, records[i].parent_id, records[i].birth_day, records[i].birth_month, records[i].birth_year); // записываем строку ученика
    }
    fclose(file); // закрываем файл
    return 1; // возвращаем успех
}
