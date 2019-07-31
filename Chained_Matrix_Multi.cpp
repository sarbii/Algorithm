#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void minmult(int N, int *d, int **p) {
	int i, j, k, diagonal, q;
	int **M;

	M = (int**)malloc(sizeof(int*)*N);
	for (i = 0; i < N; i++)
		M[i] = (int*)malloc(sizeof(int*)*N);

	for (i = 0; i < N; i++)
		M[i][i] = 0;

	for (diagonal = 1; diagonal < N; diagonal++) {
		for (i = 0; i < N - diagonal; i++) {

			j = i + diagonal;
			M[i][j] = 2147483647;
			for (k = i; k < j; k++) {
				q = (M[i][k] + M[k + 1][j] + d[(i - 1) + 1] * d[k + 1] * d[j + 1]);
				if (q < M[i][j]) {
					M[i][j] = q;
					p[i][j] = k;
				}
			}
		}
	}

	for (i = 0; i < N; i++)
		free(M[i]);
	free(M);
}

void print_order(int N, int i, int j, int **p, FILE* output) {
	int k;

	if (i == j)
		fprintf(output, " %d ", i + 1);
	else {
		k = p[i][j];
		fprintf(output, "(");
		print_order(N, i, k, p, output);
		print_order(N, k + 1, j, p, output);
		fprintf(output, ")");
	}
}

int main(void) {
	FILE *input;
	FILE *output;

	char file_name[50];
	int nn, i, N;
	int *d, **p;	

	printf("input file name?");
	scanf("%s", file_name);
	input = fopen(file_name, "r");
	output = fopen("output.txt", "w");

	fscanf(input, "%d", &nn);

	N = nn - 1;
	d = (int*)malloc(sizeof(int*)*nn);

	for (i = 0; i < nn; i++)
		fscanf(input, "%d", &(d[i]));

	p = (int**)malloc(sizeof(int*)*N);
	for (i = 0; i < N; i++)
		p[i] = (int*)malloc(sizeof(int*)*N);

	minmult(N, d, p);
	print_order(N, 0, N - 1, p, output);

	for (i = 0; i < N; i++)
		free(p[i]);
	free(p);
	free(d);

	fclose(input);
	fclose(output);

	return 0;
}
