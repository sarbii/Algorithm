//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWyNQrCahHcDFAVP&categoryId=AWyNQrCahHcDFAVP&categoryType=CODE
//swea8382
#include<iostream>
using namespace std;

int main(void)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int x1, x2, y1, y2, sub1, sub2,cnt1=0,cnt2=0;
		cin >> x1;
		cin >> y1;
		cin >> x2;		
		cin >> y2;
		sub1 = x2 - x1;
		sub2 = y2 - y1;
		if (sub1 < 0)
			sub1 = 0 - sub1;
		if (sub2 < 0)
			sub2 = 0 - sub2;
		cnt1 = sub2 - sub1;
		if (cnt1 < 0)
			cnt1 = 0 - cnt1;
		if (cnt1 % 2 == 0)
			cnt2 = cnt1 * 2;
		else
			cnt2 = cnt1 * 2 - 1;

		
		cout << "#" << test_case << " " << sub1 + sub2 +cnt2 -cnt1 << endl;



	}
}