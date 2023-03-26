#include<stdio.h>
// #define PI 3.1415
#define AREA(r) (PI*r*r)
int main()
{
    printf("Author: Vinayak Swaroop Bhatnagar\t20BCI0070\n");
    float radius;
    scanf("%f",&radius);
    #if defined(PI)
        printf("%.2f",AREA(radius));
    #else
        #define PI 3.1415
        printf("%.2f",PI*radius*radius);
    #endif
}