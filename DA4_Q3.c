# include <stdio.h>
# include <string.h>
// enum emp_dept {assembly, manufacturing, accounts, stores};
#define equals(x,y) (strcmp(x,y)==0)
#define ASSEMBLY 1
#define MANUFACTURING 2
#define ACCOUNTS 3
#define STORES 4
struct Employee
{
    char name[ 30 ] ;
    int age ;
    float bs ;
    int dept;//1. Assemnly 2.Manufacturing 3. Accounts 4.Stores
};
typedef struct Employee Employee;

char* getDepartment(Employee e)
{
    static char* p=NULL;
    char temp[30]="";
    switch(e.dept){
        case ASSEMBLY:p= "Assembly";break;
        case MANUFACTURING:p= "Manufacturing";break;
        case ACCOUNTS:p= "Accounts";break;
        case STORES:p= "Stores";break;
        default:
            p=NULL;
            printf("Invalid Department %d\n",e.dept);
    }
    return p;
}

void setDepartment(Employee *e, char dept[])
{
    if(equals(dept,"Assembly"))
        {e->dept = ASSEMBLY;return;}
    if(equals(dept,"Manufacturing"))
       { e->dept = MANUFACTURING;return;}
    if (equals(dept,"Accounts"))
        {e->dept = ACCOUNTS;return;}
    if (equals(dept,"Stores"))
        {e->dept = STORES;return;}
    e->dept=-1;
}

int main()
{
    printf("Author: Vinayak Swaroop Bhatnagar\t20BCI0070\n");
    Employee e ;
    strcpy(e.name,"Amali") ;
    e.age = 28 ;
    e.bs = 56575.50 ;
    setDepartment(&e,"Assembly");
    printf("Name: %s\nAge: %d\nBase Salary: %.2f\nDepartment: %s\n",e.name,e.age,e.bs,getDepartment(e));
    return 0 ;
}
