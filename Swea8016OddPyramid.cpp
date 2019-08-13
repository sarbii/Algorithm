

#include<iostream>
#include<math>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int t arr[1024];
		cin >> t;
		for (int j = 1; j < pow(2, t); j++) {
			cin >> arr[i];
		}
	//	cout << arr[pow(2, t - 1)] << endl;
		cout << "#" << test_case << " "

		for (int j = 1; j < t; j++) {
			for (int p = 0; p < pow(2, j); p++) {
				if (t - j - 1 > t)
					break;
				cout << arr[pow(2,t-j-1)+p*pow(2,t-j) <<endl;
			}
			 
		}








		 
	}
	return 0;
}