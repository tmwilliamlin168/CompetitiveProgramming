/*
	- https://boi2013.informatik-olympiade.de/wp-content/uploads/2013/05/vim-spoiler.pdf
	- dp1[i][j]
		- Visited all underlined before i
		- Ending with operation fj
			- Cursor before i before the last operation
		- Cursor on i if j=s[i] and after i otherwise
	- dp2[i][j][k]
		- Visited all underlined before i
		- Operation fj to land on or after i, press h's to go before i, and operation fk to land on or after i
		- Note that the contribution of the h's is only properly added when j=t[i]
			- So dp1 only uses dp2[i][t[i]]
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=7e4;
int n, a1, t[mxN+1], m, dp1[mxN+1][10], dp2[mxN+1][10][10];
string s;
bool u[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s;
	for(int i=0, j=0; i<n; ++i) {
		if(s[i]=='e') {
			a1+=2;
			j=1;
		} else {
			t[m]=s[i]-'a'-(s[i]>'e');
			u[m++]=j;
			j=0;
		}
	}
	t[m]=9;
	memset(dp2[0], 0x3f, sizeof(dp2[0]));
	for(int i=0; i<10; ++i)
		dp1[0][i]=t[0]==i?0:2;
	auto a=[](bool b) {
		return b?9*n:0;
	};
	for(int i=0; i<m; ++i) {
		for(int j=0; j<10; ++j) {
			dp1[i+1][j]=min({dp1[i][j]+a(j==t[i])+a(u[i]), dp1[i][t[i]]+2, dp2[i][t[i]][j]+a(j==t[i]), dp2[i][t[i]][t[i]]+2});
			for(int k=0; k<10; ++k)
				dp2[i+1][j][k]=min({dp1[i][j]+3+a(j==t[i]), dp1[i][t[i]]+5, dp2[i][j][k]+1+a(j==t[i])+a(k==t[i]), dp2[i][j][t[i]]+3+a(j==t[i]), dp2[i][t[i]][k]+3+a(k==t[i]), dp2[i][t[i]][t[i]]+5});
		}
	}
	cout << a1+dp1[m][9]-2;
}
