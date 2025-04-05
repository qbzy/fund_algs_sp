#include "funcs.h"

/*
    В этом файле минимально:
    - читаем пользователей из файла при старте load_users
    - в цикле предлагаем меню
    - при выходе (case '0') сохраняем пользователей save_users
    - при регистрации (case '2') тоже можно сразу сохранять,
      чтобы не потерять при аварийном завершении.
*/

int main(void) {
    // Загружаем пользователей из файла
    int capacity = 0;
    int counter = 0;
    User *array = load_users("users.txt", &counter, &capacity);
    if (!array) {
        // Если не удалось загрузить, допустим, начнём "с нуля"
        capacity = 4;
        array = malloc(sizeof(User) * capacity);
        if (!array) {
            printf("Memory error!\n");
            return ERR_MEM;
        }
        counter = 0;
    }

    while (1) {
        printf("\nWelcome! Press 1 for Sign in / 2 for Sign up / 0 for Exit:\n> ");
        char choice_line[MAX_LINE];
        if (!read_line(choice_line, sizeof(choice_line))) {
            printf("Input error\n");
            continue;
        }
        if (strlen(choice_line) == 0) {
            printf("Nothing entered.\n");
            continue;
        }

        char choice = choice_line[0];
        switch (choice) {
            case '0': {
                // Сохраняем пользователей в файл
                save_users("users.txt", array, counter);
                // Для отладки выведем логины
                for (int i = 0; i < counter; i++) {
                    printf("\n%s\n", array[i].login);
                }
                printf("Bye!\n");
                free(array);
                return OK;
            }

            case '1': {
                // Sign in
                printf("Enter your login:\n> ");
                char login_buf[MAX_LINE];
                if (!read_line(login_buf, sizeof(login_buf))) {
                    printf("Input error.\n");
                    continue;
                }
                if (!validate_login(login_buf)) {
                    printf("Invalid login!\n");
                    continue;
                }

                printf("Enter your PIN (0..100000):\n> ");
                char pin_line[MAX_LINE];
                if (!read_line(pin_line, sizeof(pin_line))) {
                    printf("Input error.\n");
                    continue;
                }
                int pin_val;
                if (sscanf(pin_line, "%d", &pin_val) != 1) {
                    printf("PIN is not a number\n");
                    continue;
                }
                if (pin_val < 0 || pin_val > 100000) {
                    printf("PIN out of range\n");
                    continue;
                }

                if (counter == 0) {
                    printf("No registered user. Please sign up first.\n");
                    continue;
                }

                int user_idx = -1;
                for (int i = 0; i < counter; i++) {
                    if ((strcmp(array[i].login, login_buf) == 0) &&
                        (array[i].pin == pin_val)) {
                        user_idx = i;
                        break;
                    }
                }
                if (user_idx == -1) {
                    printf("Incorrect login or PIN\n");
                    continue;
                }

                printf("Successfully authorised!\n");
                // Запускаем обработку команд
                while (1) {
                    printf("\nEnter command (Time, Date, Howmuch dd:mm:yy hh:mm:ss -<flag>, Sanctions <login> <limit>, Logout):\n> ");
                    char cmd_line[MAX_LINE];
                    if (!read_line(cmd_line, sizeof(cmd_line))) {
                        printf("Input error\n");
                        break;
                    }
                    if (strlen(cmd_line) == 0) {
                        printf("Empty command\n");
                        continue;
                    }
                    // Если команда Sanctions
                    if (strncmp(cmd_line, "Sanctions", 9) == 0) {
                        char conf[MAX_LINE];
                        printf("Confirm command (enter 12345):\n> ");
                        if (!read_line(conf, sizeof(conf))) {
                            printf("Input error in confirmation\n");
                            continue;
                        }
                        if (strcmp(conf, "12345") != 0) {
                            printf("Incorrect confirmation code\n");
                            continue;
                        }
                    }
                    // Проверка санкций
                    if (array[user_idx].sanctions_flag == 1) {
                        array[user_idx].commands++;
                        if (array[user_idx].commands > array[user_idx].limit) {
                            printf("Command limit (%d) exceeded. Session terminated.\n", array[user_idx].limit);
                            break;
                        }
                    }

                    int logout_flag = command_loop(login_buf, cmd_line, &array, counter, user_idx);
                    if (logout_flag == 1) {
                        printf("Logout.\n");
                        break;
                    }
                }
                break;
            }

            case '2': {
                // Sign up
                printf("Enter new login:\n> ");
                char new_login[MAX_LINE];
                if (!read_line(new_login, sizeof(new_login))) {
                    printf("Input error.\n");
                    continue;
                }
                if (!validate_login(new_login)) {
                    printf("Invalid login!\n");
                    continue;
                }

                printf("Enter new PIN (0..100000):\n> ");
                char pin_line[MAX_LINE];
                if (!read_line(pin_line, sizeof(pin_line))) {
                    printf("Input error.\n");
                    continue;
                }
                int pin_val;
                if (sscanf(pin_line, "%d", &pin_val) != 1) {
                    printf("PIN is not a number!\n");
                    continue;
                }
                if (pin_val < 0 || pin_val > 100000) {
                    printf("PIN out of range!\n");
                    continue;
                }

                // Проверка, что логин не занят
                int exists = 0;
                for (int i = 0; i < counter; i++) {
                    if (strcmp(array[i].login, new_login) == 0) {
                        printf("Login already exists!\n");
                        exists = 1;
                        break;
                    }
                }
                if (exists)
                    continue;

                // Расширение массива, если нужно
                if (counter == capacity) {
                    capacity *= 2;
                    User *tmp = realloc(array, sizeof(User) * capacity);
                    if (!tmp) {
                        printf("No memory to expand!\n");
                        free(array);
                        return ERR_MEM;
                    }
                    array = tmp;
                }

                // Заполняем
                strncpy(array[counter].login, new_login, sizeof(array[counter].login)-1);
                array[counter].login[sizeof(array[counter].login)-1] = '\0';
                array[counter].pin = pin_val;
                array[counter].sanctions_flag = 0;
                array[counter].commands = 0;
                array[counter].limit = 0;
                counter++;
                printf("Registration successful!\n");

                // Сразу сохраняем, чтобы не потерять
                save_users("users.txt", array, counter);
                break;
            }

            default: {
                printf("INVALID INPUT: %s\n", choice_line);
                break;
            }
        }
    }

    // На всякий случай
    free(array);
    return 0;
}
