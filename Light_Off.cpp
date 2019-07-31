#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



int light_off(int L, int R, int N, int M, int *D, int *W, int ***EE, int ***DD, int ***PP) {
	int i, j, diagonal;
	int DD1, DD2, EE1, EE2;

	EE[M - 1][M - 1][0] = 0;
	EE[M - 1][M - 1][1] = 0;
	for (i = 0; i < N; i++) {
		DD[i][i][0] = 0;
		DD[i][i][1] = 0;
		PP[i][i][0] = 0;
		PP[i][i][1] = 0;

		if (i != (M - 1)) {
			EE[i][i][0] = 2147483647;
			EE[i][i][1] = 2147483647;
		}
	}

	for (diagonal = 1; diagonal < N; diagonal++) {
		for (i = 0; i < (N - diagonal); i++) {
			j = i + diagonal;

			DD1 = DD[i + 1][j][0] + D[i + 1] - D[i];
			DD2 = DD[i + 1][j][1] + D[j] - D[i];

			if (EE[i + 1][j][0] != 2147483647)
				EE1 = EE[i + 1][j][0] + (DD1 * W[i]);
			else
				EE1 = 2147483647;

			if (EE[i + 1][j][1] != 2147483647)
				EE2 = EE[i + 1][j][1] + (DD2 * W[i]);
			else
				EE2 = 2147483647;

			if (EE1 < EE2) {
				EE[i][j][0] = EE1;
				DD[i][j][0] = DD1;
				PP[i][j][0] = i + 1;
			}
			else {
				EE[i][j][0] = EE2;
				DD[i][j][0] = DD2;
				PP[i][j][0] = j;
			}

			DD1 = DD[i][j - 1][0] + D[j] - D[i];
			DD2 = DD[i][j - 1][1] + D[j] - D[j - 1];

			if (EE[i][j - 1][0] != 2147483647)
				EE1 = EE[i][j - 1][0] + (DD1 * W[j]);
			else
				EE1 = 2147483647;

			if (EE[i][j - 1][1] != 2147483647)
				EE2 = EE[i][j - 1][1] + (DD2 * W[j]);
			else
				EE2 = 2147483647;

			if (EE1 < EE2) {
				EE[i][j][1] = EE1;
				DD[i][j][1] = DD1;
				PP[i][j][1] = i;
			}
			else {
				EE[i][j][1] = EE2;
				DD[i][j][1] = DD2;
				PP[i][j][1] = j - 1;
			}
		}
	}

	if (EE[L][R][0] < EE[L][R][1])
		return 0;
	else
		return 1;
}
void print_path(int L, int R, int M, int ***PP, int result, FILE *output) {

	if (result != M) {
		if (L == result)
			print_path(L + 1, R, M, PP, PP[L][R][0], output);
		else
			print_path(L, R - 1, M, PP, PP[L][R][1], output);
	}

	fprintf(output, "%d\n", result + 1);
}

int main(void) {
	FILE *input;
	FILE *output;

	char file_name[100];
	int i, j, N, M, last, L, R;
	int *D, *W, ***DD, ***EE, ***PP;
	

	printf("input file name?");
	scanf("%s", file_name);
	input = fopen(file_name, "r");
	output = fopen("output.txt", "w");

	fscanf(input, "%d", &N);
	fscanf(input, "%d", &M);

	L = 0; R = N - 1;

	D = (int*)malloc(sizeof(int*)*N);
	W = (int*)malloc(sizeof(int*)*N);

	for (i = 0; i < N; i++) {
		fscanf(input, "%d %d", &D[i], &W[i]);
	}

	DD = (int***)malloc(sizeof(int*)*N);
	EE = (int***)malloc(sizeof(int*)*N);
	PP = (int***)malloc(sizeof(int*)*N);
	for (i = 0; i < N; i++) {
		DD[i] = (int**)malloc(sizeof(int*)*N);
		EE[i] = (int**)malloc(sizeof(int*)*N);
		PP[i] = (int**)malloc(sizeof(int*)*N);
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			DD[i][j] = (int*)malloc(sizeof(int*) * 2);
			EE[i][j] = (int*)malloc(sizeof(int*) * 2);
			PP[i][j] = (int*)malloc(sizeof(int*) * 2);
		}
	}

	last = light_off(0, N - 1, N, M, D, W, EE, DD, PP);

	fprintf(output, "%d\n", EE[0][N - 1][last]);

	print_path(0, N - 1, M - 1, PP, last ? R : L, output);

	free(D);
	free(W);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			free(DD[i][j]);
			free(EE[i][j]);
			free(PP[i][j]);
		}
	}
	for (i = 0; i < N; i++) {
		free(DD[i]);
		free(EE[i]);
		free(PP[i]);
	}
	free(DD);
	free(EE);
	free(PP);

	fclose(input);
	fclose(output);

	return 0;
}




