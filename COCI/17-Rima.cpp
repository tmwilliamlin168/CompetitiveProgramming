/*
	- Reverse the strings and put them in a trie
	- Note that our two words rhyme if they are siblings or one is the parent of the other
	- dp[u] = max length ending at u
*/

#include <bits/stdc++.h>
using namespace std;

const int mxS=3e6+1;
int n, m=1, c[mxS][26], dp[mxS], ans;
string s;
bool a[mxS];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	while(n--) {
		cin >> s;
		int u=0;
		for(int i=s.size()-1; i>=0; u=c[u][s[i]-'a'], --i)
			if(!c[u][s[i]-'a'])
				c[u][s[i]-'a']=m++;
		a[u]=1;
	}
	while(m--) {
		int nc=0;
		for(int i=0; i<26; ++i)
			nc+=a[c[m][i]];
		dp[m]=a[m];
		for(int i=0; i<26; ++i) {
			if(!a[c[m][i]])
				continue;
			ans=max(dp[c[m][i]]+dp[m]+nc-2, ans);
			dp[m]=max(dp[c[m][i]]+a[m], dp[m]);
		}
		dp[m]=max(a[m]+nc, dp[m]+nc-1);
		ans=max(dp[m], ans);
	}
	cout << ans;
}
