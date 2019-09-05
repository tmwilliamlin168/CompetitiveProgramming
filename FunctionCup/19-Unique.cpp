#include "unique.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> PickUnique(int n) {
	vector<int> a(1), b(1);
	for(int i=0; i<n; ++i)
		a.push_back(UniqueCount(0, i));
	for(int i=n-1; ~i; --i)
		b.push_back(UniqueCount(i, n-1));
	vector<int> c(n);
	for(int i=0; i<n; ++i)
		c[i]=a[i+1]-a[i]>0&&b[n-i]-b[n-1-i]>0;
	return c;
}
