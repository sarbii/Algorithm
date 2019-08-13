//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWu1JmN6Js4DFASy&categoryId=AWu1JmN6Js4DFASy&categoryType=CODE
//SEWA7985

#include<iostream>
#include<math.h>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int t ,arr[1024];
		cin >> t;
		for (int j = 1; j < pow(2, t); j++) {
			cin >> arr[j];
		}
		int a = pow(2, t - 1);
			
		cout << "#" << test_case << " ";
		cout << arr[a] << endl;
			for (int j = 1; j < t; j++) {
				for (int p = 0; p < pow(2, j); p++) {
					if (t - j - 1 > t)
						break;
					int b = pow(2, t - j - 1) + p * pow(2, t - j);
					cout << arr[b]<< " ";
				}
				cout << endl;
			}

	}
	return 0;
}