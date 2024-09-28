#include <stdio.h>

int main() {
    char first_name[30];
    char last_name[30];

    printf("Enter your first name:\n");
    scanf("%s", first_name);

    printf("Enter your last name:\n");
    scanf("%s", last_name);

    printf("Hello %s %s!\n", first_name, last_name);

    return 0;
}