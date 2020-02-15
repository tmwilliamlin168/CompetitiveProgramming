#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, color[mxN];
bool u[mxN];

vector<int> dobatches(vector<array<int, 2>> v) {
	vector<int> ans(v.size()), w(v.size());
	iota(w.begin(), w.end(), 0);
	while(w.size()) {
		memset(u, 0, n);
		vector<int> tp, later;
		for(int wi : w) {
			if(!u[v[wi][0]]&&!u[v[wi][1]]) {
				u[v[wi][0]]=u[v[wi][1]]=1;
				tp.push_back(wi);
			} else
				later.push_back(wi);
		}
		cout << "Q " << tp.size();
		for(int i : tp)
			cout << " " << v[i][0]+1 << " " << v[i][1]+1;
		cout << endl;
		string ta;
		cin >> ta;
		for(int i=0; i<tp.size(); ++i)
			ans[tp[i]]=ta[i]&1;
		w=later;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		vector<array<int, 2>> v1, v2;
		for(int i=0; i+1<n; ++i)
			v1.push_back({i, i+1});
		vector<int> a1=dobatches(v1);
		for(int i=0, ld=-1; i+1<n; ++i) {
			if(a1[i])
				continue;
			if(~ld)
				v2.push_back({ld, i+1});
			ld=i;
		}
		vector<int> a2=dobatches(v2);
		for(int i=0, j=0, ld=-1; i+1<n; ++i) {
			if(a1[i]) {
				color[i+1]=color[i];
				continue;
			}
			if(ld<0)
				color[i+1]=1;
			else if(a2[j++])
				color[i+1]=color[ld];
			else
				color[i+1]=3^color[i]^color[ld];
			ld=i;
		}
		int cnt[3]={};
		for(int i=0; i<n; ++i)
			++cnt[color[i]];
		cout << "A " << cnt[0] << " " << cnt[1] << " " << cnt[2] << "\n";
		for(int i=0; i<3; ++i) {
			for(int j=0; j<n; ++j)
				if(color[j]==i)
					cout << j+1 << " ";
			cout << endl;
		}
	}
}
