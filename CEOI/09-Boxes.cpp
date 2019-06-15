/*
	- We split the belt into 200 blocks, each with 100 cells
	- Odd blocks will contain the boxes
	- In order to handle insertions, we will allow the blocks of boxes to shift left/right, but they can always have at most 100 boxes
		- In this example, at most 5 boxes per block
		- xxxxx.....xxxxx.....xxxx......
		- Insertion of X in first block
		- xxxXxx....xxxxx.....xxxx......
		- xxxXx....xxxxxx.....xxxx......
		- xxxXx....xxxxx.....xxxxx......
	- We will reset the position of every block of boxes every 100 insertions so that blocks won't shift into each other
		- This is enough since blocks can only get closer by 1 cell per insertion
	- Moves per turn:
		- 100 (resetting one block)
		- 50 (inserting into a block, note that we have to move at most half of the block)
		- 50 (shifting the increase in block size to smaller blocks, note that we have to shift through at most half the blocks)
*/

#include <bits/stdc++.h>
using namespace std;

const int m=100;
int n, s[m], g[m*m];
deque<int> a[m];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<m; ++i) {
		s[i]=(2*i+1)*m;
		for(int j=0; j<m/2; ++j) {
			a[i].push_back(i*m/2+j);
			g[i*m/2+j]=i;
			cout << "I " << s[i]+j+1 << endl;
		}
	}
	auto mo=[](int a, int b) {
		cout << "M " << a+1 << " " << b%n+1 << "\n";
	};
	for(int i=n/4, b; i<n/2; ++i) {
		cin >> b, --b;
		int c=i%m, h=g[b], p=find(a[h].begin(), a[h].end(), b)-a[h].begin();
		if(s[c]>(2*c+1)*m) {
			int j=0;
			for(auto it=a[c].begin(); it!=a[c].end(); ++it, ++j)
				mo(*it, (2*c+1)*m+j);
		} else if(s[c]<(2*c+1)*m) {
			int j=a[c].size()-1;
			for(auto it=a[c].rbegin(); it!=a[c].rend(); ++it, --j)
				mo(*it, (2*c+1)*m+j);
		}
		s[c]=(2*c+1)*m;
		a[h].insert(a[h].begin()+p+1, i);
		g[i]=h;
		if(p<m/2) {
			--s[h];
			int j=0;
			for(auto it=a[h].begin(); *it^i; ++it, ++j)
				mo(*it, s[h]+j);
		} else {
			int j=a[h].size()-1;
			for(auto it=a[h].rbegin(); *it^i; ++it, --j)
				mo(*it, s[h]+j);
		}
		if((i-h)%m<m/2) {
			for(int j=c; j^h; ) {
				int j2=(j+m-1)%m, u=a[j2].back();
				a[j2].pop_back();
				a[j].push_front(u);
				--s[j];
				g[u]=j;
				if(u^i)
					mo(u, s[j]);
				j=j2;
			}
		} else {
			for(int j=c; j^h; ) {
				int j2=(j+1)%m, u=a[j2].front();
				a[j2].pop_front();
				++s[j2];
				a[j].push_back(u);
				g[u]=j;
				if(u^i)
					mo(u, s[j]+a[j].size()-1);
				j=j2;
			}
		}
		cout << "I " << (s[g[i]]+find(a[g[i]].begin(), a[g[i]].end(), i)-a[g[i]].begin())%n+1 << endl;
	}
}
