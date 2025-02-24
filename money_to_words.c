#include "money_to_words.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMO_LIMIT 150000

static char *memo_cache[MEMO_LIMIT] = { NULL };

static char *number_to_words(long number);
static char *convert_three_digits(int num);

char *money_to_words(long money_in_cents)
{
    if (money_in_cents >= 0 && money_in_cents < MEMO_LIMIT &&
        memo_cache[money_in_cents] != NULL) {
        return memo_cache[money_in_cents];
    }

    long dollars = money_in_cents / 100;
    long cents = money_in_cents % 100;

    char *dollar_str = number_to_words(dollars);
    char *cent_str = number_to_words(cents);

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s dollars and %s cents",
             dollar_str, cent_str);

    char *result = (char *)malloc(strlen(buffer) + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, buffer);

    free(dollar_str);
    free(cent_str);

    if (money_in_cents >= 0 && money_in_cents < MEMO_LIMIT) {
        memo_cache[money_in_cents] = result;
    }

    return result;
}

static char *number_to_words(long number)
{
    if (number == 0) {
        char *zero_text = (char *)malloc(5);
        if (zero_text == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        strcpy(zero_text, "zero");
        return zero_text;
    }

    static const char *scales[] = { "", "thousand", "million", "billion" };
    char *chunks[32] = { NULL };
    int chunk_idx = 0;
    long temp_val = number;

    while (temp_val > 0) {
        int part = temp_val % 1000;
        temp_val /= 1000;

        if (part != 0) {
            char *text_part = convert_three_digits(part);
            if (scales[chunk_idx][0] != '\0') {
                char combo[256];
                snprintf(combo, sizeof(combo), "%s %s", text_part, scales[chunk_idx]);
                free(text_part);
                text_part = (char *)malloc(strlen(combo) + 1);
                if (text_part == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                strcpy(text_part, combo);
            }
            chunks[chunk_idx] = text_part;
        }
        chunk_idx++;
    }

    char combined[1024] = "";
    for (int i = chunk_idx - 1; i >= 0; i--) {
        if (chunks[i] != NULL) {
            strcat(combined, chunks[i]);
            free(chunks[i]);
            if (i > 0) {
                strcat(combined, " ");
            }
        }
    }

    char *final_str = (char *)malloc(strlen(combined) + 1);
    if (final_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(final_str, combined);
    return final_str;
}

static char *convert_three_digits(int num)
{
    static const char *ones[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
        "seventeen", "eighteen", "nineteen"
    };

    static const char *tens[] = {
        "zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    char buffer[256] = "";

    if (num >= 100) {
        int hundreds = num / 100;
        int remainder = num % 100;
        strcat(buffer, ones[hundreds]);
        strcat(buffer, " hundred");
        if (remainder > 0) {
            strcat(buffer, " ");
        }
        num = remainder;
    }

    if (num >= 20) {
        int tens_place = num / 10;
        int ones_place = num % 10;
        strcat(buffer, tens[tens_place]);
        if (ones_place > 0) {
            strcat(buffer, "-");
            strcat(buffer, ones[ones_place]);
        }
    } else if (num > 0) {
        strcat(buffer, ones[num]);
    }

    char *res = (char *)malloc(strlen(buffer) + 1);
    if (res == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(res, buffer);
    return res;
}

void clear_cache(void)
{
    for (int i = 0; i < MEMO_LIMIT; i++) {
        free(memo_cache[i]);
        memo_cache[i] = NULL;
    }
}

