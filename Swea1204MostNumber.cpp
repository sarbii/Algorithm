//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV13zo1KAAACFAYh&categoryId=AV13zo1KAAACFAYh&categoryType=CODE
//swea1204mostnumber


#include<iostream>

 
using namespace std;
 
 
 
int main(void) {
 
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int tt;
        cin >> tt;
        int most=0,test[1000],score[101]={0},qq;
        for (int j = 0; j < 1000; j++) {
            cin >> test[j];
            for (int q = 0; q < 101; q++) {
                if (q == test[j])
                    score[q]++;
            }
        }
        
        for (int q = 100; q>=0; q--) {
            if(most<score[q]){
                most=score[q];
                qq=q;
            }
                 
             
        }
         
 
 
        cout << "#" << tt << " " << qq << endl;
    }
}