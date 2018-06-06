/*
	- Apply (x, y) -> (x+y, x-y) so the distance function is now max(|x1-x2|, |y1-y2|)
	- Binary search by answer
	- Problem becomes to check if some points can be covered by 2 squares
	- One square has its left side at the minimum x and the other has its right side at the maximum x
	- Similarly, one square has its bottom side at the minimum y and the other has its top side at the maximum y
	- Bounds are just high enough that long long has to be used
*/

#include "group.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int getMinimumDelay(int n, vector<int> x, vector<int> y) {
	ll mnx=2e9, mxx=0, mny=1e9, mxy=-1e9;
	for(int i=0; i<n; ++i) {
		x[i]=x[i]+y[i], y[i]=x[i]-2*y[i];
		mnx=min((ll)x[i], mnx), mxx=max((ll)x[i], mxx);
		mny=min((ll)y[i], mny), mxy=max((ll)y[i], mxy);
	}
	ll lb=0, rb=1.5e9;
	while(lb<=rb) {
		ll mb=(lb+rb)/2;
		bool ok1=1, ok2=1;
		for(int i=0; i<n&&(ok1||ok2); ++i) {
			ok1&=x[i]<=mnx+mb&&y[i]<=mny+mb||x[i]>=mxx-mb&&y[i]>=mxy-mb;
			ok2&=x[i]<=mnx+mb&&y[i]>=mxy-mb||x[i]>=mxx-mb&&y[i]<=mny+mb;
		}
		if(ok1||ok2)
			rb=mb-1;
		else
			lb=mb+1;
	}
	return lb;
}
