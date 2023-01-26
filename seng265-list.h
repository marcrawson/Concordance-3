#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define LIST_MAXLEN_TEXT 100

typedef struct node_t {
    char text[LIST_MAXLEN_TEXT];
    struct node_t *next;
} node_t;

typedef struct node_k {
    char keyword[LIST_MAXLEN_TEXT];
    char line[LIST_MAXLEN_TEXT];
    struct node_k *next;
} node_k;

typedef struct node_c {
    char ch;
    struct node_c *next;
} node_c;

node_t *new_node(char *);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void    apply(node_t *, void(*fn)(node_t *, void *), void *arg);
node_t *add_inorder(node_t *, node_t *);
int contains(node_t *, char *);

node_k *new_node_k(char *, char *);
node_k *add_end_k(node_k *, node_k *);
node_k *add_inorder_k(node_k *, node_k *);
node_k *add_inorder_k_2(node_k *, node_k *);

node_c *new_node_c(char);
node_c *add_end_c(node_c *, node_c *);

#endif