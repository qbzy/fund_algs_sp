#include "funcs.h"

/* ========== Работа с файлом пользователей ========== */

/* Пример: текстовый формат
   login pin sanctions_flag limit commands
   по одной строке на пользователя */

User *load_users(const char *filename, int *pcount, int *pcapacity) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        // Файл отсутствует => вернём NULL
        return NULL;
    }

    // Начнём с capacity = 4 (или другой)
    int capacity = 4;
    User *arr = malloc(sizeof(User)*capacity);
    if (!arr) {
        fclose(fp);
        return NULL;
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Убираем \n
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';
        if (strlen(line) == 0) {
            // пустая строка
            continue;
        }
        // Парсим: login pin sf limit commands
        char tmp_login[16];
        int tmp_pin, tmp_sf, tmp_lim, tmp_cmd;
        int fields = sscanf(line, "%15s %d %d %d %d",
                            tmp_login, &tmp_pin, &tmp_sf, &tmp_lim, &tmp_cmd);
        if (fields < 5) {
            printf("Error parse line: %s\n", line);
            continue; // пропустим эту строку
        }

        // Валидируем логин, PIN и т.д.
        if (!validate_login(tmp_login)) {
            printf("Invalid login in line: %s\n", line);
            continue;
        }
        if (tmp_pin < 0 || tmp_pin > 100000) {
            printf("PIN out of range in line: %s\n", line);
            continue;
        }
        if (tmp_sf < 0 || tmp_sf > 1) {
            printf("sanctions_flag must be 0 or 1 in line: %s\n", line);
            continue;
        }
        if (tmp_lim < 0) {
            printf("limit must be >=0 in line: %s\n", line);
            continue;
        }
        if (tmp_cmd < 0) {
            printf("commands must be >=0 in line: %s\n", line);
            continue;
        }

        // При необходимости увеличим массив
        if (count == capacity) {
            capacity *= 2;
            User *tmp = realloc(arr, sizeof(User)*capacity);
            if (!tmp) {
                fclose(fp);
                free(arr);
                return NULL;
            }
            arr = tmp;
        }
        // Заполняем запись
        strncpy(arr[count].login, tmp_login, 6);
        arr[count].login[6] = '\0';
        arr[count].pin = tmp_pin;
        arr[count].sanctions_flag = tmp_sf;
        arr[count].limit = tmp_lim;
        arr[count].commands = tmp_cmd;
        count++;
    }
    fclose(fp);

    *pcount = count;
    *pcapacity = capacity;
    return arr;
}

void save_users(const char *filename, const User *arr, int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error saving file %s\n", filename);
        return;
    }
    // Пишем по строкам
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %d %d %d\n",
                arr[i].login,
                arr[i].pin,
                arr[i].sanctions_flag,
                arr[i].limit,
                arr[i].commands);
    }
    fclose(fp);
    printf("Saved %d users to %s (text mode)\n", count, filename);
}


/* ========== Остальные функции ========== */

int read_line(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin))
        return 0;
    char *nl = strchr(buf, '\n');
    if (nl)
        *nl = '\0';
    return 1;
}

int validate_login(const char *login) {
    size_t len = strlen(login);
    if (len == 0 || len > 6)
        return 0;
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)login[i]))
            return 0;
    }
    return 1;
}

/* мини-вспомогательные функции */
static bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
static int days_in_month(int month, int year) {
    if (month == 2)
        return is_leap_year(year) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

bool is_valid_date_time(DateTime dt) {
    if (dt.year < 1 || dt.month < 1 || dt.month > 12 ||
        dt.day < 1 || dt.day > days_in_month(dt.month, dt.year) ||
        dt.hour < 0 || dt.hour > 23 ||
        dt.minute < 0 || dt.minute > 59 ||
        dt.second < 0 || dt.second > 59)
        return false;
    return true;
}

long long time_difference(DateTime dt1, DateTime dt2) {
    long long total1 = 0, total2 = 0;
    for (int y = 1; y < dt1.year; y++)
        total1 += is_leap_year(y) ? 366LL * 86400 : 365LL * 86400;
    for (int m = 1; m < dt1.month; m++)
        total1 += days_in_month(m, dt1.year) * 86400LL;
    total1 += (dt1.day - 1) * 86400LL + dt1.hour * 3600 + dt1.minute * 60 + dt1.second;

    for (int y = 1; y < dt2.year; y++)
        total2 += is_leap_year(y) ? 366LL * 86400 : 365LL * 86400;
    for (int m = 1; m < dt2.month; m++)
        total2 += days_in_month(m, dt2.year) * 86400LL;
    total2 += (dt2.day - 1) * 86400LL + dt2.hour * 3600 + dt2.minute * 60 + dt2.second;

    return total1 - total2;
}

/* Реализация cmd_time/cmd_date в виде статических функций */
static void cmd_time(void) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    printf("Текущее время: %02d:%02d:%02d\n", tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
}
static void cmd_date(void) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    printf("Текущая дата: %02d:%02d:%04d\n", tm_now->tm_mday, tm_now->tm_mon + 1, tm_now->tm_year + 1900);
}

enum Errors sanctions(User **arr, int counter, const char *user, int lim) {
    if (!arr || !(*arr) || !user)
        return ERR_PTR;

    int cur_user = -1;
    for (int i = 0; i < counter; i++) {
        if (strcmp((*arr)[i].login, user) == 0)
            cur_user = i;
    }
    if (cur_user == -1 || (*arr)[cur_user].sanctions_flag || lim < 0 || lim == INT_MAX)
        return ERR_SANC;

    (*arr)[cur_user].sanctions_flag = 1;
    (*arr)[cur_user].limit = lim;
    return OK;
}

int command_loop(const char *userLogin, const char *command, User **arr, int counter, int user_idx) {
    if (strcmp(command, "Time") == 0) {
        cmd_time();
        return 0;
    }
    if (strcmp(command, "Date") == 0) {
        cmd_date();
        return 0;
    }
    if (strcmp(command, "Logout") == 0)
        return 1;

    // Howmuch
    DateTime dt;
    char flag;
    if (sscanf(command, "Howmuch %d:%d:%d %d:%d:%d -%c",
               &dt.day, &dt.month, &dt.year,
               &dt.hour, &dt.minute, &dt.second, &flag) == 7) {
        if (!is_valid_date_time(dt)) {
            printf("Invalid date/time format\n");
            return 0;
        }
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        DateTime dt_now = {
                .day = tm_now->tm_mday,
                .month = tm_now->tm_mon + 1,
                .year = tm_now->tm_year + 1900,
                .hour = tm_now->tm_hour,
                .minute = tm_now->tm_min,
                .second = tm_now->tm_sec
        };
        long long diff = time_difference(dt_now, dt);
        switch (flag) {
            case 's': printf("Result: %lld seconds\n", diff); break;
            case 'm': printf("Result: %lld minutes\n", diff / 60); break;
            case 'h': printf("Result: %lld hours\n", diff / 3600); break;
            case 'y': printf("Result: %d years\n", dt_now.year - dt.year); break;
            default: printf("Unknown flag\n"); break;
        }
        return 0;
    }

    // Sanctions
    {
        char user[32];
        int lim;
        if (sscanf(command, "Sanctions %31s %d", user, &lim) == 2) {
            enum Errors st = sanctions(arr, counter, user, lim);
            if (st == OK)
                printf("Sanctions set for user %s with limit %d\n", user, lim);
            else
                printf("Error setting sanctions: %d\n", st);
            return 0;
        }
    }

    printf("Unknown command: %s\n", command);
    return 0;
}
