//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWwXCn2KQjEDFATu&categoryId=AWwXCn2KQjEDFATu&categoryType=CODE
//SWEA8104
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case, N, K;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		cin >> K;
		int a[21] = {0};
		//a = {0};
		int sum = 0;
		
		for (int j = 1; j <= K; j++) {
			if (N == 1)
				a[j] = j;
			else if (N % 2 == 0)
				a[j] = K*N * N / 2 + (N / 2);
			else
				a[j] = (N + 1)*(N / 2)*K + (N + 1) / 2 +j-1;	
		}
		cout << "#"<<i+1<<" ";
		for (int j = 1; j <= K; j++)
			cout << a[j] << " ";
		cout << endl;
		}
		
		return 0;
	}
