/*
	- Try to satisfy a[i] < a[i+k]
	- Try to fill the "?"s from 0, then +-1, +-2, ...
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, INF=2e9;
int n, k, a[mxN];

inline void fk() {
	cout << "Incorrect sequence";
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		string s;
		cin >> s;
		a[i]=s=="?"?INF:stoi(s);
	}
	for(int ki=0; ki<k; ++ki) {
		for(int i=ki, lv=-INF; i<n;) {
			if(a[i]!=INF) {
				lv=a[i];
				i+=k;
				continue;
			}
			int j=i, nv;
			while(j<n&&a[j]==INF)
				j+=k;
			nv=j>=n?INF:a[j];
			if(nv<=0)
				for(int m=j-k; m>=i; m-=k)
					a[m]=--nv;
			else if(lv>=0)
				for(int m=i; m<j; m+=k)
					a[m]=++lv;
			else {
				int nf=(j-i)/k;	
				if(min(abs(lv), abs(nv))<=(nf+1)/2) {
					if(abs(lv)<abs(nv))
						for(int m=i; m<j; m+=k)
							a[m]=++lv;
					else
						for(int m=j-k; m>=i; m-=k)
							a[m]=--nv;
				} else {
					lv=-nf/2;
					for(int m=i; m<j; m+=k)
						a[m]=lv++;
				}
			}
			i=j;
		}
		for(int i=ki; i+k<n; i+=k)
			if(a[i]>=a[i+k])
				fk();
	}
	for(int i=0; i<n; ++i)
		cout << a[i] << " ";
}
