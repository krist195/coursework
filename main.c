#include <stdio.h> // подключаем стандартный ввод и вывод
#include <stdlib.h> // подключаем функции преобразования чисел



#include "header/zapisi.h" // подключаем структуры record и parent
#include "header/fajl.h" // подключаем функции работы с файлами
#include "header/pokaz.h" // подключаем функции вывода таблицы
#include "header/sortirovka.h" // подключаем сортировку записей
#include "header/operacii.h" // подключаем добавление, удаление и фильтрацию
#include "header/stroki.h" // подключаем простые функции сравнения строк


char record_file_path[] = "database/db.txt"; // путь к файлу со списком учеников
char parent_file_path[] = "database/parentdb.txt"; // путь к файлу с родителями


int copy_text(char *target, const char *source, int max_length) // функция копирования строк с проверками
{
    if (target == NULL || source == NULL) // проверяем указатели на  валидность
    {
        return 0; // возвращаем 0 если что-то не так
    }
    int source_length = text_length(source); // узнаем длину исходной строки
    if (source_length >= max_length) // проверяем помещается ли строка
    {
        return 0; // если строка слишком длинная, возвращаем 0
    }
    text_copy(target, source); // копируем строку целиком
    return 1; // возвращаем 1 при успешном копировании
} 







int string_to_int(const char *text, int *value) // переводим строку в целое число
{
    char *end_pointer; // указатель на остаток строки
    long temp_value; // временное значение типа long
    if (text == NULL || value == NULL) // проверяем валидность указателей
    {
        return 0; // если указатели кал, возвращаем 0
    }
    temp_value = strtol(text, &end_pointer, 10); // преобразуем строку в число
    if (text[0] == '\0' || *end_pointer != '\0') // проверяем что строка целиком число
    {
        return 0; // если есть лишние символы, возвращаем 0
    }
    if (temp_value < -2147483648L || temp_value > 2147483647L) // проверяем диапазон int
    {
        return 0; // если число слишком большое, возвращаем 0
    }
    *value = (int)temp_value; // записываем результат через указатель
    return 1; // возвращаем 1 если всё чилл
}



// выводим подсказку по использованию
void show_usage(const char *program_name)
{
    printf("Usage:\n"); // выводим заголовок
    printf("  %s list\n", program_name); // показываем команду list
    printf("  %s add Name Surname PersonalCode Email Group Phone ParentID BirthDay BirthMonth BirthYear\n", program_name); // показываем команду add
    printf("  %s remove Phone\n", program_name); // показываем команду remove
    printf("  %s sort field [field...]\n", program_name); // показываем команду sort
    printf("  %s group GroupName [field]\n", program_name); // показываем команду group
    printf("  %s parent ParentID\n", program_name); // показываем команду parent
    printf("Fields: name, surname, group, phone, parent, birthday, personal, code\n"); // перечисляем доступные поля
} 





int main(int argc, char *argv[])
{
    struct record records[100]; // создаем массив учеников
    struct parent parents[100]; // создаем массив родителей

    int record_count = read_records(records, 100); // загружаем записи учеников из файла
    int parent_count = read_parents(parents, 100); // загружаем записи родителей из файла

    if (argc < 2) // проверяем что пользователь указал команду
    {
        show_usage(argv[0]); // если нет, выводим подсказку
        return 0; 
    }

    if (text_equals(argv[1], "list")) // проверяем команду list
    {
        printf("Loaded %d records from %s\n\n", record_count, record_file_path); // сообщаем сколько записей загрузили
        show_records(records, record_count, parents, parent_count); // выводим таблицу учеников
        return 0;
    }



    if (text_equals(argv[1], "add")) // проверяем команду add
    {
        struct record new_record; // создаем новую структуру ученика
        if (argc != 12) // проверяем количество аргументов
        {
            printf("Wrong arguments for add\n"); // сообщаем об ошибке
            show_usage(argv[0]); // подсказываем правильный формат
            return 1; 
        }
        if (!copy_text(new_record.name, argv[2], sizeof(new_record.name))) // копируем имя
        {
            printf("Bad name value\n"); 
            return 1; 
        }
        if (!copy_text(new_record.surname, argv[3], sizeof(new_record.surname))) // копируем фамилию
        {
            printf("Bad surname value\n");
            return 1; 
        }
        if (!copy_text(new_record.personal_code, argv[4], sizeof(new_record.personal_code))) // копируем персональный код
        {
            printf("Bad personal code\n");
            return 1; 
        }
        if (!copy_text(new_record.email, argv[5], sizeof(new_record.email))) // копируем адрес почты
        {
            printf("Bad email value\n");
            return 1; 
        }
        if (!copy_text(new_record.group, argv[6], sizeof(new_record.group))) // копируем группу
        {
            printf("Bad group value\n");
            return 1; 
        }
        if (!copy_text(new_record.phone, argv[7], sizeof(new_record.phone))) // копируем телефон
        {
            printf("Bad phone value\n"); 
            return 1; 
        }
        if (!string_to_int(argv[8], &new_record.parent_id)) // читаем идентификатор родителя
        {
            printf("Bad parent id\n");
            return 1; 
        }
        if (!string_to_int(argv[9], &new_record.birth_day)) // читаем день рождения
        {
            printf("Bad birth day\n");
            return 1; 
        }
        if (!string_to_int(argv[10], &new_record.birth_month)) // читаем месяц рождения
        {
            printf("Bad birth month\n");
            return 1;
        }
        if (!string_to_int(argv[11], &new_record.birth_year)) // читаем год рождения
        {
            printf("Bad birth year\n");
            return 1; 
        }
        if (new_record.birth_day < 1 || new_record.birth_day > 31 || new_record.birth_month < 1 || new_record.birth_month > 12 || new_record.birth_year < 1900) // проверяем дату рождения
        {
            printf("Birthday looks wrong\n");
            return 1; 
        }
        record_count = add_record(records, record_count, 100, new_record); // пытаемся добавить новую запись
        if (!write_records(records, record_count)) // сохраняем изменения в файл
        {
            printf("Could not save database\n"); // сообщаем об ошибке записи
            return 1; // завершаем с ошибкой
        }
        printf("Added record for %s %s\n", new_record.name, new_record.surname); // подтверждаем добавление

        return 0;
    }

    if (text_equals(argv[1], "remove")) // проверяем команду remove

    {
        int new_count; // переменная для нового количества записей
        if (argc != 3) // проверяем количество аргументов
        {
            printf("Wrong arguments for remove\n"); // сообщаем об ошибке
            show_usage(argv[0]); // показываем правильный формат
            return 1;
        }
        new_count = remove_record_by_phone(records, record_count, argv[2]); // удаляем запись по телефону
        if (new_count == record_count) // проверяем что запись действительно удалена
        {
            printf("Phone %s not found\n", argv[2]); // сообщаем что телефон не нашли
            return 1;
        }
        record_count = new_count; // обновляем количество записей
        if (!write_records(records, record_count)) // сохраняем изменения в файл
        {
            printf("Could not save database\n"); // сообщаем об ошибке записи
            return 1; 
        }
        printf("Removed record with phone %s\n", argv[2]); // подтверждаем удаление
        return 0; 
    }
    if (text_equals(argv[1], "sort")) // проверяем команду sort
    {
        int i; // индекс для перебора полей
        if (argc < 3) // проверяем что указано хотя бы одно поле
        {
            printf("Need at least one field for sort\n"); // сообщаем об ошибке
            show_usage(argv[0]); // подсказываем синтаксис
            return 1;
        }
        for (i = 2; i < argc; i++) // проходим по всем указанным полям
        {
            bubble_sort_records(records, record_count, argv[i]); // сортируем по текущему полю
        }
        if (!write_records(records, record_count)) // сохраняем сортировку в файл
        {
            printf("Could not save database\n"); // сообщение об ошибке записи
            return 1;
        }

        show_records(records, record_count, parents, parent_count); // выводим отсортированную таблицу
        return 0;
    }
    if (text_equals(argv[1], "group")) // проверяем команду group
    {
        struct record filtered[100]; // создаем массив для выбранных записей
        int filtered_count; // переменная для количества найденных записей
        const char *sort_field = "birthday"; // сортируем по дате рождения по умолчанию
        if (argc != 3 && argc != 4) // проверяем количество аргументов
        {
            printf("Wrong arguments for group\n"); // сообщаем об ошибке
            show_usage(argv[0]); // подсказываем синтаксис
            return 1; // завершаем с ошибкой
        }
        if (argc == 4) // если указано поле сортировки
        {
            sort_field = argv[3]; // сохраняем поле сортировки
        }
        filtered_count = filter_by_group(records, record_count, argv[2], filtered); // фильтруем записи по группе
        if (filtered_count == 0) // проверяем нашли ли мы кого-нибудь
        {
            printf("No records in group %s\n", argv[2]); // выводим сообщение что группа пустая
            return 0;
        }
        bubble_sort_records(filtered, filtered_count, sort_field); // сортируем найденные записи
        show_records(filtered, filtered_count, parents, parent_count); // выводим таблицу отфильтрованных учеников
        return 0; 
    }
    if (text_equals(argv[1], "parent")) // проверяем команду parent
    {
        struct record filtered[100]; // создаем массив для записей родителя
        int filtered_count; // количество найденных записей
        int parent_id; // идентификатор родителя
        if (argc != 3) // проверяем количество аргументов
        {
            printf("Wrong arguments for parent\n"); // сообщаем об ошибке
            show_usage(argv[0]); // подсказываем синтаксис
            return 1;
        }
        if (!string_to_int(argv[2], &parent_id)) // преобразуем аргумент в число
        {
            printf("Parent id must be a number\n"); // пишем об ошибке преобразования
            return 1; 
        }
        filtered_count = filter_by_parent(records, record_count, parent_id, filtered); // выбираем записи по родителю
        if (filtered_count == 0) // проверяем есть ли записи
        {
            printf("No records for parent %d\n", parent_id); // пишем что записей нет
            return 0;
        }
        bubble_sort_records(filtered, filtered_count, "name"); // сортируем найденных учеников по имени
        show_records(filtered, filtered_count, parents, parent_count); // выводим результат
        return 0; 
    }
    if (text_equals(argv[1], "help")) // проверяем команду help
    {
        show_usage(argv[0]); // выводим подсказку
        return 0; 
    }


    printf("Unknown command: %s\n", argv[1]); // если команда не та, сообщаем об этом

    show_usage(argv[0]); // выводим подсказку

    return 1;
}



//./main.o list - показывает бд в данный момент
//./main.o add Maksim Bundera 184913-19431 kkrisdw - добавляет нового ученика
//./main.o remove 281992948 - удаляет ученика по номеру телефона (Только по номеру телефона)
//./main.o sort name/surname/phone/birthday - сортирует бд по имени/фамилии/номеру телефона/дате рождения 
//./main.o group px24 name - показывает всех учеников из группы px24, отсортированных по имени
//./main.o parent 2 - показывает всех учеников с% родителем с id 2


//как заполнять бд ученика ИМЯ | ФАМИЛИЯ | ПЕРСОНАЛЬНЫЙ КОД | ПОЧТА | ГРУППА | ТЕЛЕФОН | ID РОДИТЕЛЯ | ДЕНЬ РОЖДЕНИЯ | МЕСЯЦ РОЖДЕНИЯ | ГОД РОЖДЕНИЯ
