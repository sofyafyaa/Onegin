#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define my_assert(condition, ret_on_err)                                                    \
    if (condition) {                                                                        \
        fprintf(stderr, "ERROR %s in FILE %s : %d\n", #condition, __FILE__, __LINE__);        \
        return ret_on_err;                                                                  \
    }

/**
 * @brief this struct contains
 * ptr -- pointer to the first char of string
 * sz -- size of string
 */
typedef struct string_ {
    char* ptr;
    size_t sz;
} string;

/**
 * @brief copy all text from "text_name".txt (fread) to text_buff
 * allocates memory by calloc
 * 
 * @param[out] text_buf 
 * @param[in] text_name 
 * @return size_t -- number of symbols
 */
size_t text_in_buf(char** text_buf, const char* text_name);

/**
 * @brief Split text from text_buf into string struct
 * allocates memory by calloc
 * 
 * @param[in] text_buf 
 * @param[in] text_sz 
 * @param[out] string_mas 
 * @return size_t -- number of strings 
 */
size_t text_to_strings(const char* text_buf, size_t text_sz, string** string_mas);

/**
 * @brief create array of pointers to array of strings
 * Skip empty strings!
 * allocates memory by alloc
 * 
 * @param[in] string_mas -- const array of strings
 * @param[in] string_num -- number of strings in string_mas
 * @param[out] string_ptr -- number of nun 
 * @return size_t 
 */
size_t string_pointers_init(const string* string_mas, size_t string_num, string*** string_ptr);

/**
 * @brief print array of strings according to 
 * order of pointers to array of strings
 * 
 * @param[in] string_ptr -- array of pointers to array of strings
 * @param[in] string_num  -- number of non empty strings
 * @param[in] file -- output file
 * @param[in] mode -- write or clear & write
 * @return int 
 */
int print_strings_by_ptr(string** string_ptr, size_t string_num, const char* file, const char* mode);
/**
 * @brief comparator for qsort
 * compares lexicographically two strings
 * from left to right
 * skips symbols wich are not in the alphabet
 * 
 * @param[int] s1 - pointer to a pointer on string
 * @param[int] s2 
 * @return int --  >0 if s1 > s2
 */
int comparator_lr(const void* s1, const void* s2);

/**
 * @brief comparator for qsort
 * compares lexicographically two strings
 * from left to right
 * skips symbols wich are not in the alphabet
 * 
 * @param s1[in] - pointer to a pointer on string
 * @param s2[in] - pointer to a pointer on string
 * @return int 
 */
int comparator_rl(const void *s1, const void *s2);

void my_qsort (void* base, size_t num, size_t size, int (*comparator)(const void*,const void*));
