#include <bits/stdc++.h>
using namespace std;

bool solve(int n, int a, string sa, string sb, char ca, char cb, int s) {
	int l=0, r=s+1;
	for(int i=n-1; ~i; --i) {
		if(sb[i]==ca)
			r = min(r+1, s+1);
		if(sb[i]==cb)
			l = max(l-1, 0);
		if(sa[i]==ca)
			++l;
		if(sa[i]==cb)
			--r;
		if(l+1>=r)
			return 0;
	}
	return l<a&&a<r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int h, w, n, sr, sc;
	string sa, sb;
	cin >> h >> w >> n >> sr >> sc >> sa >> sb;
	cout << (solve(n, sr, sa, sb, 'U', 'D', h)&&solve(n, sc, sa, sb, 'L', 'R', w)?"YES":"NO");
}
