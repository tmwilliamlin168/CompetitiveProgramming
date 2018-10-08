#include <bits/stdc++.h>
using namespace std;

const int mxN=600;
int n, qa, c[mxN];
bool vis[mxN];
vector<int> adj[mxN], pt;

int qry(vector<int> &s) {
	if(!s.size())
		return 0;
	cout << "? " << s.size() << "\n";
	for(int si : s)
		cout << si+1 << " ";
	cout << endl;
	cin >> qa;
	return qa;
}

void dfs1(int u) {
	vis[u]=1;
	while(1) {
		vector<int> s;
		for(int i=0; i<n; ++i)
			if(!vis[i])
				s.push_back(i);
		int a=qry(s);
		s.push_back(u);
		int b=qry(s);
		s.pop_back();
		if(a==b)
			break;
		int lb=0, rb=s.size()-1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			vector<int> t;
			for(int i=0; i<=mb; ++i)
				t.push_back(s[i]);
			a=qry(t);
			t.push_back(u);
			b=qry(t);
			t.pop_back();
			if(a<b)
				rb=mb;
			else
				lb=mb+1;
		}
		adj[u].push_back(s[lb]);
		adj[s[lb]].push_back(u);
		c[s[lb]]=c[u]^1;
		dfs1(s[lb]);
	}
}

bool dfs2(int u, int t) {
	vis[u]=1;
	pt.push_back(u);
	if(u==t)
		return 1;
	for(int v : adj[u])
		if(!vis[v]&&dfs2(v, t))
			return 1;
	pt.pop_back();
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	dfs1(0);
	vector<int> s1, s2;
	for(int i=0; i<n; ++i) {
		if(c[i])
			s1.push_back(i);
		else
			s2.push_back(i);
	}
	if(!qry(s1)&&!qry(s2)) {
		cout << "Y " << s1.size() << "\n";
		for(int si : s1)
			cout << si+1 << " ";
		return 0;
	}
	if(qry(s2))
		swap(s1, s2);
	int b=qry(s1);
	for(int si : s1) {
		vector<int> t;
		for(int si2 : s1)
			if(si2!=si)
				t.push_back(si2);
		int a=qry(t);
		if(a==b)
			continue;
		int lb=0, rb=t.size()-1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			vector<int> t2;
			for(int i=0; i<=mb; ++i)
				t2.push_back(t[i]);
			a=qry(t2);
			t2.push_back(si);
			b=qry(t2);
			t2.pop_back();
			if(a<b)
				rb=mb;
			else
				lb=mb+1;
		}
		memset(vis, 0, sizeof(vis));
		dfs2(si, t[lb]);
		cout << "N " << pt.size() << "\n";
		for(int pi : pt)
			cout << pi+1 << " ";
		break;
	}
}
