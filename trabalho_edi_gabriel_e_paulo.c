#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

struct lsuser {
    char email[MAX], name[MAX];
    struct lsuser *nextu;
}; typedef struct lsuser User;

struct lsbook {
    char title[MAX], author[MAX], email[MAX];
    int year, id, status;
    struct lsbook *nextb;
}; typedef struct lsbook Book;

struct lsulist {
    User *head, *tail;
}; typedef struct lsulist Ulist;

struct lsblist {
    Book *head, *tail;
}; typedef struct lsblist Blist;

void initUlist(Ulist *ul) {
    ul->head=NULL;
    ul->tail=NULL;
}

void initBlist(Blist *bl) {
    bl->head=NULL;
    bl->tail=NULL;
}

void addUser(Ulist *ul) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    User *u = malloc(sizeof(User));
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

void addBook(Blist *bl) {
    int c, y;
    while ((c = getchar()) != '\n' && c != EOF);
    Book *b = malloc(sizeof(Book));
    b->status=0;
    printf("Insira o nome do livro:\n");
    fgets(b->title, MAX, stdin);
    printf("Insira o autor do livro:\n");
    fgets(b->author, MAX, stdin);
    printf("Insira o ano de publicação do livro:\n");
    scanf("%d",&y);
    b->year=y;
    if (bl->head==NULL){
        bl->head=b;
        bl->tail=b;
        b->id=1;
    } else {
        Book *aux = bl->head;
        if (aux->id==2) {
            b->nextb=aux;
            bl->head=b;
            b->id=1;
            return;
        }
        for(aux;aux!=NULL;aux=aux->nextb) {
            if (aux->nextb==NULL) break;
            else {
                if ((aux->id)+1<aux->nextb->id) {
                    b->id=(aux->id)+1;
                    b->nextb=aux->nextb;
                    aux->nextb=b;
                    return;
                }
            }
        }
        b->id=(bl->tail->id)+1;
        bl->tail->nextb=b;
        bl->tail=b;
    }
}

void add(Ulist *ul, Blist *bl) {
    printf("O que deseja cadastrar?\n1.Livro\n2.Usuário\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op) {
        case 0: printf("Voltando!\n");
                break;
        case 1: addBook(bl);
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
                else printf("Email:%sNome:%s",&aux->email,&aux->name);
                break;
        case 2: printf("Digite o nome:\n");
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(a, MAX, stdin);
                for(aux=ul->head;aux!=NULL;aux=aux->nextu) {
                    if (strcmp(aux->email, a) == 0) break;
                }
                if (aux==NULL) printf("Nome não encontrado!\n");
                else printf("Email:%sNome:%s",&aux->email,&aux->name);
                break;
    }
}

void consultBook(Blist *bl) {
    int c, id;
    printf("Consultar por?\n1.Id\n2.Autor\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    Book *aux;
    char a[MAX];
    switch(op) {
        case 0: printf("Voltando!\n");
                break;
        case 1: printf("Digite o id:\n");
                scanf("%d",&id);
                for(aux=bl->head;aux!=NULL;aux=aux->nextb) {
                    if (id==aux->id) break;
                }
                if (aux==NULL) printf("Livro não encontrado!\n");
                else {
                    if (aux->status==0) {
                        printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Disponível\n",&aux->title,&aux->author,aux->year);
                    } else {
                        printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Emprestado\n",&aux->title,&aux->author,aux->year);
                    }
                }
                break;
        case 2: printf("Digite o autor:\n");
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(a, MAX, stdin);
                int n = 0;
                for(aux=bl->head;aux!=NULL;aux=aux->nextb) {
                    if (strcmp(aux->author, a) == 0) {
                        n=1;
                        if (aux->status==0) {
                            printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Disponível\n\n",&aux->title,&aux->author,aux->year);
                        } else {
                            printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Emprestado\n\n",&aux->title,&aux->author,aux->year);
                        }
                    }
                }
                if (n==0) printf("Autor não encontrado!\n");
                break;
    }
}

void consultBorrow(Blist *bl) {
    int c, n;
    printf("Consultar?\n1.Sim, digite o email\n0.Não,voltar\n");
    int op = 0;
    scanf("%d",&op);
    Book *aux;
    char a[MAX];
    switch(op) {
        case 0: printf("Voltando!\n");
                break;
        case 1: printf("Digite o email:\n");
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(a, MAX, stdin);
                for(aux=bl->head;aux!=NULL;aux=aux->nextb) {
                    if (strcmp(aux->email, a) == 0) {
                        n=1;
                        printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Emprestado\n",&aux->title,&aux->author,aux->year);
                    }
                }
                if (n==0) printf("Nenhum livro emprestado para esse email!\n");
                break;
    }
}

void consult(Ulist *ul, Blist *bl) {
    printf("O que deseja consultar?\n1.Livro\n2.Usuário\n3.Empréstimos\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                break;
        case 1: consultBook(bl);
                break;
        case 2: consultUser(ul);
                break;
        case 3: consultBorrow(bl);
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
    printf("Email:%sNome:%sQual o novo nome?\n",&aux->email,&aux->name);
    fgets(a, MAX, stdin);
    strcpy(aux->name,a);
}

void updateBook(Blist *bl) {
    int c, id, op, y;
    Book *aux;
    char a[MAX];
    printf("Digite o id:\n");
    scanf("%d",&id);
    for(aux=bl->head;aux!=NULL;aux=aux->nextb) {
        if (id==aux->id) break;
    }
    if (aux==NULL){
        printf("Livro não encontrado!\n");
        return;
    }
    printf("Título:%sAutor:%sAno de publicação:%d\nO que deseja alterar?\n1.Título\n2.Autor\n3.Ano\n",&aux->title,&aux->author,aux->year);
    scanf("%d",&op);
    while ((c = getchar()) != '\n' && c != EOF);
    switch(op){
        case 1: printf("Qual o novo título?\n");
                fgets(a, MAX, stdin);
                strcpy(aux->title,a);
                break;
        case 2: printf("Qual o novo autor?\n");
                fgets(a, MAX, stdin);
                strcpy(aux->author,a);
                break;
        case 3: printf("Qual o novo ano?\n");
                scanf("%d",&y);
                aux->year=y;
                break;
    }
}

void update(Ulist *ul, Blist *bl) {
    printf("O que deseja atualizar?\n1.Livro\n2.Usuário\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                break;
        case 1: updateBook(bl);
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
    printf("Email:%sNome:%sTem certeza que deseja deletar?\n1.Sim\n0.Não\n",&aux->email,&aux->name);
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                return;
        case 1: if (aux->nextu==NULL && prev==NULL) {
                    ul->head=NULL;
                    ul->tail=NULL;
                }
                else {
                    if (aux==ul->head) {
                        ul->head=aux->nextu;
                    }
                    else {
                        prev->nextu=aux->nextu;
                        ul->tail=prev;
                    }
                }
                return;
    }
}

void deleteBook(Blist *bl) {
    int c, op, id;
    Book *aux, *prev;
    aux=bl->head;
    prev=NULL;
    printf("Digite o id:\n");
    scanf("%d",&id);
    prev=aux;
    for(aux;aux!=NULL;aux=aux->nextb) {
        if (aux->id==id) break;
        prev=aux;
    }
    if (aux==NULL){
        printf("Livro não encontrado!\n");
        return;
    }
    if (aux->status==0) {
        printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Disponível\nTem certeza que deseja deletar?\n1.Sim\n0.Não\n",&aux->title,&aux->author,aux->year);
    } else {
        printf("Título:%sAutor:%sAno de publicação:%d\nStatus:Emprestado\nTem certeza que deseja deletar?\n1.Sim\n0.Não\n",&aux->title,&aux->author,aux->year);
    }    
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                return;
        case 1: if (aux->nextb==NULL && prev==NULL) {
                    bl->head=NULL;
                    bl->tail=NULL;
                }
                else {
                    if (aux==bl->head){
                        bl->head=aux->nextb;
                    }
                    else {
                        prev->nextb=aux->nextb;
                        bl->tail=prev;
                    }
                }
                return;
    }
}

void delete(Ulist *ul, Blist *bl) {
    printf("O que deseja deletar?\n1.Livro\n2.Usuário\n0.Voltar\n");
    int op = 0;
    scanf("%d",&op);
    switch(op){
        case 0: printf("Voltando!\n");
                break;
        case 1: deleteBook(bl);
                break;
        case 2: deleteUser(ul);
                break;
    }
}

void borrow(Blist *bl) {
    int c, id;
    char a[MAX];
    Book *aux;
    printf("Digite o id do livro a ser emprestado:\n");
    scanf("%d",&id);
    for(aux=bl->head;aux!=NULL;aux=aux->nextb) {
        if (id==aux->id) break;
    }
    if (aux==NULL) printf("Livro não encontrado!\n");
    else {
        if (aux->status==1) {
            printf("O livro já está emprestado!\n");
            return;
        } else {
            printf("Título:%sAutor:%sAno de publicação:%d\nDigite o email:\n",&aux->title,&aux->author,aux->year);
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(a, MAX, stdin);
            strcpy(aux->email,a);
            aux->status=1;
            printf("O livro foi emprestado!\n");
        }
    }
}

void giveback(Blist *bl) {
    int c, id;
    Book *aux;
    char a[MAX]="";
    printf("Digite o id do livro a ser devolvido:\n");
    scanf("%d",&id);
    for(aux=bl->head;aux!=NULL;aux=aux->nextb) {
        if (id==aux->id) break;
    }
    if (aux==NULL) printf("Livro não encontrado!\n");
    else {
        if (aux->status==0) {
            printf("O livro já está disponível!\n");
            return;
        } else {
            printf("Título:%sAutor:%sAno de publicação:%d\n",&aux->title,&aux->author,aux->year);
            aux->status=0;
            strcpy(aux->email,a);
            printf("O livro foi devolvido!\n");
        }
    }
}

int main()
{
    Ulist *userl = malloc(sizeof(Ulist));
    initUlist(userl);
    Blist *bookl = malloc(sizeof(Blist));
    initBlist(bookl);
    int o = 1;
    while (o!=0) {
        printf("O que deseja fazer?\n1. Cadastro\n2. Consulta\n3. Atualização\n4. Exclusão\n5. Empréstimo\n6. Devolução\n0. Sair\n");
        scanf("%d",&o);
        switch(o) {
            case 0: printf("Saindo!\n");
                    return 0;
            case 1: add(userl,bookl);
                    break;
            case 2: consult(userl,bookl);
                    break;
            case 3: update(userl,bookl);
                    break;
            case 4: delete(userl,bookl);
                    break;
            case 5: borrow(bookl);
                    break;
            case 6: giveback(bookl);
                    break;
        }
    }
    return 0;
}
