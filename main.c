#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct comando{
    char a[50], b[50];
    int c;
    struct comando *prev;
}com;

typedef struct comando* ptr_stack;
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
            //printf("b:%d\n", riga[0]);
            int i=0;
            char a[] = "";
            char b[] = "";
            char c[] = "";
            for(; i<100 && !isspace(a[i]); i++){//legge prima parte
                a[i] = riga[i];
            }

            int offset = i;
            for(; i<100 && !isspace(riga[i]); i++){//legge seconda parte
                b[(i-offset)] = riga[i];
            }
            offset = i;

            for(; i<100 && !isspace(riga[i]); i++){//legge terza parte
                c[(i-offset)] = riga[i];
                printf("%c\n", c[i]);
            }
            //printf("%s,%s,%d", a, b, c);
            ptr_stack x = {a, b, atoi(c), it};
            //printf("%s,%s,%d", it->a, it->b, it->c);
            it = x;
        }
    }
    return 0;
}