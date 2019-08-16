//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWrDLM0aRA8DFARG&categoryId=AWrDLM0aRA8DFARG&categoryType=CODE
//SWEA7732
#include<iostream>
#include<string>



using namespace std;

int main(void)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		long long cnt = 0, result = 0;
		int h1, h2, m1, m2, s1, s2,h3,m3,s3;
		string str1, str2;
		cin >> str1;
		cin >> str2;
		h1 = str1.at(0) * 10 + str1.at(1);
		h2 = str2.at(0) * 10 + str2.at(1);
		m1 = str1.at(3) * 10 + str1.at(4);
		m2 = str2.at(3) * 10 + str2.at(4);
		s1 = str1.at(6) * 10 + str1.at(7);
		s2 = str2.at(6)* 10 + str2.at(7);

		
			s3 = s2 - s1;
			if (s3 < 0) {
				s3 = s3 + 60;
				m2 = m2 - 1;				
			}
			m3 = m2 - m1;
			if (m3 < 0) {
				m3 = m3 + 60;
				h2 = h2 - 1;
			}			
			h3 = h2 - h1;
			if (h3 < 0) {
				h3 = h3 + 24;
			}
		if(h3<10)
			cout << "#" << test_case << " 0" << h3;
        else
            cout << "#" << test_case << " " << h3;
        if(m3<10)
        	cout<< ":0" << m3;
        else
            cout<< ":" << m3;
        if(s3<10)    
        	cout<< ":0" << s3<< endl;
        else
            cout<< ":" << s3<< endl;



	}
}