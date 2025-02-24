#include <stdio.h>
#include <stdlib.h>
#include "money_to_words.h"

int main(void)
{
    long input_cents;
    while (scanf("%ld", &input_cents) == 1) {
        char *words = money_to_words(input_cents);
        printf("%ld = %s\n", input_cents, words);
        free(words);
    }
    
    clear_cache();
    return 0;
}

