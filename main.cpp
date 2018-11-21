
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>


using namespace std;

struct STACK {
    int *elems;    //申请内存用于存放栈的元素
    int max;    //栈能存放的最大元素个数
    int pos;    //栈实际已有元素个数，栈空时pos=0;
};

void initSTACK(STACK *const p, int m);  //初始化p指向的栈：最多m个元素

void initSTACK(STACK *const p, const STACK &s); //用栈s初始化p指向的栈
int size(const STACK *const p);        //返回p指向的栈的最大元素个数max
int howMany(const STACK *const p);    //返回p指向的栈的实际元素个数pos
int getelem(const STACK *const p, int x);    //取下标x处的栈元素
STACK *const push(STACK *const p, int e);    //将e入栈，并返回p
STACK *const pop(STACK *const p, int &e);    //出栈到e，并返回p
STACK *const assign(STACK *const p, const STACK &s); //赋s给p指的栈,并返回p
void print(const STACK *const p);            //打印p指向的栈
void destroySTACK(STACK *const p);        //销毁p指向的栈

bool isNum(char c) {
    if (c >= '0'&&c <= '9')
        return true;
    else return false;
}

ofstream saveMessage("U201614751.txt");

int main(int argc, char* argv[]) {


    if (!saveMessage.is_open())
        return 1;

    if (argc > 1) {
        int i = 1;
        int e = 0;

        int model = 0;

        int j = 0;
        int popNum = 0;
        STACK * p = (STACK*)malloc(sizeof(STACK));
        STACK *c = 0;

        p->elems = 0;
        p->max = 0;
        p->pos = 0;
        bool isEnd = false;
        for (; i < argc; i++) {
            if (isEnd) {
                destroySTACK(p);
                return 0;
            }

            if (strcmp(argv[i], "-S") == 0) {
                int m = atoi(argv[i + 1]);
                i++;
                initSTACK(p, m);

                printf("S  %d  ", m);
                saveMessage << "S  " << m << "  ";

            }
            else {

                if (strcmp(argv[i], "-I") == 0) {
                    model = 1;
                }
                else if (strcmp(argv[i], "-O") == 0){
                    model = 2;
                }
                else if (strcmp(argv[i], "-C") == 0) {
                    model = 3;
                    i--;
                }
                else if (strcmp(argv[i], "-A") == 0) {
                    model = 4;
                }
                else if (strcmp(argv[i], "-N") == 0) {
                    model = 5;
                    i--;
                }
                else if (strcmp(argv[i], "-G") == 0) {
                    model = 6;
                }
                else {
                    i--;
                }
                i++;
                switch (model)
                {
                    case 1:

                        printf("I  ");
                        saveMessage << "I  ";

                        for (; i < argc; i++) {
                            if (isNum(argv[i][0])) {
                                if (p->pos < p->max) {
                                    e = atoi(argv[i]);
                                    push(p, e);
                                }
                                else {
                                    printf("E");
                                    saveMessage << "E";

                                    isEnd = true;
                                    break;
                                }
                            }
                            else {
                                i--;
                                break;
                            }
                        }
                        if(!isEnd)
                            print(p);
                        break;
                    case 2:
                        popNum = atoi(argv[i]);

                        printf("O  ");
                        saveMessage << "O  ";

                        for (j=0; j < popNum; j++) {
                            p=pop(p, e);
                            if (!p) {
                                printf("E");
                                saveMessage << "E";

                                isEnd = true;
                                break;
                            }
                        }
                        if (!isEnd) {
                            print(p);
                        }
                        break;
                    case 3:
                        c = (STACK*)malloc(sizeof(STACK));
                        c->max = 0;
                        c->elems = 0;
                        c->pos = 0;
                        initSTACK(c, *p);
                        destroySTACK(p);
                        free(p);

                        p = c;
                        printf("C  ");
                        saveMessage << "C  ";
                        print(p);
                        break;
                    case 4:
                        c = (STACK*)malloc(sizeof(STACK));
                        c->max = atoi(argv[i]);
                        c->elems = 0;
                        c->pos = 0;

                        assign(c, *p);
                        destroySTACK(p);
                        free(p);
                        p=0;

                        p = c;
                        printf("A  ");
                        saveMessage << "A  ";
                        print(p);
                        break;
                    case 5:
                        printf("N  %d  ", howMany(p));
                        saveMessage << "N  " << howMany(p) << "  ";
                        break;
                    case 6:
                        e = atoi(argv[i]);
                        printf("G  ");
                        saveMessage << "G  ";
                        if (e < p->pos&&e >= 0) {
                            printf("%d  ", getelem(p, e));
                            saveMessage << getelem(p, e) << "  ";
                        }
                        else {
                            printf("E");
                            saveMessage << "E";
                            isEnd = true;
                        }
                        break;
                    default:
                        break;
                }

            }
        }
    }
    saveMessage.close();
    return 0;
}

void initSTACK(STACK *const p, int m) {
    if (p) {
        p->pos = 0;
        p->elems = (int *)malloc(m * sizeof(int));
        if (p->elems == NULL) {
            p->max = 0;
        }
        else p->max = m;
    }
}

void initSTACK(STACK *const p, const STACK &s) {
    int i = 0;

    p->pos = 0;
    p->elems = (int*)malloc(s.max * sizeof(int));
    p->max = s.max;

    for (; i < s.pos; i++) {
        p->elems[i] = s.elems[i];
        p->pos++;
    }
}

int size(const STACK *const p) {
    if (p) {
        return p->max;
    }
    else {
        return 0;
    }
}

int howMany(const STACK *const p) {
    if (p) {
        return p->pos;
    }
    else return 0;
}

int getelem(const STACK *const p, int x) {
    if (x < p->pos) {
        return p->elems[x];
    }
    else return -1;
}


STACK *const push(STACK *const p, int e) {
    if (p->pos < p->max) {
        p->elems[p->pos++] = e;
    }

    return p;
}
STACK *const pop(STACK *const p, int &e) {
    if (p->pos > 0) {
        e = p->elems[--p->pos];
        return p;
    }
    else return 0;
}

STACK *const assign(STACK *const p, const STACK &s) {

    p->elems = (int*)malloc(s.max * sizeof(int));

    int i = 0;
    for (i = 0; i < s.pos; i++) {
        p->elems[i] = s.elems[i];
        p->pos++;
    }
    p->max = s.max;

    return p;
}

void print(const STACK *const p) {
    int i = 0;
    for (; i < p->pos; i++) {
        printf("%d  ", p->elems[i]);
        saveMessage << p->elems[i] << "  ";
    }
}

void destroySTACK(STACK *const p) {
    if (p) {
        if (p->elems) {
            free(p->elems);
            p->elems = 0;
        }
    }
}