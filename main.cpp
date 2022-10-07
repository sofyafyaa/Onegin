/**
 * @file main.cpp
 * @author Sofyaa
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "onegin.h"

/**
 * @brief this program sort strings
 * and print it in the ../build/output.txt
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char*argv[]) {
    char* text_name = (char *)"Eugene_Oneguine.txt";
    char* output = (char *)"output.txt";

    char* text_buf;
    size_t text_sz = text_in_buf(&text_buf, text_name);
    
    string* str_mas;
    size_t str_num = text_to_strings(text_buf, text_sz, &str_mas);

    string** str_ptr_lr;
    size_t non_empty_str_num = string_pointers_init(str_mas, str_num, &str_ptr_lr); //pointer to massive of pointers
    qsort((void*) str_ptr_lr, non_empty_str_num, sizeof(string*), comparator_lr);
    print_strings_by_ptr(str_ptr_lr, non_empty_str_num, output, "w");

    printf("Non empty strings: %ld\n", non_empty_str_num);

    string** str_ptr_rl;
    string_pointers_init(str_mas, str_num, &str_ptr_rl);
    qsort((void*) str_ptr_rl, non_empty_str_num, sizeof(string*), comparator_rl);
    print_strings_by_ptr(str_ptr_rl, non_empty_str_num, output, "a");

    string** str_ptr;
    string_pointers_init(str_mas, str_num, &str_ptr);
    print_strings_by_ptr(str_ptr, non_empty_str_num, output, "a");

    free(str_mas); 
    free(str_ptr_lr); 
    free(str_ptr_rl); 
    free(str_ptr);

    return 0;
}