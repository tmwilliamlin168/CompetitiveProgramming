#include "assistant.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
bool e[mxN];

void Assist(unsigned char *a, int n, int k, int r) {
	vector<int> v;
	for(int i=0; i<k; ++i) {
		v.push_back(i);
		e[i]=1;
	}
	for(int i=0, j=0; i<n; ++i) {
		int c=GetRequest();
		if(!e[c]) {
			while(1) {
				int u=v.back();
				v.pop_back();
				if(a[j++]) {
					e[u]=0;
					PutBack(u);
					break;
				}
			}
		}
		e[c]=1;
		v.push_back(c);
	}
}
