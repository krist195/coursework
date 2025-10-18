#include "sortirovka.h"
#include "stroki.h"

static int compare_records_by_field(struct record *first, struct record *second, const char *field_name) // внутри файла сравниваем две записи
{
    if (field_name == 0) // проверяем строку поля
    {
        return 0; // если поля нет, возвращаем 0
    }
    if (text_equals(field_name, "name")) // если требуется сравнение по имени
    {
        return text_compare(first->name, second->name); // сравниваем имена
    }
    if (text_equals(field_name, "surname")) // если поле фамилия
    {
        return text_compare(first->surname, second->surname); // сравниваем фамилии
    }
    if (text_equals(field_name, "group")) // если поле группа
    {
        return text_compare(first->group, second->group); // сравниваем группы
    }
    if (text_equals(field_name, "phone")) // если поле телефон
    {
        return text_compare(first->phone, second->phone); // сравниваем телефоны
    }
    if (text_equals(field_name, "parent")) // если поле родитель
    {
        return first->parent_id - second->parent_id; // вычисляем разницу идентификаторов
    }
    if (text_equals(field_name, "personal") || text_equals(field_name, "code")) // если поле персональный код
    {
        return text_compare(first->personal_code, second->personal_code); // сравниваем персональные коды
    }
    if (text_equals(field_name, "birthday")) // если поле дата рождения
    {
        if (first->birth_year != second->birth_year) // сравниваем годы
        {
            return first->birth_year - second->birth_year; // возвращаем разницу лет
        }
        if (first->birth_month != second->birth_month) // если года равны, смотрим месяцы
        {
            return first->birth_month - second->birth_month; // возвращаем разницу месяцев
        }
        return first->birth_day - second->birth_day; // возвращаем разницу дней
    }
    return text_compare(first->name, second->name); // по умолчанию сравниваем по имени
} 

static void swap_records(struct record *a, struct record *b) // меняем местами две записи
{
    struct record temp = *a; // сохраняем первую запись во временную переменную
    *a = *b; // записываем вторую запись на место первой
    *b = temp; // помещаем временную запись на место второй
}

void bubble_sort_records(struct record *records, int record_count, const char *field_name) // сортировка записей пузырьком
{
    int i; // индекс цикла
    int swapped; // флаг был ли обмен
    if (records == 0) // проверяем указатель на массив
    {
        return; // если указатель пустой, выходим
    }
    if (record_count <= 1) // проверяем количество элементов
    {
        return; // если один или ноль элементов, сортировать не нужно
    }
    do // запускаем цикл сортировки
    {
        swapped = 0; // сбрасываем флаг обмена
        for (i = 0; i < record_count - 1; i++) // проходим по массиву
        {
            if (compare_records_by_field(&records[i], &records[i + 1], field_name) > 0) // сравниваем соседние элементы
            {
                swap_records(&records[i], &records[i + 1]); // меняем записи местами
                swapped = 1; // отмечаем что обмен был
            }
        }
    } while (swapped); // повторяем пока делаются обмены
}
