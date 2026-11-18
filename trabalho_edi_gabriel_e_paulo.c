#include <stdio.h>
#include <stdlib.h>
#define MAX 30

struct tuser {
    char email[MAX], name[MAX];
    int borrow;
    struct tuser *nextu;
}; typedef struct tuser User;

struct tbook {
    char title[MAX], autor[MAX], email[MAX];
    int year, id, status, borrow;
    struct tbook *bl, *br;
}; typedef struct tbook Book;

struct lsulist {
    User *head, *tail;
}; typedef struct lsulist Ulist;

struct tbtree {
    Book *root;
}; typedef struct tbtree Btree;

void addUser(Ulist *ul) {
    User *u = malloc(sizeof(User));
    printf("Insira seu email:\n");
    fgets(u->email, MAX, stdin);
    if (ul->head==NULL){
        printf("Digite seu nome:\n");
        fgets(u->name, MAX, stdin);
        ul->head=u;
        ul->tail=u;
    }
}

void addBook() {
    
}

void add() {

}

int main()
{
    Ulist *userl = malloc(sizeof(Ulist));
    addUser(userl);

    return 0;
}
