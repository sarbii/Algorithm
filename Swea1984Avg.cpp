//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5Pw_-KAdcDFAUq&categoryId=AV5Pw_-KAdcDFAUq&categoryType=CODE
//swea1984avg

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>

int max(int a, int b) {
	if (a < b)
		return b;
	else
		return a;
}
int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
	}

int main(void) {

	int t;
	scanf("%d", &t);

	
	for (int j = 0; j < t; j++) {
		int temp[10000], m=0, n=100000, total = 0;
		double val=0;
		for (int i = 0; i < 10; i++) {
			
			scanf("%d", &temp[i]);
			total += temp[i];
            
            
			if (i >= 0) {
				m = max(m, temp[i]);
				n = min(n, temp[i]);
			}
		}
		val = total - m - n;
        
		val = val / 8;
		int average = (int)round(val);

		printf("#%d %d\n", j+ 1,average);
		
	}
   
}