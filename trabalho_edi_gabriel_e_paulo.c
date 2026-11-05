#include <stdio.h>
#include <stdlib.h>

struct tuser {
    char email[30], name[30];
    int borrow;
    struct tuser *ul, *ur;
}; typedef struct tuser User;

struct tbook {
    char title[30], autor[30], email[30];
    int year, id, status, borrow;
    struct tbook *bl, *br;
}; typedef struct tbook Book;

struct tutree {
    User *root;
}; typedef struct tutree Utree;

struct tbtree {
    Book *root;
}; typedef struct tbtree Btree;



int main()
{
    printf("Hello World");

    return 0;
}