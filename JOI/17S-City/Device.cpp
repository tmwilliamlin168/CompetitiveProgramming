#include "Device.h"
#include <bits/stdc++.h>
using namespace std;

void InitDevice() {}

int Answer(long long s, long long t) {
	auto decrange=[](int x) {
		int l=1, r=1<<11;
		while(l<r) {
			int m=(l+r+1)/2;
			if(m*(m-1)/2<=x)
				l=m;
			else
				r=m-1;
		}
		return array<int, 2>{x-r*(r-1)/2, r};
	};
	auto inr=[](int x, array<int, 2> r) {
		return r[0]<=x&&x<r[1];
	};
	if(s>>26&&t>>26) {
		if((s>>15^t>>15)&(1<<11)-1)
			return 2;
		array<int, 2> rs=decrange(s&(1<<15)-1), rt=decrange(t&(1<<15)-1);
		return inr(rt[0], rs)?1:(inr(rs[0], rt)?0:2);
	}
	if(s>>26)
		return inr(s>>15&(1<<11)-1, decrange(t&(1<<21)-1))?0:2;
	if(t>>26)
		return inr(t>>15&(1<<11)-1, decrange(s&(1<<21)-1))?1:2;
	int sd=s>>21, td=t>>21;
	array<int, 2> rs=decrange(s&(1<<21)-1), rt=decrange(t&(1<<21)-1);
	return td>sd&&inr(rt[0], rs)?1:(sd>td&&inr(rs[0], rt)?0:2);
}
