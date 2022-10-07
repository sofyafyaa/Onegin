#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "onegin.h"

#define TEST_MODE

#ifdef TEST_MODE
bool TEST = true;
#else 
bool TEST  = false;
#endif

size_t text_in_buf(char** text_buf, const char* text_name) {
    my_assert(text_buf == NULL, -1);
    my_assert(text_name == NULL, -1);

    struct stat statbuf;
    stat(text_name, &statbuf);
    size_t text_size = statbuf.st_size;
    
    (*text_buf) = (char*)calloc((text_size + 10), sizeof(char));
    my_assert(text_buf == NULL, -1);

    FILE* text = fopen(text_name, "r");
    my_assert(text == NULL, -1);

    size_t sucnum = fread(*text_buf, sizeof(char), text_size, text);

    if (TEST) {
        FILE* logs = fopen("logs.txt", "a");
        if(!logs) {
            printf("Cannot open the logs.txt file\n");
        }
        if (sucnum == text_size)
            fprintf(logs, "Read successful! (%ld chars = %ld)\n", sucnum, text_size);
        else
            fprintf(logs, "Read unsuccessful! (%ld chars = %ld)\n", sucnum, text_size);
        
        char* it = *text_buf;
        while(it != *text_buf + text_size) {
            putc(*it++, logs);
        }
        fprintf(logs, "\n");
        fclose(logs);
    }

    fclose(text);
    return text_size;
}

size_t text_to_strings(const char* text_buf, size_t text_sz, string** string_mas) {
    my_assert(text_buf == NULL, -1);
    my_assert(string_mas == NULL, -1);

    FILE* logs = fopen("logs.txt", "a");
    if(!logs) {
        printf("Cannot open the logs.txt file\n");
        TEST = 0;
    }
    
    size_t string_num = 1;

    for (char* it = (char*) text_buf; (it = strchr(it + 1, '\n')) != NULL; string_num++)  {} //count number of strings

    (*string_mas) = (string*)calloc(string_num, sizeof(string));
    my_assert(string_mas == NULL, -1); //calloc memory for massive of structures

    size_t line = 1;
    (*string_mas)[0].ptr = (char*) text_buf;
    for (char* it = (char*) text_buf; (it = strchr(it + 1, '\n')) != NULL; line++) {
        *it = '\0';
        (*string_mas)[line].ptr = it + 1;
        (*string_mas)[line - 1].sz = it - (*string_mas)[line - 1].ptr;
    }

    (*string_mas)[line - 1].sz = (*string_mas)[0].ptr + text_sz - (*string_mas)[line - 1].ptr;

    if (TEST) {
        for (size_t i = 0; i < line; i++) {
            fprintf(logs, "[%ld] SIZE: %ld\n%s\n\n", i, (*string_mas)[i].sz, (*string_mas)[i].ptr);
        }
    }
    fclose(logs);

    return line;
}

size_t string_pointers_init(const string* string_mas, size_t string_num, string*** string_ptr) {
    my_assert(string_ptr == NULL, -1)
    my_assert(string_mas == NULL, -1);

    FILE* logs = fopen("logs.txt", "w");
    if(!logs) {
        printf("Cannot open the logs.txt file\n");
        TEST = 0;
    }

    (*string_ptr) = (string**)calloc(string_num, sizeof(string*));
    my_assert(*string_ptr == NULL, -1);

    size_t j = 0;
    for (size_t i = 0; (i < string_num) && (j < string_num); i++) {
        if (string_mas[i].sz != 0) {
        (*string_ptr)[j] = (string*) &(string_mas[i]);
        if (TEST) fprintf (logs, "str_ptr[%ld] = %s\n", j, (*string_ptr)[j]->ptr);
        j++;
        }
        else {
            if (TEST) fprintf (logs, "str_ptr[%ld] = Empty!\n", j);
        }
    }

    fclose(logs);
    return j;
}

int comparator_lr(const void* s1, const void* s2) {

    char* it1 = (*((string**)s1))->ptr;
    char* it2 = (*((string**)s2))->ptr;

    while (*it1 != '\0' || *it2 != '\0') {
        if (!isalpha(*it1)) {
            it1++;
            continue;
        }
        if (!isalpha(*it2)) {
            it2++;
            continue;
        }

        if (*it1 == *it2) {
            it1++;
            it2++;
            continue;
        }

        return (*it1 - *it2);
    }

    if (*it1 == '\0' && isalpha(*it2))
        return 1;

    if (*it2 == '\0' && isalpha(*it1))
        return -1;

    return 0;
}

int comparator_rl(const void* s1, const void* s2) {
    char* it1 = (*((string**)s1))->ptr + (*((string**)s1))->sz - 1;
    char* it2 = (*((string**)s2))->ptr + (*((string**)s2))->sz - 1;

    do {
            if (!isalpha(*it1)) {
            it1--;
            continue;
        }

        if (!isalpha(*it2)) {
            it2--;
            continue;
        }
        if (*it1 == *it2) {
            it1--;
            it2--;
            continue;
        }

        return (*it1 - *it2);
    } while (*it1 != '\0' || *it2 != '\0');
    

    if (*it1 == '\0')
        return 1;

    if (*it2 == '\0')
        return -1;
    return 0;
}

int print_strings_by_ptr(string** string_ptr, size_t string_num, const char* file, const char* mode) {
    my_assert(file == NULL, -1); my_assert(string_ptr == NULL, -1);

    FILE* out = fopen(file, mode);
    my_assert(out == NULL, -1);

    for (size_t i = 0; i < string_num; i++) {
        fprintf(out, "%s\n", string_ptr[i]->ptr);
    }
    fprintf(out, 
    "\n______________________________________________________\n______________________________________________________\n______________________________________________________\n______________________________________________________\n______________________________________________________\n\n");
    
    fclose(out);
    return 0;
}