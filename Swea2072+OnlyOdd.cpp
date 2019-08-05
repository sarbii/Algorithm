//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5QSEhaA5sDFAUq&categoryId=AV5QSEhaA5sDFAUq&categoryType=CODE
//sw Expert Academy
#include<stdio.h>
#include<string.h>
  
int main(void){
      
    int t;
    scanf("%d",&t);
    for(int i=0; i<t;i++){
        int temp1,temp2;
        scanf("%d", &temp1);
        scanf("%d", &temp2);
        if (temp1==temp2)
            printf("#%d =\n", i+1);
        else if(temp1>temp2)
            printf("#%d >\n", i+1);
        else
            printf("#%d <\n", i+1);
    }
}