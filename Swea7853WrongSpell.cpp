//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWttUKkq5hQDFASy&categoryId=AWttUKkq5hQDFASy&categoryType=CODE
//SWEA7853
#include<iostream>
#include<math.h>
#define a 1000000007
using namespace std;

int main(void)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		long long cnt = 0, result = 0;
		string str;
		cin >> str;
		cnt = str.length();
		if (cnt == 1)
			result = 1;
		else {
			if (str.at(0) == str.at(1))
				result = 1;
			else
				result = 2;
		}    
            

		for (int i = 1; i < cnt - 1; i++) {
			if (str.at(i - 1) == str.at(i) && str.at(i) == str.at(i + 1) && str.at(i - 1) == str.at(i+1) ){
				result = result;
            result = result % a;}
			else if (str.at(i - 1) != str.at(i) && str.at(i + 1) != str.at(i) && str.at(i + 1) != str.at(i-1)){
				result = 3 * result;
            result = result % a;}
			else{
				result = 2 * result;
            result = result % a;
            }
            }
        
        if (cnt >= 2) {
			if (str.at(cnt - 1) != str.at(cnt - 2)){
				result = 2 * result;
            result = result % a;}
		}
        
          if(cnt==3){
            if (str.at(2) != str.at(1) && str.at(0) != str.at(1) && str.at(0) == str.at(2) )
				result = 8;
        }
	
		result = result % a;
		cout << "#" << test_case << " " <<  result << endl;

	}
	return 0;
}
