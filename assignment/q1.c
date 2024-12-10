#include <stdio.h>
#include <string.h>

struct employee{
    int employeeCode;
    char employeeName[20];
    int dateOfJoining;
};
void f01(struct employee emp[]) {
    int year;
    printf("enter year:\t");
    scanf("%d",&year);
    for(int i=0;i<4;i++) {
        if(year-(emp[i].dateOfJoining%100)>=3) {
            printf("employee name: %s\n",emp[i].employeeName);
            printf("emplyee code: %d\n",emp[i].employeeCode);
            printf("date of joining: %d\n\n",emp[i].dateOfJoining);
        }
    }
}
int main() {
    struct employee emp[4];
    for(int i=0;i<4;i++) {
        char name[20];
        printf("enter name:\t");
        scanf(" %[^\n]s",name);
        printf("enter employee code:\t");
        scanf(" %d",&emp[i].employeeCode);
        printf("enter date of joining in ddmmyy:\t");
        scanf(" %d",&emp[i].dateOfJoining);
        strcpy(emp[i].employeeName,name);
    }
    f01(emp);
}