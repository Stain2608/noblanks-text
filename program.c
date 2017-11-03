#include <stdio.h>
#define MAXLINE 1000 /* tamaño máximo de la línea de entrada */

char texf[MAXLINE];
char texi[MAXLINE];

int blanks = 0;
int charac = 0;
int nl = 0;

int fix(void);
int getext(void);
int verify(void);

int fix(void) {

    extern char texi[];
    extern char texf[];

    extern int blanks;
    extern int charac;
    extern int nl;

    int q = 0;
    int end = 0;
    int i = 0;
    int max = MAXLINE;

    for (q = 0; q < max - 1; ++q) {
        if (texi[q] != '\n') {
            if (texi[q] != ' ' && texi[q] != '\t') {
                texf[i] = texi[q];
                ++charac;
                ++i;
            } else if (texi[q] == ' ' || texi[q] == '\t') {
                ++blanks;
            }
        }
        else if (texi[q] == '\n') {
            texf[i++] = texi[q];
            texf[i] = '\0';
            ++nl;
            break;
        }
    }


    i = charac + nl;

    return i;
}

int getext(void) {

    extern char texi[];
    extern char texf[];

    int i = 0;
    int c = 0;
    int max = MAXLINE;

    for (i = 0; i < max - 1 && (c = getchar()) != EOF; ++i) {
        if (c != '\n') {
            texi[i] = c;
        } else if (c == '\n') {
            texi[i++] = c;
            texi[i] = '\0';
            break;
        }
    }

    if (c != EOF) {
        i = fix();
    } else if (c == EOF) {
        i = 0;
    }

    return i;
}

int verify(void) {

    extern int blanks;
    extern int charac;
    extern int nl;

    int fin = 0;
    int ver = 0;

    if (blanks < 1 && charac < 1) {
        ver = 0;
    }
    if (blanks > 0 && charac < 1) {
        ver = 1;
    }
    if (blanks < 1 && charac > 0) {
        ver = 2;
    }
    if (blanks > 1 && charac > 0) {
        ver = 3;
    }

    if (ver == 0) {
        if (nl > 0) {
            printf("Only ENTER character are not allowed\n");
            printf("TRY AGAIN\n");
            fin = 0;
        }
    }
    if (ver == 1) {
        printf("Only BLANKS characters are not allowed\n");
        printf("TRY AGAIN\n");
        fin = 1;
    }
    if (ver == 2 || ver == 3) {

        fin = 2;
    }
    return fin;
}

int main(void) {

    extern char texf[];

    int i = 0;

    while ((i = getext()) > 0) {

        int f = verify();

        if (f == 0) {
            printf("0\n");
            break;
        }
        if (f == 1) {
            printf("1\n");
            break;
        }
        if (f == 2) {
            printf("what you inputed without blank characters:\n");
            printf("%s", texf);
            charac = blanks = nl = 0;
        }
    }
    printf("%d %d %d\n", blanks, charac, nl);
    return 0;
}
