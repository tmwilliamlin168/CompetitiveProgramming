#include <bits/stdc++.h>
using namespace std;

class GridSpiral {
public:
	long long findCell(int d) {
		if(d%2==0)
			return -1;
		if(d<7)
			return 0;
		long long a=(d-7)/2;
		return (a+1)/2*(a/2+1);
	}
};
