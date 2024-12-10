#include <stdio.h>
#include <stdlib.h>
int validateEmail(char* email) {
    int i=0;
    int at=0;
    int dot=0;
    int ati;
    while(email[i]!='\0') {
        if(email[i]=='@') {
            at++;
            ati=i;
        }
        i++;
    }
    if(at==1) {
        i=ati;
        while(email[i]!='\0') {
            if(email[i]!='.') {
                dot++;
            }
            i++;
        }
    }
    else {
        return 0;
    }
    i=0;
    while(i<ati) {
        if(email[i]=='.') {
            return 0;
        }
        i++;
    }
    if(at==1 && dot>=1) {
        return 1;
    }
    else {
        return 0;
    }
}
int main() {
    printf("enter your email:\n");
    char* email=malloc(sizeof(char)*1);
    int len=0;
    while(1) {
        email=realloc(email,sizeof(char)*(len+1));
        char val;
        scanf("%c",&val);
        if(val=='\n') {
            break;
        }
        email[len]=val;
        len++;
    }
    email[len]='\0';
    if(validateEmail(email)) {
        printf("valid email");
    }
    else {
        printf("not valid");
    }
    free(email);
}