#include <bits/stdc++.h>
using namespace std;

bool possible[2001];

void recur(int day, int ga, vector<int> a, int gb, vector<int> b) {
	if(day>=4) {
		//the end, mark possible
		possible[ga]=1;
		return;
	}
	if(day&1) {
		//tuesday or thursday
		for(int i=0; i<b.size(); ++i) {
			vector<int> newa=a, newb=b;
			newa.push_back(b[i]);
			newb.erase(newb.begin()+i);
			recur(day+1, ga+b[i], newa, gb-b[i], newb);
		}
	} else {
		//monday or wednesday
		for(int i=0; i<a.size(); ++i) {
			vector<int> newa=a, newb=b;
			newa.erase(newa.begin()+i);
			newb.push_back(a[i]);
			recur(day+1, ga-a[i], newa, gb+a[i], newb);
		}
	}
}

int main() {
	ifstream cin("backforth.in");
	ofstream cout("backforth.out");
	
	//input
	vector<int> a, b;
	int x, ans=0;
	for(int i=0; i<10; ++i) {
		cin >> x;
		a.push_back(x);
	}
	for(int i=0; i<10; ++i) {
		cin >> x;
		b.push_back(x);
	}
	//do recursion
	recur(0, 1000, a, 1000, b);
	//count number of answers
	for(int i=0; i<=2000; ++i)
		ans+=possible[i];
	cout << ans;
}
