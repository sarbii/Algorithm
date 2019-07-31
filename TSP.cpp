#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int n; 
int **adjMatrix; 
int heapLimit; 

typedef struct
{
	int level;
	int *path;
	int bound;
}node;
typedef struct
{
	node *s;
	int heapsize;
}heap;

void travel(int *opttour);
int bound(node *v);
void insert(heap *H, node *newnode);
void shiftdown(heap *H, int i);
node deleteMin(heap *H);



int main()
{
	FILE *input, *output;
	char inputFileName[50];
	int *opttour; 
	int i, j;

	printf("input file name? ");
	scanf("%s", inputFileName);
	if ((input = fopen(inputFileName, "r")) == NULL)
	{
		printf("%s file cannot be opened!\n", inputFileName);
		return 0;
	}
	if (fscanf(input, "%d", &n) == EOF)
	{
		printf("file is not in right form\n");
	}
	opttour = (int *)malloc(sizeof(int)*(n + 1));
	adjMatrix = (int **)malloc(sizeof(int *)*n); 
	for (i = 0; i < n; i++)
	{
		adjMatrix[i] = (int *)malloc(sizeof(int)*n);
		for (j = 0; j < n; j++)
		{
			if (fscanf(input, "%d", &adjMatrix[i][j]) == EOF)
			{
				printf("file is not in right form\n");
			}
		}
	}
	travel(opttour);

	if ((output = fopen("output.txt", "w")) == NULL)
	{
		printf("output.txt file cannot be opened!\n");
		return 0;
	}
	for (i = 0; i < n; i++)
		fprintf(output, "%d\n", opttour[i]);
	fprintf(output, "%d", opttour[n]);

	fclose(input);
	fclose(output);
	free(opttour);
	for (i = 0; i < n; i++)
	{
		free(adjMatrix[i]);
	}
	free(adjMatrix);
	return 1;
}

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
		if ((2 * parent < H->heapsize) && (H->s[2 * parent].bound > H->s[2 * parent + 1].bound))
			largerchild = 2 * parent + 1;
		else
			largerchild = 2 * parent;
		if (shiftkey.bound > H->s[largerchild].bound)
		{
			H->s[parent] = H->s[largerchild];
			parent = largerchild;
		}
		else
			found = 1;
	}
	H->s[parent] = shiftkey;
}
node deleteMin(heap *H)
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
	heap tH;
	H->heapsize = H->heapsize + 1;
	if (H->heapsize == heapLimit)
	{
		heapLimit = heapLimit * 2;
		tH.s = H->s;
		H->s = (node *)malloc(sizeof(node)*heapLimit);
		memcpy(H->s, tH.s, sizeof(node)*(heapLimit / 2));
		free(tH.s);
	}
	H->s[H->heapsize].path = (int*)malloc(sizeof(int)*(n + 1));
	memcpy(H->s[H->heapsize].path, newnode->path, sizeof(int)*(n + 1));
	H->s[H->heapsize].bound = newnode->bound;
	H->s[H->heapsize].level = newnode->level;

	parent = H->heapsize / 2;
	while (parent > 0)
	{
		shiftdown(H, parent);
		parent = parent / 2;
	}
}
int bound(node *v)
{
	int i, j, k;
	int min;
	int result;
	int bFound;

	result = 0;
	if (v->level == 0)
	{
		for (i = 0; i < n; i++)
		{
			min = 9000;
			for (j = 0; j < n; j++)
			{
				if (adjMatrix[i][j] < min && adjMatrix[i][j] > 0)
					min = adjMatrix[i][j];
			}
			result += min;
		}
		return result;
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			bFound = 0;
			for (j = 0; j < v->level; j++)
			{
				if (v->path[j] == i + 1)
				{
					bFound = 1;
					result += adjMatrix[i][v->path[j + 1] - 1];
					break;
				}
			}
			if (bFound)
				continue;
			if (bFound == 0 && v->path[v->level] == i + 1)
			{
				min = 9000;
				for (j = 1; j < n; j++)
				{
					bFound = 0;
					for (k = 1; k <= v->level; k++)
					{
						if ((j + 1) == v->path[k])
							bFound = 1;
					}
					if (!bFound && adjMatrix[i][j] < min)
						min = adjMatrix[i][j];
				}
				result += min;
			}
			else
			{
				min = 9000;
				for (j = 0; j < n; j++)
				{
					bFound = 0;
					for (k = 1; k <= v->level; k++)
					{
						if ((j + 1) == v->path[k])
							bFound = 1;
					}
					if (!bFound && adjMatrix[i][j] < min && adjMatrix[i][j] > 0)
						min = adjMatrix[i][j];
				}
				result += min;
			}
		}
	}

	return result;
}
void travel(int *opttour)
{
	heap H;
	node u, v;
	int minlength, tlength;
	int i, j, k;
	int bFound;
	H.heapsize = 0;
	heapLimit = 100;
	H.s = (node *)malloc(sizeof(node)*heapLimit);

	u.path = (int *)malloc(sizeof(int)*(n + 1));
	v.level = 0;
	v.path = (int *)malloc(sizeof(int)*(n + 1));
	v.path[0] = 1;
	v.bound = bound(&v);
	minlength = 9000;
	insert(&H, &v);
	free(v.path);
	while (H.heapsize != 0)
	{
		v = deleteMin(&H);
		if (v.bound < minlength)
		{
			u.level = v.level + 1;
			for (i = 2; i <= n; i++)
			{
				bFound = 0;
				for (j = 1; j <= v.level; j++)
				{
					if (v.path[j] == i)
					{
						bFound = 1;
						break;
					}
				}
				if (bFound)
					continue;
				else
				{
					memcpy(u.path, v.path, sizeof(int)*(n + 1));
					u.path[u.level] = i;
				}
				if (u.level == n - 2)
				{
					for (j = 2; j <= n; j++)
					{
						bFound = 0;
						for (k = 1; k <= u.level; k++)
						{
							if (j == u.path[k])
								bFound = 1;
						}
						if (!bFound)
						{
							u.path[u.level + 1] = j;
							break;
						}
					}
					u.path[u.level + 2] = 1;
					tlength = bound(&u);
					if (tlength < minlength)
					{
						minlength = tlength;
						memcpy(opttour, u.path, sizeof(int)*(n + 1));
					}
				}
				else
				{
					u.bound = bound(&u);
					if (u.bound < minlength)
						insert(&H, &u);
				}
			}
		}
		free(v.path);
	}
	free(H.s);
	free(u.path);
}