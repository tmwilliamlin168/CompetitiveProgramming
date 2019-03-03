#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n;
double p[mxN], ans, a, b=1;

int main() {
	ifstream cin("cowdate.in");
	ofstream cout("cowdate.out");

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> p[i], p[i]/=1e6;
	for(int i1=0, i2=0; i1<n; ++i1) {
		while(i2<n&&a<1) {
			a+=p[i2]/(1-p[i2]);
			b*=(1-p[i2]);
			++i2;
		}
		ans=max(a*b, ans);
		a-=p[i1]/(1-p[i1]);
		b/=(1-p[i1]);
	}
	cout << (int)(ans*1e6);
}
