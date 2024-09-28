#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main (void) {
    char string1[50], string2[50];

    printf("String 1: ");
    scanf("%s", string1);
    printf("String 2: ");
    scanf("%s", string2);

    int num_alpha_char = 0;
    for (size_t i = 0; i < strlen(string1); i++) {
        if (isalpha(string1[i]))
            num_alpha_char++;
    }
    printf("Letters in string 1: %d\n", num_alpha_char);

    int num_upper_char = 0;
    for (size_t i = 0; i < strlen(string2); i++) {
        if (isupper(string2[i]))
            num_upper_char++;
    }
    printf("Uppercase in string 2: %d\n", num_upper_char);

    for (size_t i = 0; i < strlen(string1); i++) {
        if (isupper(string1[i])) 
            string1[i] = tolower(string1[i]);
    }

    for (size_t i = 0; i < strlen(string2); i++) {
        if (isupper(string2[i])) 
            string2[i] = tolower(string2[i]);
    }

    printf("String 1 to lower: %s\nString 2 to lower: %s\n", string1, string2);

    if (strcmp(string1, string2) < 0) {
        printf("String are different\nOrdered alphabetically: %s, %s", string1, string2);
    } else if (strcmp(string1, string2) > 0) {
        printf("Strings are different\nOrdered alphabetically: %s, %s", string2, string1);
    } else {
        printf("Strings are equal");
    }

    char string3[50];
    strcpy(string3, string2);

    strcat(string2, string3);
    printf("\nConcatenated string2 and string3: %s", string2);
    
    return 0;
}