/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"


node_t *new_node(char *text) {
    assert( text != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    strncpy(temp->text, text, LIST_MAXLEN_TEXT);
    temp->next = NULL;

    return temp;
}


node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }
    node_t *temp = list->next;
    free(list);
    return temp;
}


void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}

node_t *add_inorder(node_t *head, node_t *new) {
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (head == NULL) {
        return new;
    }

    for (curr = head; curr != NULL; curr = curr->next) {
        if (strcmp(new->text, curr->text) > 0) {
            prev = curr;
        } else {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return head;
    }
}

int contains(node_t *head, char *string) {
    while(head != NULL) {
        if (strcmp(head->text, string) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

node_k *new_node_k(char *keyword, char *line) {
    assert(keyword != NULL);
    assert(line != NULL);

    node_k *temp = (node_k *)emalloc(sizeof(node_k));

    strncpy(temp->keyword, keyword, LIST_MAXLEN_TEXT);
    strncpy(temp->line, line, LIST_MAXLEN_TEXT);
    temp->next = NULL;

    return temp;
}

node_k *add_end_k(node_k *list, node_k *new) {
    node_k *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

node_k *add_inorder_k(node_k *head, node_k *new) {
    node_k *prev = NULL;
    node_k *curr = NULL;

    if (head == NULL) {
        return new;
    }

    for (curr = head; curr != NULL; curr = curr->next) {
        if (strcmp(new->keyword, curr->keyword) > 0) {
            prev = curr;
        } else {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return head;
    }
}

node_k *add_inorder_k_2(node_k *head, node_k *new) {
    node_k *prev = NULL;
    node_k *curr = NULL;

    if (head == NULL) {
        return new;
    }

    for (curr = head; curr != NULL; curr = curr->next) {
        if (strcmp(new->keyword, curr->keyword) > 0) {
            prev = curr;
        } else if (strcmp(new->keyword, curr->keyword) == 0) {
            strcmp(new->line, curr->line) > 0;
                prev = curr;
        } else {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return head;
    }
}

node_c *new_node_c(char character) {
    // assert(character != NULL); // causes warning

    node_c *temp = (node_c *)emalloc(sizeof(node_c));

    temp->ch = character;
    temp->next = NULL;

    return temp;
}

node_c *add_end_c(node_c *head, node_c *new) {
    node_c *curr;

    if (head == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = head; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return head;
}

// node_l *new_node_l(char *keyword, char *line, node_c *char_l) {
//     node_l *temp = (node_l *)emalloc(sizeof(node_l));

//     strncpy(temp->keyword, keyword, LIST_MAXLEN_TEXT);
//     strncpy(temp->line, line, LIST_MAXLEN_TEXT);
//     temp->ch_line = *char_l;
//     temp->next = NULL;

//     return temp;
// }

// node_l *add_end_l(node_l *head, node_l *new) {
//     node_l *curr;

//     if (head == NULL) {
//         new->next = NULL;
//         return new;
//     }

//     for (curr = head; curr->next != NULL; curr = curr->next);
//     curr->next = new;
//     new->next = NULL;
//     return head;
// }

// node_l *add_inorder_l(node_l *head, node_l *new) {
//     node_l *prev = NULL;
//     node_l *curr = NULL;

//     if (head == NULL) {
//         return new;
//     }

//     for (curr = head; curr != NULL; curr = curr->next) {
//         if (strcmp(new->line, curr->line) > 0) {
//             prev = curr;
//         } else {
//             break;
//         }
//     }

//     new->next = curr;

//     if (prev == NULL) {
//         return new;
//     } else {
//         prev->next = new;
//         return head;
//     }
// }

// typedef struct node_l {
//     char keyword[LIST_MAXLEN_TEXT];
//     char line[LIST_MAXLEN_TEXT];
//     node_c ch_line;
//     struct node_l *next;
// } node_l;