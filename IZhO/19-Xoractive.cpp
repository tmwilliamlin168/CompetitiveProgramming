#include "interactive.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> guess(int n) {
	int k=-1;
	while(n>1<<++k);
	vector<int> ans, c[k];
	ans.push_back(ask(1));
	for(int j=0; j<k; ++j) {
		vector<int> a;
		for(int i=0; i<n; ++i)
			if(i>>j&1)
				a.push_back(i+1);
		vector<int> b=get_pairwise_xor(a);
		a.push_back(1);
		c[j]=get_pairwise_xor(a);
		c[j].erase(c[j].begin());
		for(int d : b)
			c[j].erase(find(c[j].begin(), c[j].end(), d));
		for(int &d : c[j])
			d^=ans[0];
	}
	for(int i=1; i<n; ++i) {
		vector<int> v;
		for(int j=0; j<k; ++j) {
			if(i>>j&1^1)
				continue;
			if(v.size()) {
				vector<int> w;
				for(int b : c[j])
					if(find(v.begin(), v.end(), b)!=v.end())
						w.push_back(b);
				v=w;
			} else
				v=c[j];
		}
		for(int j=0; j<k; ++j)
			if(i>>j&1^1)
				for(int b : c[j])
					if(find(v.begin(), v.end(), b)!=v.end())
						v.erase(find(v.begin(), v.end(), b));
		ans.push_back(v[0]);
	}
	return ans;
}
