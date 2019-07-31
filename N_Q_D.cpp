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
int main()
{
	FILE *input;
	FILE *output;
	char inputFileName[100];
	int i;

	printf("input file name? ");
	scanf("%s", inputFileName);
	input = fopen(inputFileName, "r");
	output = fopen("output.txt", "w");
	fscanf(input, "%d", &n);

	board = (int *)malloc(sizeof(int)*(n + 1));

	queens(0);

	for (i = 1; i < n; i++)
		fprintf(output, "%d\n", board[i]);
	fprintf(output, "%d", board[n]);
	

	free(board);
	fclose(input);
	fclose(output);
	return 1;
}