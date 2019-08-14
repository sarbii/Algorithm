//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWuSgKpqmooDFASy&categoryId=AWuSgKpqmooDFASy&categoryType=CODE
//SWEA7964

#include<iostream>
#include<vector>

using namespace std;

int main(void)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int city, door,  clk = 0, door_clk = 0;
		//int arr[30000];
        vector<int> arr(300001);
		cin >> city;
		cin >> door;
		for (int j = 0; j < city ; j++) 
		{
			cin >> arr[j];
		}
		if (arr[0] == 0) 
		{
			door_clk++;
			arr[0] = 1;
		}
		if (arr[city-1] == 0)
		{
			door_clk++;
			arr[city-1] = 1;
		}
		for (int j = 0; j < city; j++) 
		{
			if (arr[j] == 0)
				clk++;
            else
                clk=0;
			if (clk == door){
				door_clk++;
                clk=0;
            }
            
		}		
		
		cout << "#" << test_case << " " <<door_clk <<endl;

	}
	return 0;
}