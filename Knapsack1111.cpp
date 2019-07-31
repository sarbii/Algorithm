
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

double W; // �ڷ翡 ���� �� �ִ� ����
int n; // ������ �� ����
double *w; // ���ǵ��� ���� 1~n (0 ~ n-1 �� �ϸ� �ȵ�)
double *p; // ���ǵ��� ��ġ // ��������
int heapLimit; // ���� �޸� ũ��

//heap
typedef struct
{
	int level;
	int *bIn; // level��° ������ �־����� 1 �ȳ־����� 0
	double profit;
	double weight;
	double bound;
}node;
typedef struct
{
	node *s;
	int heapsize;
}heap;
void shiftdown(heap *H, int i)
{
	node shiftkey;
	int parent;
	int found;
	int largerchild;

	shiftkey = H->s[i];
	parent = i;
	found = 0;
	while ((2 * parent <= H->heapsize) && !found)
	{
		if ((2 * parent < H->heapsize) && (H->s[2 * parent].bound < H->s[2 * parent + 1].bound))
			largerchild = 2 * parent + 1;
		else
			largerchild = 2 * parent;
		if (shiftkey.bound < H->s[largerchild].bound)
		{
			H->s[parent] = H->s[largerchild];
			parent = largerchild;
		}
		else
			found = 1;
	}
	H->s[parent] = shiftkey;
}
node deleteMax(heap *H) // delete Max
{
	node keyout;
	keyout = H->s[1];
	H->s[1] = H->s[H->heapsize];
	H->heapsize = H->heapsize - 1;
	shiftdown(H, 1);
	return keyout;
}
void insert(heap *H, node *newnode)
{
	int parent;
	heap tH; // ���� �ּҸ� ��� ����
	H->heapsize = H->heapsize + 1;
	if (H->heapsize == heapLimit) // ���� �޸��Ҵ緮�� ������ 2��� �ٽ� �Ҵ�
	{
		heapLimit = heapLimit * 2;
		tH.s = H->s;
		H->s = (node *)malloc(sizeof(node)*heapLimit);
		memcpy(H->s, tH.s, sizeof(node)*(heapLimit / 2));
		free(tH.s);
	}
	H->s[H->heapsize].bIn = (int*)malloc(sizeof(int)*n);
	memcpy(H->s[H->heapsize].bIn, newnode->bIn, sizeof(int)*n);
	H->s[H->heapsize].bound = newnode->bound;
	H->s[H->heapsize].level = newnode->level;
	H->s[H->heapsize].profit = newnode->profit;
	H->s[H->heapsize].weight = newnode->weight;

	parent = H->heapsize / 2;
	while (parent > 0)
	{
		shiftdown(H, parent);
		parent = parent / 2;
	}
}
double bound(node u)
{
	int j, k;
	double totweight;
	double result;

	if (u.weight >= W)
		return 0;
	else
	{
		result = u.profit;
		j = u.level + 1;
		totweight = u.weight;
		while (j <= n && totweight + w[j] <= W)
		{
			totweight = totweight + w[j];
			result = result + p[j];
			j++;
		}
		k = j;
		if (k <= n)
			result = result + (W - totweight)*(p[k] / w[k]);
		return result;
	}
}
void knapsack(double *maxprofit, node *maxnode) // maxnode���� �����Ҵ��� ���� node�� �޴´�.
{
	heap H;
	node u, v;
	// �� �ʱ�ȭ
	H.heapsize = 0;
	heapLimit = 100; // ó���� heap ��� �뷮�� 100���� ��´�.
	H.s = (node *)malloc(sizeof(node)*heapLimit);
	// ��
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	*maxprofit = 0;
	v.bound = bound(v);
	u.bIn = (int *)malloc(sizeof(int)*n);
	memset(u.bIn, 0, sizeof(int)*n);
	v.bIn = (int *)malloc(sizeof(int)*n);
	memset(v.bIn, 0, sizeof(int)*n);
	insert(&H, &v);
	free(v.bIn);

	while (H.heapsize != 0)
	{
		v = deleteMax(&H);
		if (v.bound > *maxprofit)
		{
			u.level = v.level + 1;
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			memcpy(u.bIn, v.bIn, sizeof(int)*n);
			if (u.weight <= W && u.profit > *maxprofit)
			{
				*maxprofit = u.profit;
				u.bIn[u.level - 1] = 1;
				memcpy(maxnode->bIn, u.bIn, sizeof(int)*n);
			}
			u.bound = bound(u);
			if (u.bound > *maxprofit)
			{
				u.bIn[u.level - 1] = 1;
				insert(&H, &u);
			}
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(u);
			if (u.bound > *maxprofit)
			{
				u.bIn[u.level - 1] = 0;
				insert(&H, &u);
			}
		}
		free(v.bIn);
	}
	free(H.s);
	free(u.bIn);
}
int main()
{
	FILE *pInputStream, *pOutputStream;
	char inputFileName[50];
	int i, j;
	double tP, tW;
	double maxprofit;
	int *result; // �Է°��� profit/weight ������ sorting �����ϱ� ����Ҷ� �ٽ� ������� �������� ���
	int tS;
	int *seq; // �Է°��� ������ �����ߴٰ� ����Ҷ� ����.
	node maxnode;

	printf("input file name? ");
	scanf("%s", inputFileName);
	if ((pInputStream = fopen(inputFileName, "r")) == NULL)
	{
		printf("%s file cannot be opened!\n", inputFileName);
		return 0;
	}
	if (fscanf(pInputStream, "%d %lf", &n, &W) == EOF)
	{
		printf("file is not in right form\n");
	}
	w = (double *)malloc(sizeof(double)*(n + 1));
	p = (double *)malloc(sizeof(double)*(n + 1));
	result = (int *)malloc(sizeof(double)*n);
	seq = (int *)malloc(sizeof(int)*(n + 1));
	for (i = 1; i <= n; i++) // seq[1]=1, seq[2] = 2, ~, seq[n] = n
		seq[i] = i;
	for (i = 0; i < n; i++)
	{
		if (fscanf(pInputStream, "%lf %lf", &p[i + 1], &w[i + 1]) == EOF)
		{
			printf("file is not in right form\n");
		}
	}
	

	for (i = 1; i < n; i++) // �Է¹��� profit, weight�� profit/weight�� ū ������ ����
	{
		for (j = n - 1; j >= i; j--)
		{
			if (p[j] / w[j] < p[j + 1] / w[j + 1])
			{
				tP = p[j];
				tW = w[j];
				p[j] = p[j + 1];
				w[j] = w[j + 1];
				p[j + 1] = tP;
				w[j + 1] = tW;
				tS = seq[j];
				seq[j] = seq[j + 1];
				seq[j + 1] = tS;
			}
		}
	}
	
	
	maxnode.bIn = (int *)malloc(sizeof(int)*n);
	
	knapsack(&maxprofit, &maxnode);


	for (i = 0; i < n; i++) // ���� ���� �������
		result[seq[i + 1] - 1] = maxnode.bIn[i];
	

	if ((pOutputStream = fopen("output.txt", "w")) == NULL)
	{
		printf("output.txt file cannot be opened!\n");
		return 0;
	}

	fprintf(pOutputStream, "%d", (int)maxprofit);
	for (i = 0; i < n; i++)
	{
		fprintf(pOutputStream, "\n%d", result[i]);
	}
	

	free(w);
	free(p);
	free(seq);
	free(result);
	fclose(pInputStream);
	fclose(pOutputStream);
	return 1;
}