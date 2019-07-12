#include "transfer.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> get_attachment(vector<int> s) {
	int x=0;
	for(int i=0; i<s.size(); ++i)
		if(s[i])
			x^=i+1;
	vector<int> v{__builtin_popcount(x)&1};
	for(; x; x/=2)
		v.push_back(x&1);
	return v;
}

vector<int> retrieve(vector<int> d) {
	int n=d.size()>=255?255:63, x=0;
	for(int i=d.size()-1; i>n; --i)
		x=x*2+d[i];
	vector<int> v=vector<int>(d.begin(), d.begin()+n);
	if((__builtin_popcount(x)^d[n])&1)
		return v;
	for(int i=0; i<n; ++i)
		if(d[i])
			x^=i+1;
	if(x)
		v[x-1]^=1;
	return v;
}
