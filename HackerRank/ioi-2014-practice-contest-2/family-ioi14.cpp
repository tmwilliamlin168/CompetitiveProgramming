#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int ax, ay, bx, by, cx, cy;
	cin >> ax >> ay >> bx >> by >> cx >> cy;
	array<int, 2> d[3]={{ax+bx-2*cx, ay+by-2*cy}, {ax+cx-2*bx, ay+cy-2*by}, {bx+cx-2*ax, by+cy-2*ay}};
	sort(d, d+3);
	for(int i=0; i<3; ++i)
		cout << d[i][0] << " " << d[i][1] << "\n";
}
