#include "vassal.h"
#include <bits/stdc++.h>
using namespace std;

map<int, vector<int>> mp;
void Init(long long b, vector<int> c) {
	for(int i=0; i<c.size(); ++i)
		mp[c[i]].push_back(i);
}

int Maid(int w) {
	auto it=mp.lower_bound(w);
	if(it==mp.end())
		return -1;
	int a=it->second.back();
	it->second.pop_back();
	if(it->second.empty())
		mp.erase(it);
	return a;
}
