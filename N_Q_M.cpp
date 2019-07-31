#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int *board;
int n;
int bStop = 0;
int promising(int i)
{
	int k = 1;
	int prom = 1;
	while (k < i && prom)
	{
		if (board[i] == board[k] || (abs(board[i] - board[k]) == i - k))
			prom = 0;
		k++;
	}
	return prom;
}
void queens(int i)
{
	int j;
	if (promising(i))
	{
		if (i == n)
		{
			bStop = 1;
			return;
		}
		else
		{
			for (j = 1; j <= n; j++)
			{
				if (bStop)
					break;
				board[i + 1] = j;
				queens(i + 1);
			}
		}
	}
}
int prom_rand(int n)
{
	int i, j, *prom_level;
	int temp;
	int prom_level_cnt;
	prom_level = (int *)malloc(sizeof(int)*(n + 1));
	i = 0;
	prom_level_cnt = 1;
	while (prom_level_cnt != 0 && i < n)
	{
		i++;
		for (j = 1; j <= n; j++) 
			prom_level[j] = 1;
		for (j = 1; j < i; j++)
		{
			prom_level[board[j]] = 0; 
			temp = board[j] - (i - j); 
			if (temp > 0)
				prom_level[temp] = 0;
			temp = board[j] + (i - j); 
			if (temp <= n)
				prom_level[temp] = 0;
		}
		prom_level_cnt = 0;
		for (j = 1; j <= n; j++)
		{
			if (prom_level[j])
			{
				prom_level[prom_level_cnt] = j;
				prom_level_cnt++;
			}
		}
		if (prom_level_cnt > 0)
			board[i] = prom_level[rand() % prom_level_cnt];
	}
	free(prom_level);
	return i - 1;
}
int main()
{
	FILE *input;
	FILE *output;
	char inputFileName[100];
	int i, rn;

	printf("input file name? ");
	scanf("%s", inputFileName);
	input = fopen(inputFileName, "r");
	output = fopen("output.txt", "w");
	
	fscanf(input, "%d", &n);
	
	board = (int *)malloc(sizeof(int)*(n + 1));

	while (!bStop)
	{
		do {
			rn = prom_rand(n);
		} while (rn < n - 5);
		rn--;


		while (rn >= 0)
		{
			queens(rn);
			if (bStop)
				break;
			else
				rn--;
		}
		if (rn < 0)
			break;
	}

		
	
	for (i = 1; i < n; i++)
		fprintf(output, "%d\n", board[i]);
	fprintf(output, "%d", board[n]);
	

	free(board);
	fclose(input);
	fclose(output);
	return 1;
}
