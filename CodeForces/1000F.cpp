/*
	- Mo's algorithm
	- The compiler won't inline upd(), add(), and del() without __attribute__((always_inline)), which reduces the runtime significantly
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, bs, q, a[mxN], ans[mxN], cnt[mxN+1];
vector<int> v;
bool inv[mxN+1];

struct query {
	int l, r, i;
	inline bool operator<(const query &o) const {
		if(l/bs!=o.l/bs)
			return l<o.l;
		return l/bs&1?r<o.r:r>o.r;
	}
} qs[mxN];

__attribute__((always_inline)) void upd(int i) {
	if(cnt[a[i]]==1&&!inv[a[i]]) {
		v.push_back(a[i]);
		inv[a[i]]=1;
	}
}

__attribute__((always_inline)) void add(int i) {
	++cnt[a[i]];
	upd(i);
}

__attribute__((always_inline)) void del(int i) {
	--cnt[a[i]];
	upd(i);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	bs=sqrt(n);
	for(int i=0; i<n; ++i)
		cin >> a[i];
	cin >> q;
	for(int i=0; i<q; ++i)
		cin >> qs[i].l >> qs[i].r, --qs[i].l, --qs[i].r, qs[i].i=i;
	sort(qs, qs+q);
	int l=0, r=-1;
	for(int i=0; i<q; ++i) {
		while(l>qs[i].l)
			add(--l);
		while(r<qs[i].r)
			add(++r);
		while(l<qs[i].l)
			del(l++);
		while(r>qs[i].r)
			del(r--);
		while(!v.empty()&&cnt[v.back()]!=1) {
			inv[v.back()]=0;
			v.pop_back();
		}
		ans[qs[i].i]=v.empty()?0:v.back();
	}
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}
