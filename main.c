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

int main(int argc, char **argv){
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
            /*//printf("b:%d\n", riga[0]);
            int i=0;
            char a[] = "";
            char b[] = "";
            char c[] = "";
            for(; i<100 && !isspace(riga[i]); i++){//legge prima parte
                a[i] = riga[i];
                //printf("a:%c\n", riga[i]);
            }

            int offset = i;
            for(; i<100 && !isspace(riga[i]); i++){//legge seconda parte
                b[(i-offset)] = riga[i];
                //printf("b:%c\n", riga[i]);
            }
            
            offset = i;
            for(; i<100 && !isspace(riga[i]); i++){//legge terza parte
                c[(i-offset)] = riga[i];
                //printf("c:%c\n", riga[i]);
            }*/
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

            printf("a:%s, b:%s, c:%s\n", a, b, c);

            if(!strcmp(a, "push")){
                struct command x;
                x.a = (char*)malloc(50);
                x.b = (char*)malloc(50);
                x.c = (char*)malloc(50);
                x.prev = it;
                strcpy(x.a, a);
                strcpy(x.b, b);
                strcpy(x.c, c);
                //printf("a:%s, b:%s, c:%s", a, b, c);
                //printf("%s,%s,%d", it->a, it->b, it->c);
                it = &x;
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