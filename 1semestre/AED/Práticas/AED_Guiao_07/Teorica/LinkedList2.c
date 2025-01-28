#include <stdlib.h>
#include <stdio.h>

struct node {
    int value;
    struct node *next;
};
typedef struct node node_t;

void print_list(node_t *head) {
    node_t *tmp = head;
    while(tmp != NULL) {
        printf(" %d |", tmp);
        tmp = tmp->next;
    }
}

node_t *create_new_node(int value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}

int main() {
    node_t *head = NULL;
    node_t *tmp;

    for(int i = 0; i < 25; i++) {
        tmp = create_new_node(i);
        insert_at_head(head, tmp);
    }

    print_list(head);

    return 0;
}