#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void Miro(int N, int **W, char **touch, int **length) {
	int neari, nearj, min;
	int i, j;

	while (1) {
		min = 2147483647;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (length[i][j] > -1 && length[i][j] < min) {
					min = length[i][j];
					neari = i;
					nearj = j;
				}
			}
		}

		if (neari == N - 1 && nearj == N - 1)	break;

		if (neari > 0 && length[neari - 1][nearj] > (length[neari][nearj] + W[neari - 1][nearj])) {
			touch[neari - 1][nearj] = 'D';
			length[neari - 1][nearj] = (length[neari][nearj] + W[neari - 1][nearj]);
		}

		if (neari < N - 1 && length[neari + 1][nearj] >(length[neari][nearj] + W[neari + 1][nearj])) {
			touch[neari + 1][nearj] = 'U';
			length[neari + 1][nearj] = (length[neari][nearj] + W[neari + 1][nearj]);
		}

		if (nearj > 0 && length[neari][nearj - 1] > (length[neari][nearj] + W[neari][nearj - 1])) {
			touch[neari][nearj - 1] = 'R';
			length[neari][nearj - 1] = (length[neari][nearj] + W[neari][nearj - 1]);
		}

		if (nearj < N - 1 && length[neari][nearj + 1] >(length[neari][nearj] + W[neari][nearj + 1])) {
			touch[neari][nearj + 1] = 'L';
			length[neari][nearj + 1] = (length[neari][nearj] + W[neari][nearj + 1]);
		}

		length[neari][nearj] = -1;
	}
}

void print_path(int N, int i, int j, char **touch, FILE* output) {
	if (touch[i][j] == 'L')
		print_path(N, i, j - 1, touch, output);
	else if (touch[i][j] == 'R')
		print_path(N, i, j + 1, touch, output);
	else if (touch[i][j] == 'U')
		print_path(N, i - 1, j, touch, output);
	else if (touch[i][j] == 'D')
		print_path(N, i + 1, j, touch, output);
	fprintf(output, "%d %d\n", i + 1, j + 1);
}


int main(void) {
	FILE *input;
	FILE *output;

	char file_name[100], **touch;
	int i, j, **length, **W, N;
	
	

	printf("input file name?");
	scanf("%s", file_name);
	input = fopen(file_name, "r");
	output = fopen("output.txt", "w");

	fscanf(input, "%d", &N);

	touch = (char**)malloc(sizeof(char*)*N);
	length = (int**)malloc(sizeof(int*)*N);
	W = (int**)malloc(sizeof(int*)*N);

	for (i = 0; i < N; i++) {
		touch[i] = (char*)malloc(sizeof(char*)*N);
		length[i] = (int*)malloc(sizeof(int*)*N);
		W[i] = (int*)malloc(sizeof(int*)*N);
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fscanf(input, "%1d", &(W[i][j]));
			if (W[i][j] == 1)
				W[i][j] = 0;
			else
				W[i][j] = 1;
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			touch[i][j] = 'X';
		}
	}
	touch[0][0] = 'S';

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			length[i][j] = 2147483647;
		}
	}
	length[0][0] = 0;

	Miro(N, W, touch, length);

	fprintf(output, "%d\n", length[N - 1][N - 1]);
	print_path(N, N - 1, N - 1, touch, output);

	for (i = 0; i < N; i++) {
		free(touch[i]);
		free(length[i]);
		free(W[i]);
	}
	free(touch);
	free(length);
	free(W);

	fclose(input);
	fclose(output);

	return 0;
}



