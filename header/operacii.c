#include "operacii.h"
#include "stroki.h"

int add_record(struct record *records, int record_count, int max_records, struct record new_record)
{
    int i; //для проверки
    if (records == 0) // проверяем указатель на массив
    {
        return record_count; // если массив пустой, возвращаем исходное количество
    }
    if (record_count >= max_records) // проверяем место в массиве
    {
        return record_count; // если места нет, возвращаем исходное количество
    }
    for (i = 0; i < record_count; i++) // проходим по текущим записям
    {
        if (text_equals(records[i].phone, new_record.phone)) // сравниваем телефоны на совпадение
        {
            return record_count; // если телефон уже есть, не добавляем запись
        }
    }
    records[record_count] = new_record; // копируем новую запись в конец массива
    return record_count + 1; // увеличиваем количество записей
} // конец функции add_record

int remove_record_by_phone(struct record *records, int record_count, const char *phone) // удаляем запись по номеру телефона
{
    int i; // индекс поиска
    int j; // индекс для сдвига
    if (records == 0) // проверяем массив
    {
        return record_count; // если массив пустой, возвращаем исходное количество
    }
    if (phone == 0) // проверяем телефон
    {
        return record_count; // если телефона нет, ничего не делаем
    }
    for (i = 0; i < record_count; i++) // ищем подходящую запись
    {
        if (text_equals(records[i].phone, phone)) // сравниваем телефон
        {
            for (j = i; j < record_count - 1; j++) // сдвигаем остальные записи
            {
                records[j] = records[j + 1]; // переносим следующую запись на текущую позицию
            }
            return record_count - 1; // уменьшаем количество записей
        }
    }
    return record_count; // если запись не нашли, возвращаем исходное количество
} // конец функции remove_record_by_phone

int filter_by_group(struct record *records, int record_count, const char *group, struct record *result) // ищем всех учеников группы
{
    int i; // индекс входного массива
    int out_index = 0; // индекс для результата
    if (records == 0 || result == 0) // проверяем указатели
    {
        return 0; // если указателей нет, ничего не возвращаем
    }
    if (group == 0) // проверяем строку группы
    {
        return 0; // если группы нет, ничего не возвращаем
    }
    for (i = 0; i < record_count; i++) // идем по всем ученикам
    {
        if (text_equals(records[i].group, group)) // сравниваем группу
        {
            result[out_index] = records[i]; // копируем запись в результат
            out_index++; // увеличиваем количество найденных записей
        }
    }
    return out_index; // возвращаем сколько записей нашли
} // конец функции filter_by_group

int filter_by_parent(struct record *records, int record_count, int parent_id, struct record *result) // ищем учеников по родителю
{
    int i; // индекс входного массива
    int out_index = 0; // индекс результата
    if (records == 0 || result == 0) // проверяем указатели
    {
        return 0; // если указателей нет, ничего не возвращаем
    }
    for (i = 0; i < record_count; i++) // идем по всем ученикам
    {
        if (records[i].parent_id == parent_id) // сравниваем идентификатор родителя
        {
            result[out_index] = records[i]; // копируем запись в результат
            out_index++; // увеличиваем счетчик найденных записей
        }
    }
    return out_index;
}
