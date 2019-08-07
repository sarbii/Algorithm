//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PTeo6AHUDFAUq&categoryId=AV5PTeo6AHUDFAUq&categoryType=CODE
//swea1926 369


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int main(void) {

   int i;
   scanf("%d", &i);
   for (int t = 1; t < i+1; t++) {
      
      if(1000>t){
         int y1=0, y2=0,y3=0;
         int a, b, c;
         a = t % 10;
         b = t / 100;
         c = t / 10 - 10*b;

         if (a == 3 || a == 6 || a == 9)
            y1 = 1;
         if (b == 3 || b == 6 || b == 9)
            y2 = 1;
         if (c == 3 || c == 6 || c == 9)
            y3 = 1;
         
         if (y1 && y2 && y3)
            printf("--- ");
         else if (y1  && y3 )
            printf("-- ");
         else if (y2  && y3 )
            printf("-- ");
         else if (y1  && y2 )
            printf("-- ");
         else if (y1 )
            printf("- ");
         else if (y2 )
            printf("- ");
         else if (y3 )
            printf("- ");

         else
            printf("%d ", t);
      }
      else
         printf("%d ", t);


         
   }
}