#include<stdio.h>
#define ADD(n,sum) ({\
                        int i=0;\
                        float temp;\
                        for(i=0;i<n;i++){\
                            scanf("%f",&temp);\
                            sum+=temp;\
                        }\
                    })
#define MEAN(n) ({\
                    float sum=0;\
                    ADD(n,sum);\
                    printf("%.2f",(sum/n));\
                })
#define ABS(x) ((x)<0?-(x):(x))
#define TOLOWER(ch) (ch+32)
#define GETMAX(x,y) ((x)>(y)?(x):(y))

int main()
{
    int ch;
    int a,b;
    char c;
    printf("Author: Vinayak Swaroop Bhatnagar\t20BCI0070\n");
    do{
        printf("Choose: \n");
        printf("1.Find Mean of n numbers\n2.Get Absolute\n3.Convert to lower case \n4.Get Maximum \n5.Exit\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Enter value of n: ");
                scanf("%d",&a);
                printf("Enter n numbers: \n");
                MEAN(a);
                printf("\n");
                break;
            case 2:
                printf("Enter a number: ");
                scanf("%d",&a);
                printf("Absolute value is: %d\n",ABS(a));
                break;
            case 3:
                printf("Enter a lowercase character: ");
                scanf("%c",&c);
                while(c=='\n')
                    scanf("%c",&c);
                printf("Lowercase: %c\n",TOLOWER(c));
                break;
            case 4:
                printf("Enter 2 numbers: ");
                scanf("%d%d",&a,&b);
                printf("Larger number is: %d\n",GETMAX(a,b));
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:printf("Invalid Input");
        }
    }while(ch!=5);

	return 0;
}