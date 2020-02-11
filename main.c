#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

typedef struct command{
    char *a, *b, *c;
    struct command *prev;
}com;

typedef struct command* ptr_stack;
ptr_stack it = NULL;

char* removetr(char* c){
    char *c2 = (char*)malloc(50);
    for(int i=0; i<50 && !isspace(c[i]); i++){
        c2[i] = c[i];
    }
    return c2;
}

int main(int argc, char **argv){
    int local[10000] = (int)malloc(sizeof(int)*10000);
    //printf("%s", argv[1]);
    FILE *fin;//apre file input
    fin = fopen(argv[1], "r");
    
    char dest[]="";
    for(int i=0; i<strlen(argv[1]); i++){
        if(argv[1][i] != '.'){
            dest[i] = argv[1][i];
            //strcat(dest, argv[1][i]);
        }
    }
    FILE *fout;
    fout = fopen(strcat(dest,".asm"), "w");

    char riga[100];
    while(fgets(riga, 100, fin)){
        //printf("a:%d\n", riga[0]);
        if(riga[0] != '\r' && riga[0] != '/'){
            char *a = (char*)malloc(50);
            char *b = (char*)malloc(50);
            char *c = (char*)malloc(50);
            char *token;
            char s[] = " ";

            token = strtok(riga, s);//load a
            strcpy(a, token);
        
            token = strtok(NULL, s);
            if(token != NULL){
                strcpy(b, token);//load b

                token = strtok(NULL, s);
                if(token != NULL)
                    strcpy(c, token);//load c
            }

            a = removetr(a);//removes trailing lf
            b = removetr(b);
            c = removetr(c);

            printf("a:%s, b:%s, c:%s\n", a, b, c);

            if(!strcmp(a, "push")){
                ptr_stack x = (ptr_stack)malloc(sizeof(com));
                x->a = (char*)malloc(50);
                x->b = (char*)malloc(50);
                x->c = (char*)malloc(50);
                //if(it != NULL)
                //    printf("test:%s",it->c);
                x->prev = it;
                strcpy(x->a, a);
                strcpy(x->b, b);
                strcpy(x->c, c);
                //printf("a:%s, b:%s, c:%s", a, b, c);
                //printf("%s,%s,%d", it->a, it->b, it->c);
                it = x;
                //if(it->prev != NULL)
                //    printf("test3:%s",it->prev->c);
            }
            if(!strcmp(a, "add")){
                printf("asd");
                com c1 = *it;
                it = it->prev;
                com c2 = *it;
                it = it->prev;//reads the first two items on the stack

                //processes the first argument
                if(!strcmp(c1.b, "constant")){
                    fprintf(fout, "@%d\n", atoi(c1.c));
                    fprintf(fout, "D=A\n");
                }else if(!strcmp(c1.b, "constant")){
                    fprintf(fout, "@%d\n", atoi(c1.c));
                    fprintf(fout, "D=A\n");
                }

                //processes the second argument
                if(!strcmp(c2.b, "constant")){
                    fprintf(fout, "@%d\n", atoi(c2.c));
                    fprintf(fout, "D=D+A\n");
                }
            }
        }
    }
    while(it != NULL){
        printf("%s", it->c);
        it = it->prev;
        getchar();
    }
    fclose(fin);
    fclose(fout);
    return 0;
}