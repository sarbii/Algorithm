#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	unsigned int id;
	double weight;
	double profit;
	double profit_density;
} item;

double knapsack(const double *weights, const double *profits,size_t n, double capacity, unsigned int **max_knapsack);
static void knapsack_recursive(const item *items, size_t n, double capacity,unsigned int *current_knapsack, double *current_weight, double *current_profit,
	unsigned int *max_knapsack, double *max_profit, unsigned int level);
static double profit_bound(const item *items, size_t n, double capacity,double current_weight, double current_profit,
	unsigned int level);
static int compare_items(const item *item1, const item *item2);


int main()
{
	FILE *output;
	FILE *input;
	int k, W;
	char inputFileName[50];

	unsigned int *max_knapsack;
	double *profits, *weights;


	printf("input file name? ");
	scanf("%s", inputFileName);
	input = fopen(inputFileName, "r");
	output = fopen("output.txt", "w");

	fscanf(input, "%d", &k);
	fscanf(input, "%d", &W);

	double capacity = W;
	const size_t n = k;

	weights = (double *)malloc(sizeof(double)*(n + 1));
	profits = (double *)malloc(sizeof(double)*(n + 1));



	for (int i = 0; i < k; i++)
	{
		fscanf(input, "%lf %lf", &profits[i], &weights[i]);

	}


	int max_profit = knapsack(weights, profits, n, capacity, &max_knapsack);

	
	fprintf(output, "%d", max_profit);
	for (int i = 0; i < n; i++) {
		if (max_knapsack[i] == 1) {
			fprintf(output, "\n1");
		}
		else {
			fprintf(output, "\n0");
		}
	}


	free(weights);
	free(profits);
	free(max_knapsack);
	fclose(input);
	fclose(output);

	return 1;
}

static int compare_items(const item *item1, const item *item2)
{
	if (item1->profit_density > item2->profit_density) {
		return -1;
	}
	if (item1->profit_density < item2->profit_density) {
		return 1;
	}
	return 0;
}

static double profit_bound(const item *items, size_t n, double capacity,
	double current_weight, double current_profit,
	unsigned int level)
{
	double remaining_capacity = capacity - current_weight;
	double bound = current_profit;
	unsigned int lvl = level;
	while (lvl < n &&
		items[lvl].weight <= remaining_capacity)
	{
		remaining_capacity -= items[lvl].weight;
		bound += items[lvl].profit;
		lvl++;
	}
	if (lvl < n) {
		bound += items[lvl].profit_density
			* remaining_capacity;
	}
	return bound;
}

static void knapsack_recursive(const item *items, size_t n, double capacity,
	unsigned int *current_knapsack, double *current_weight, double *current_profit,
	unsigned int *max_knapsack, double *max_profit, unsigned int level)
{
	if (level == n) {
		*max_profit = *current_profit;
		memcpy(max_knapsack, current_knapsack, n * sizeof(unsigned int));
		return;
	}
	if (*current_weight + items[level].weight <= capacity)
	{  	*current_weight += items[level].weight;
		*current_profit += items[level].profit;
		current_knapsack[items[level].id] = 1;
		knapsack_recursive(items, n, capacity, current_knapsack, current_weight,
			current_profit, max_knapsack, max_profit, level + 1);
		*current_weight -= items[level].weight;
		*current_profit -= items[level].profit;
		current_knapsack[items[level].id] = 0;
	}
	if (profit_bound(items, n, capacity, *current_weight,
		*current_profit, level + 1) > *max_profit) {
		knapsack_recursive(items, n, capacity, current_knapsack, current_weight,
			current_profit, max_knapsack, max_profit, level + 1);
	}
}

double knapsack(const double *weights, const double *profits,
	size_t n, double capacity, unsigned int **max_knapsack)
{
	double current_weight = 0.0;
	double current_profit = 0.0;
	double max_profit = 0.0;
	unsigned int i;
	item *items = (item*)malloc(n * sizeof(item));
	unsigned int *current_knapsack = (unsigned int*)calloc(n, sizeof(unsigned int));
	*max_knapsack = (unsigned int*)malloc(n * sizeof(unsigned int));
	if (!(items && current_knapsack && *max_knapsack)) {
		free(items);
		free(current_knapsack);
		free(*max_knapsack);
		*max_knapsack = NULL;
		return 0;
	}
	for (i = 0; i < n; i++) {
		items[i].id = i;
		items[i].weight = weights[i];
		items[i].profit = profits[i];
		items[i].profit_density = profits[i] / weights[i];
	}
	qsort(items, n, sizeof(item),
		(int(*)(const void *, const void *))compare_items);
	knapsack_recursive(items, n, capacity, current_knapsack, &current_weight,
		&current_profit, *max_knapsack, &max_profit, 0);
	free(items);
	free(current_knapsack);
	return max_profit;
}





