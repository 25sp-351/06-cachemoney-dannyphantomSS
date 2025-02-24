#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "money_to_words.h"

void test_money_to_words()
{
    assert(strcmp(money_to_words(100), "one dollars and zero cents") == 0);
    assert(strcmp(money_to_words(12345), "one hundred twenty-three dollars and forty-five cents") == 0);
    assert(strcmp(money_to_words(0), "zero dollars and zero cents") == 0);
    printf("All tests passed!\n");

    clear_cache();
}

int main(void)
{
    test_money_to_words();
    return 0;
}

