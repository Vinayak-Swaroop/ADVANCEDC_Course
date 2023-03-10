#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum position{President,Treasurer,Member};
typedef enum position position;
struct Student
{
    char name[20];
    char regno[20];
    char gender;
    float CGPA;
    int num_of_activities_organised;
    int num_of_activities_participated;
    enum position post;
    int level_of_performance;
};
typedef struct Student Student;

int getPost(char *temp)
{
    if(strcmp(temp,"President")==0)
    {
        return 0;
    }
    else if(strcmp(temp,"Member")==0)
    {
        return 2;
    }
    else if(strcmp(temp,"Treasurer")==0)
    {
        return 1;
    }
}

Student newStudent()
{
    Student s;
    char temp[20];
    printf("Enter the name of the student: ");
    scanf("%s",s.name);
    printf("Enter the registration number: ");
    scanf("%s",s.regno);
    printf("Enter the gender of the student: ");
    fflush(stdin);
    scanf("%c",&s.gender);
    printf("Enter the CGPA of the student: ");
    scanf("%f",&s.CGPA);
    printf("Enter the number of activities organised: ");
    scanf("%d",&s.num_of_activities_organised);
    printf("Enter the number of activities participated: ");
    scanf("%d",&s.num_of_activities_participated);
    printf("Enter the position of the student: ");
    scanf("%s",temp);
    s.post=getPost(temp);
    printf("Enter the level of performance of the student: ");
    scanf("%d",&s.level_of_performance);
    return s;
}

char* displayPost(position p){
    char *temp=NULL;
    switch(p)
    {
        case President:
            temp="President";
            break;
        case Member:
            temp="Member";
            break;
        case Treasurer:
            temp="Treasurer";
            break;
    }
    return temp;
}

void displayStudent(Student s)
{
    printf("%s %s %c %.2f %d %d %s %d\n",s.regno,s.name,s.gender,s.CGPA,s.num_of_activities_organised,s.num_of_activities_participated,displayPost(s.post),s.level_of_performance);
}
int getNumofRecords(FILE *fp){
    Student s;
    int ct=0;
    while(fread(&s,sizeof(s),1,fp)==1)
        ct++;
    rewind(fp);
    return ct;
}
int isEligible(Student s){
    if(s.CGPA>=9 && s.num_of_activities_organised>4 && s.level_of_performance==1)
        return 1;
    return 0;
}

int greaterStudent(Student s1,Student s2){
    if(s1.CGPA>s2.CGPA)
        return 1;
    else if(s1.CGPA==s2.CGPA){
        if(s1.num_of_activities_organised>s2.num_of_activities_organised)
            return 1;
        else if(s1.num_of_activities_organised==s2.num_of_activities_organised){
            if(s1.level_of_performance<s2.level_of_performance)
                return 1;
            else return 0;
        }
    }
    else
        return 0;
}

int searchStudent(Student s,FILE *fp){
    rewind(fp);
    Student temp;
    while(fread(&temp,sizeof(temp),1,fp)==1)
        if(strcmp(temp.regno,s.regno)==0)
            return 1;
    return 0;
}

int insertStudent(Student s,FILE *fp,int club){
    if(searchStudent(s,fp)==1){
        printf("Student already exists\n");
        return -1;
    }
    Student temp;
    rewind(fp);
    FILE* TEMP=fopen("temp.dat","wb+");
    int flag=0;
    while(fread(&temp,sizeof(temp),1,fp)==1){
        if(greaterStudent(s,temp)==1 && !flag){
            fwrite(&s,sizeof(s),1,TEMP);
            flag=1;
        }
        fwrite(&temp,sizeof(temp),1,TEMP);
    }
    if(!flag)
        fwrite(&s,sizeof(s),1,TEMP);

    if(club==1){
        fclose(TEMP);
        fclose(fp);
        remove("club1.dat");
        rename("temp.dat","club1.dat");
        fp=fopen("club1.dat","ab+");
        rewind(fp);
    }
    else if(club==2){
        fclose(TEMP);
        fclose(fp);
        remove("club2.dat");
        rename("temp.dat","club2.dat");
        fp=fopen("club2.dat","ab+");
        rewind(fp);
    }
    return 1;
}
void modifyPosition(FILE *fp,int choice){
    Student s;
    rewind(fp);
    FILE* TEMP=fopen("temp.dat","wb+");
    fread(&s,sizeof(s),1,fp);
    s.post=President;
    fwrite(&s,sizeof(s),1,TEMP);
    fread(&s,sizeof(s),1,fp);
    s.post=Treasurer;
    fwrite(&s,sizeof(s),1,TEMP);
    while(fread(&s,sizeof(s),1,fp))
        fwrite(&s,sizeof(s),1,TEMP);
    fclose(TEMP);
    fclose(fp);
    if(choice==1){
        printf("Records edited successfully");
        remove("club1.dat");
        rename("temp.dat","club1.dat");
        fp=fopen("club1.dat","ab+");
    }
    else if(choice==2){
        printf("Records edited successfully");
        remove("club2.dat");
        rename("temp.dat","club2.dat");
        fp=fopen("club2.dat","ab+");
    }
}


int main()
{
    FILE *club1,*club2;
    club1=fopen("club1.dat","ab+");
    if(club1==NULL){
        printf("Error opening club1.dat\nExiting...\n");
        return 0;
    }
    club2=fopen("club2.dat","ab+");
    if(club2==NULL){
        printf("Error opening club2.dat\nExiting...\n");
        return 0;
    }
    int ch;
    do{
        int temp;
        Student s;
        printf("\n");
        printf("1.Add student to club \n");
        printf("2.Display students\n");
        printf("3.Display eligible students\n");
        printf("4.Display names of top 2 boys and girls\n");
        printf("5.Modify positions\n");
        printf("6.Exit\n");
        //7 to re-inititialize files
        printf("\nEnter choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter club:");
                scanf("%d",&temp);
                s=newStudent();
                if(temp==1)
                    insertStudent(s,club1,temp);
                else if(temp==2)
                    insertStudent(s,club2,temp);
                else
                    printf("Invalid choice\n");
                break;
            case 2:
                printf("Enter club:");
                scanf("%d",&temp);
                if(temp==1){
                    rewind(club1);
                    while(fread(&s,sizeof(s),1,club1)==1)
                        displayStudent(s);
                }
                else if(temp==2){
                    rewind(club2);
                    while(fread(&s,sizeof(s),1,club2)==1)
                        displayStudent(s);
                }
                break;
            case 3:
                printf("Enter club:");
                scanf("%d",&temp);
                if(temp==1){
                rewind(club1);
                    while(fread(&s,sizeof(s),1,club1)==1)
                        if(isEligible(s))
                            displayStudent(s);}
                else if(temp==2){
                    rewind(club2);
                    while(fread(&s,sizeof(s),1,club2)==1)
                        if(isEligible(s))
                            displayStudent(s);}
                break;
            case 4:
                printf("Enter club:");
                scanf("%d",&temp);
                rewind(club1);
                rewind(club2);
                int boyct=0,girlct=0;
                Student s;
                if(temp==1)
                    while(fread(&s,sizeof(s),1,club1)==1){
                        if(s.gender=='M' && boyct<2){
                            boyct++;
                            displayStudent(s);
                        }
                        else if(s.gender=='F' && girlct<2){
                            girlct++;
                            displayStudent(s);
                        }
                        if(boyct==2 && girlct==2)
                            break;
                    }
                else if(temp==2)
                    while(fread(&s,sizeof(s),1,club1)==1){
                        if(s.gender=='M' && boyct<2){
                            boyct++;
                            displayStudent(s);
                        }
                        else if(s.gender=='F' && girlct<2){
                            girlct++;
                            displayStudent(s);
                        }
                        if(boyct==2 && girlct==2)
                            break;
                    }
                break;
            case 5:
                printf("Enter club:");
                scanf("%d",&temp);
                if(temp==1)
                    modifyPosition(club1,temp);
                else if(temp==2)
                    modifyPosition(club2,temp);
                break;
            case 6:printf("Exiting...\n");break;
            case 7:club1=fopen("club1.dat","wb+");club2=fopen("club2.dat","wb+");break;
            default:printf("Invalid choice\n");
        }           
    }while(ch!=6);
    fclose(club1);
    fclose(club2);
    return 0;
}
