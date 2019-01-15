#include <bits/stdc++.h>
using namespace std;

int t, n, m, k;
string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> n >> m >> k >> s;
		if(m==1) {
			bool ok=0;
			for(int i=0; i<n&&!ok; ++i)
				ok=s[i]=='B'&&s[(i+1)%n]=='B';
			ok&=n>1&&n%k==0;
			if(ok) {
				cout << "Yes\n" << n << " ";
				for(int i=0; i<n; ++i)
					cout << i << " \n"[i==n-1];
			} else
				cout << "No\n";
			continue;
		}
		vector<int> b, c;
		for(int i=0; i<n; ++i) {
			if(s[i]=='B'&&b.size()>=2*m)
				s[i]='C';
			if(s[i]=='B')
				b.push_back(i);
			else
				c.push_back(i);
		}
		if(b.size()<2*m||n%k||n<(long long)m*max(k, 2)) {
			cout << "No\n";
			continue;
		}
		cout << "Yes\n";
		int nd=max(k, 2)-2;
		while(b.size()>4) {
			int p1=lower_bound(c.begin(), c.end(), b[b.size()-2])-c.begin(), p2=lower_bound(c.begin(), c.end(), b.back())-c.begin();
			cout << nd+2 << " ";
			if(p1>=nd) {
				for(int i=p1-nd; i<p1; ++i)
					cout << c[i] << " ";
				cout << b[b.size()-2] << " " << b.back() << "\n";
				c.erase(c.begin()+p1-nd, c.begin()+p1);
			} else if(c.size()-p2>=nd) {
				cout << b[b.size()-2] << " " << b.back() << " ";
				for(int i=c.size()-nd; i<c.size(); ++i)
					cout << c[i] << " \n"[i==c.size()-1];
				c.erase(c.end()-nd, c.end());
			} else {
				cout << b[b.size()-2] << " ";
				for(int i=p2-nd; i<p2; ++i)
					cout << c[i] << " ";
				cout << b.back() << "\n";
				c.erase(c.begin()+p2-nd, c.begin()+p2);
			}
			b.pop_back();
			b.pop_back();
		}
		b.insert(b.end(), c.begin(), c.end());
		sort(b.begin(), b.end());
		int ws=b.size()/k/2*k, bc=0;
		for(int i=0; i<ws; ++i)
			bc+=s[b[i]]=='B';
		vector<int> a[2];
		for(int i=0; ; ++i) {
			if(bc==2) {
				for(int j=0; j<b.size(); ++j)
					a[(j>=i&&j<i+ws)^s[b[j]]=='B'].push_back(b[j]);
				break;
			}
			bc+=s[b[i+ws]]=='B';
			bc-=s[b[i]]=='B';
		}
		for(int i=0; i<2; ++i) {
			cout << a[i].size() << " ";
			for(int j=0; j<a[i].size(); ++j)
				cout << a[i][j] << " \n"[j==a[i].size()-1];
		}
	}
}
