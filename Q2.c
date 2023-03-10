#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Student
{
    char regno[20];
    char name[20];
    char programme[20];
    char school[20];
    float CGPA;
    int rank;
};
typedef struct Student Student;

void displayStudent(Student s){
    printf("%s %s %s %s %.2f %d\n",s.regno,s.name,s.programme,s.school,s.CGPA,s.rank);
}

int searchStudent(Student s,FILE *fp){
    rewind(fp);
    Student temp;
    while(fread(&temp,sizeof(temp),1,fp)==1)
        if(strcmp(temp.regno,s.regno)==0){
            printf("Student exists\n");
            displayStudent(temp);
            return 1;
    }
    return 0;
}

int greaterStudent(Student s1,Student s2){
    if(s1.CGPA>s2.CGPA)
        return 1;
    else
        return 0;
}

int insertStudent(Student s,FILE *fp,char filename[]){
    if(searchStudent(s,fp)==1){
        printf("Student already exists\n");
        return -1;
    }
    Student temp;
    rewind(fp);
    FILE* TEMP=fopen("temp.dat","wb+");
    int flag=0,i=1;
    while(fread(&temp,sizeof(temp),1,fp)==1){
        if(greaterStudent(s,temp)==1 && !flag){
            s.rank=i;
            fwrite(&s,sizeof(s),1,TEMP);
            flag=1;
        }
        i++;
        if(flag)
            temp.rank++;
        fwrite(&temp,sizeof(temp),1,TEMP);
    }
    if(!flag){
        s.rank=i;
        fwrite(&s,sizeof(s),1,TEMP);
    }
    FILE* monitor=fopen("monitor.dat","ab+");
    if(s.CGPA<4.0){
        fwrite(&s,sizeof(s),1,monitor);
        fclose(monitor);
    }
    fclose(fp);
    fclose(TEMP);
    remove(filename);
    rename("temp.dat",filename);
    fp=fopen(filename,"ab+");
    return 1;
}
Student newStudent()
{
    Student s;
    printf("Enter the name of the student: ");
    scanf("%s",s.name);
    printf("Enter the registration number: ");
    scanf("%s",s.regno);
    printf("Enter the program: ");
    scanf("%s",s.programme);
    printf("Enter the school: ");
    scanf("%s",s.school);
    printf("Enter the CGPA: ");
    scanf("%f",&s.CGPA);
    s.rank=0;
    return s;
}
int main()
{
    FILE* student_file;
    student_file=fopen("student.dat","ab+");
    FILE* monitor=fopen("monitor.dat","rb+");
    int choice;
    Student s;
    do{
        printf("\n 1.Insert Student\n 2.Display Student\n 3.Search Student\n 4.View Montior File\n 5.Exit\n");
        //5.Re-initialize the file
        scanf("%d",&choice);
        switch(choice){
            case 1:
                insertStudent(newStudent(),student_file, "student.dat");
                break;
            case 2:
                rewind(student_file);
                while(fread(&s,sizeof(s),1,student_file)==1)
                    displayStudent(s);
                break;
            case 3:
                rewind(student_file);
                printf("Enter the registration number: ");
                scanf("%s",s.regno);
                if(!searchStudent(s,student_file))
                    printf("Student not found\n");
                break;
            case 4:
                while(fread(&s,sizeof(s),1,monitor)==1)
                    displayStudent(s);
                break;
            case 5:
                printf("Exiting...\n");break;
            case 6:
                fclose(student_file);
                fclose(monitor);
                student_file=fopen("student.dat","wb+");
                monitor=fopen("monitor.dat","wb+");
                break;
            default:printf("Invalid choice\n");
        }
    }while(choice!=5);
    return 0;
}
