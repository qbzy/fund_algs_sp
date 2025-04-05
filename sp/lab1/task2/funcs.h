#pragma once
#include <stdbool.h>
#include <stdio.h>


#define PATH_MAX 256
#define BUFFER_SIZE 4096

typedef enum {
    OK,
    ERROR,
    ERROR_INPUT,
    ERROR_FILE,
    ERROR_MEMORY
} Error;

Error handle_xor(int N, char **files, int num_files);

Error handle_mask(const char *mask_str, char **files, int num_files);

Error handle_copy(int N, char **files, int num_files);

Error handle_find(const char *search_str, char **files, int num_files);


