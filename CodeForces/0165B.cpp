#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	int lb=1, rb=1e9; //Left bound and right bound for answer, inclusive
	while(lb<rb) { //While we don't know the answer
		int mb=(lb+rb)/2, v=mb, s=0; //Guess the middle
		while(v) {
			s+=v;
			v/=k;
		}
		if(s>=n)
			rb=mb; //We want the minimum, all v>mb aren't minimal since v=mb works
		else
			lb=mb+1; //mb doesn't work, so we need at least mb+1
	}
	cout << lb;
}
