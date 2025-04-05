#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#define MAX_LINE 256

enum Errors {
    OK = 0,
    INVALID_INPUT,
    ERR_LOGIN,
    ERR_MEM,
    ERR_PTR,
    ERR_SANC
};

typedef struct {
    char login[7];
    int pin;
    int sanctions_flag;
    int limit;
    int commands;
} User;

typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
} DateTime;

// Функции работы с пользователями (сериализация/десериализация)
User *load_users(const char *filename, int *pcount, int *pcapacity);
void save_users(const char *filename, const User *arr, int count);

// Остальные
int read_line(char *buf, size_t size);
int validate_login(const char *login);
bool is_valid_date_time(DateTime dt);
long long time_difference(DateTime dt1, DateTime dt2);
enum Errors sanctions(User **arr, int counter, const char *user, int lim);
int command_loop(const char *userLogin, const char *command, User **arr, int counter, int user_idx);


