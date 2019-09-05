#include "museum.h"
#include <bits/stdc++.h>
using namespace std;

long long CountSimilarPairs(vector<int> b, vector<int> t, vector<int> g) {
	long long ans=0;
	for(int i=1; i<8; ++i) {
		unordered_map<int, int> mp;
		for(int j=0; j<b.size(); ++j) {
			int k=((i&1?b[j]:0)*101+(i&2?t[j]:0))*101+(i&4?g[j]:0);
			ans+=(mp[k]++)*(__builtin_popcount(i)%2*2-1);
		}
	}
	return ans;
}
