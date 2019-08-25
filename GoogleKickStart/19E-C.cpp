#include <bits/stdc++.h>
using namespace std;

int t, l, r;
vector<int> v;

int s(int r) {
	return upper_bound(v.begin(), v.end(), r)-v.begin();
}

int solve() {
	cin >> l >> r;
	return (l<=1)+(l<=8&&8<=r)+(l<=4&&4<=r)+s(r)-s(l-1)+s(r/4)-s((l+3)/4-1)+r/2-(l-1)/2-r/4+(l-1)/4;
}

struct segmentedsieve {
	void ac(int n, auto f) {
		int s=1;
		while(s*s<n)
			++s;
		vector<int> c(s+1), v;
		for(int i=2; i<=s; ++i) {
			if(c[i])
				continue;
			f(i);
			v.push_back(i);
			for(int j=i*i; j<=s; j+=i)
				c[j]=1;
		}
		for(int i1=s+1, i2=2*s; i1<=n; i1+=s, i2+=s) {
			c=vector<int>(s);
			for(int p : v)
				for(int j=(i1+p-1)/p; j*p<=i2; ++j)
					c[j*p-i1]=1;
			for(int j=i1; j<=i2; ++j)
				if(!c[j-i1]&&j<=n)
					f(j);
		}
	}
} ss;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ss.ac(1e9, [](const int &i) {
		v.push_back(i);
	});
	v.erase(v.begin());

	cin >> t;
	for(int i=1; i<=t; ++i)
		cout << "Case #" << i << ": " << solve() << "\n";
}
