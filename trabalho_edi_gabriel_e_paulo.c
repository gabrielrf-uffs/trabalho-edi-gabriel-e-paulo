#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void initUlist(Ulist *ul) {
    ul->head=NULL;
    ul->tail=NULL;
}

void addUser(Ulist *ul) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    User *u = malloc(sizeof(User));
    u->borrow=0;
    printf("Insira seu email:\n");
    fgets(u->email, MAX, stdin);
    if (ul->head==NULL){
        printf("Digite seu nome:\n");
        fgets(u->name, MAX, stdin);
        ul->head=u;
        ul->tail=u;
    } else {
        User *aux = ul->head;
        for(aux;aux!=NULL;aux=aux->nextu) {
            if (strcmp(aux->email, u->email) == 0) {
                printf("Email já cadastrado!\n");
                return;
            }
        }
        printf("Digite seu nome:\n");
        fgets(u->name, MAX, stdin);
        ul->tail->nextu=u;
        ul->tail=u;
    }
}

void addBook() {
    
}

void add(Ulist *ul) {
    printf("O que deseja cadastrar?\n1.Livro\n2.Usuário\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op) {
        case 0: printf("Voltando!\n");
                break;
        case 1: addBook();
                break;
        case 2: addUser(ul);
                break;
    }
}

void consultUser(Ulist *ul) {
    int c;
    printf("Consultar por?\n1.Email\n2.Nome\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    User *aux;
    char a[MAX];
    switch(op) {
        case 0: printf("Voltando!\n");
                break;
        case 1: printf("Digite o email:\n");
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(a, MAX, stdin);
                for(aux=ul->head;aux!=NULL;aux=aux->nextu) {
                    if (strcmp(aux->email, a) == 0) break;
                }
                if (aux==NULL) printf("Email não encontrado!\n");
                else printf("Email:%sNome:%sLivros em posse:%d\n",&aux->email,&aux->name,&aux->borrow);
                break;
        case 2: printf("Digite o nome:\n");
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(a, MAX, stdin);
                for(aux=ul->head;aux!=NULL;aux=aux->nextu) {
                    if (strcmp(aux->email, a) == 0) break;
                }
                if (aux==NULL) printf("Nome não encontrado!\n");
                else printf("Email:%sNome:%sLivros em posse:%d\n",&aux->email,&aux->name,&aux->borrow);
                break;
    }
}

void consultBook() {

}

void consultBorrow() {

}

void consult(Ulist *ul) {
    printf("O que deseja consultar?\n1.Livro\n2.Usuário\n3.Empréstimos\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                break;
        case 1: consultBook();
                break;
        case 2: consultUser(ul);
                break;
        case 3: consultBorrow();
                break;
    }
}

void updateUser(Ulist *ul) {
    int c;
    User *aux;
    char a[MAX];
    printf("Digite o email:\n");
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(a, MAX, stdin);
    for(aux=ul->head;aux!=NULL;aux=aux->nextu) {
        if (strcmp(aux->email, a) == 0) break;
    }
    if (aux==NULL){
        printf("Email não encontrado!\n");
        return;
    }
    printf("Email:%sNome:%sLivros em posse:%d\nQual o novo nome?\n",&aux->email,&aux->name,&aux->borrow);
    fgets(a, MAX, stdin);
    strcpy(aux->name,a);
}

void updateBook() {
    
}

void update(Ulist *ul) {
    printf("O que deseja atualizar?\n1.Livro\n2.Usuário\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                break;
        case 1: updateBook();
                break;
        case 2: updateUser(ul);
                break;
    }
}

void deleteUser(Ulist *ul) {
    int c, op;
    User *aux, *prev;
    char a[MAX];
    aux=ul->head;
    prev=NULL;
    printf("Digite o email:\n");
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(a, MAX, stdin);
    for(aux;aux!=NULL;aux=aux->nextu) {
        if (strcmp(aux->email, a) == 0) break;
        prev=aux;
    }
    if (aux==NULL){
        printf("Email não encontrado!\n");
        return;
    }
    printf("Email:%sNome:%sLivros em posse:%d\nTem certeza que deseja deletar?\n1.Sim\n0.Não\n",&aux->email,&aux->name,&aux->borrow);
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                return;
        case 1: if (prev==NULL) {
                    ul->head=NULL;
                    ul->tail=NULL;
                }
                else {
                    prev->nextu=aux->nextu;
                    ul->tail=prev;
                }
                return;
    }
}

void deleteBook() {
    
}

void delete(Ulist *ul) {
    printf("O que deseja deletar?\n1.Livro\n2.Usuário\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                break;
        case 1: deleteBook();
                break;
        case 2: deleteUser(ul);
                break;
    }
}

int main()
{
    Ulist *userl = malloc(sizeof(Ulist));
    initUlist(userl);
    int o = 1;
    while (o!=0) {
        printf("O que deseja fazer?\n1. Cadastro\n2. Consulta\n3. Atualização\n4. Exclusão\n5. Empréstimo\n6. Devolução\n0. Sair\n");
        scanf("%d",&o);
        switch(o) {
            case 0: printf("Saindo!\n");
                    return 0;
            case 1: add(userl);
                    break;
            case 2: consult(userl);
                    break;
            case 3: update(userl);
                    break;
            case 4: delete(userl);
                    break;
        }
    }
    return 0;
}
