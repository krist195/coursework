#pragma once // просим компилятор включать этот файл только один раз

struct record // структ с данными ученика
{
    char name[100]; // имя ученика
    char surname[100]; // фамилия ученика
    char personal_code[50]; // персональный код полностью
    char email[100]; // электронная почта
    char group[50]; // группа
    char phone[30]; // номер телефона
    int parent_id; // айдишка родителя
    int birth_day; // день рождения
    int birth_month; // месяц рождения
    int birth_year; // год рождения
}; 

struct parent // структ с данными родителя
{
    int id; // айди родителя
    char name[100]; // имя родителя
    char surname[100]; // фамилия родителя
}; 

