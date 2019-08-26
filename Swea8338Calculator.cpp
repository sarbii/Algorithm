//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWxpQia60FgDFAWL&categoryId=AWxpQia60FgDFAWL&categoryType=CODE
//SWEA8338

#include<iostream>
using namespace std;
int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int cnt = 0, result = 0;
		int tt=0,t=0;
		cin >> t;
		for (int i = 0; i < t; i++) {
			cin >> tt;
			if (result + tt > result*tt)
				result = result + tt;
			else
				result = result * tt;
		}
		cout << "#" << test_case << " " << result << "\n";
	}
}