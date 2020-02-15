#include<bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, m, a[mxN], b[mxN], ia[mxN], ib[mxN], oa[mxN], ob[mxN], qt, la, ra, lb, rb, xi, yi;
array<int, 5> qs[mxN];
vector<int> ft[mxN+1], ftp[mxN+1];

int qry(int x, int y) {
	int r=0;
	for(; x>0; x-=x&-x)
		for(int j=lower_bound(ftp[x].begin(), ftp[x].end(), y)-ftp[x].begin(); j>0; j-=j&-j)
			r+=ft[x][j];
	return r;
}

void fupd(int i, int j) {
	for(++i; i<=n; i+=i&-i)
		ftp[i].push_back(j);
}

void upd(int i2, int j2, int x) {
	for(int i=i2+1; i<=n; i+=i&-i)
		for(int j=lower_bound(ftp[i].begin(), ftp[i].end(), j2)-ftp[i].begin()+1; j<ft[i].size(); j+=j&-j)
			ft[i][j]+=x;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i], --a[i], ia[a[i]]=i;
	for(int i=0; i<n; ++i)
		cin >> b[i], --b[i], ib[b[i]]=i;
	memcpy(oa, a, sizeof(a));
	memcpy(ob, b, sizeof(b));
	for(int i=0; i<n; ++i)
		fupd(ia[i], ib[i]);
	for(int i=0; i<m; ++i) {
		cin >> qt;
		if(qt==1) {
			cin >> la >> ra >> lb >> rb, --la, --ra, --lb, --rb;
			qs[i]={1, la, ra, lb, rb};
		} else {
			cin >> xi >> yi, --xi, --yi;
			qs[i]={2, xi, yi};
			swap(b[xi], b[yi]);
			tie(xi, yi)=pair<int, int>{b[yi], b[xi]};
			fupd(ia[xi], ib[yi]);
			fupd(ia[yi], ib[xi]);
			swap(ib[xi], ib[yi]);
			
		}
	}
	memcpy(a, oa, sizeof(a));
	memcpy(b, ob, sizeof(b));
	for(int i=0; i<n; ++i) {
		ia[a[i]]=i;
		ib[b[i]]=i;
	}
	for(int i=1; i<=n; ++i) {
		sort(ftp[i].begin(), ftp[i].end());
		ft[i]=vector<int>(ftp[i].size()+1);
	}
	for(int i=0; i<n; ++i)
		upd(ia[i], ib[i], 1);
	for(int i=0; i<m; ++i) {
		array<int, 5> a=qs[i];
		if(a[0]==2) {
			int x=a[1], y=a[2];
			swap(b[x], b[y]);
			tie(x, y)=pair<int, int>{b[y], b[x]};
			upd(ia[x], ib[x], -1);
			upd(ia[y], ib[y], -1);
			upd(ia[x], ib[y], 1);
			upd(ia[y], ib[x], 1);
			swap(ib[x], ib[y]);
		} else
			cout << qry(a[2]+1, a[4]+1)-qry(a[1], a[4]+1)-qry(a[2]+1, a[3])+qry(a[1], a[3]) << "\n";
	}
}
