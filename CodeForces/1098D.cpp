#include <bits/stdc++.h>
using namespace std;

#define ll long long

int q, x, f;
char qt;
ll ss[30];
priority_queue<int, vector<int>, greater<int>> p1[30], p2[30];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> q;
	while(q--) {
		cin >> qt >> x;
		int k=31-__builtin_clz(x), ans=0;
		if(qt=='+') {
			ss[k]+=x;
			p1[k].push(x);
			++f;
		} else {
			ss[k]-=x;
			p2[k].push(x);
			--f;
		}
		ll ps=0;
		for(int i=0; i<30; ps+=ss[i++]) {
			while(p1[i].size()&&p2[i].size()&&p1[i].top()==p2[i].top()) {
				p1[i].pop();
				p2[i].pop();
			}
			if(p1[i].size())
				ans+=p1[i].top()>2*ps;
		}
		cout << f-ans << "\n";
	}
}
