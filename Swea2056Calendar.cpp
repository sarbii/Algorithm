//https://swexpertacademy.com/main/solvingProblem/solvingProblem.do
//2056 claender

#include<stdio.h>
#include<string.h>
  
int main(void)
{
      
    int t;
    scanf("%d",&t);
    for(int i=0; i<t;i++)
    {
        int s,year,month,day, mon,d; 
        
        scanf("%d",&s);
        
        year = s/10000;
        month = s/100 - 100*year;
        day = s%100;
        
        switch(month){
                case 1:
                d=31;
                break;
                case 3:
                d=31;
                break;
                case 5:
                d=31;
                break;
                case 7:
                d=31;
                break;
                case 8:
                d=31;
                break;
            case 10:
                d=31;
                break;
            case 12:
               d=31;
                break;
            case 4:
                d=30;
                break;
            case 6:
                d=30;
                break;
            case 9:
                d=30;
                break;
           case 11:
                d=30;
                break;
            case 2:
                d=28;
                break;
            default:
                d=0;
                break;
        }
        
        if(d<day)
            printf("#%d -1\n", i+1);
        else{
            if (year < 10) printf("#%d 000%d/",  i+1, year);
			else if (year < 100) printf("#%d 00%d/",  i+1, year);
			else if (year < 1000) printf("#%d 0%d/",  i+1, year);
			else printf("#%d %d/",  i+1, year);
			if (month < 10) printf("0%d/", month);
			else printf("%d/", month);
			if (day < 10) printf("0%d\n", day);
			else printf("%d\n", day);
        }
        
        
        
        
        
    }
}