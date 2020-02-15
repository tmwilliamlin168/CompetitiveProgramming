#include <bits/stdc++.h>
using namespace std;

const int mxN=500;
int n, qa;
array<int, 2> s[mxN];
vector<int> a, b, c;
vector<array<int, 2>> ans;

int qry(vector<int> s, vector<int> t, int v) {
	cout << s.size() << "\n";
	for(int a : s)
		cout << a+1 << " ";
	cout << "\n" << t.size() << "\n";
	for(int a : t)
		cout << a+1 << " ";
	cout << "\n" << v+1 << endl;
	cin >> qa;
	return qa;
}

void fc(int u, int l, int r, int s) {
	if(!s)
		return;
	if(l==r) {
		c.push_back(b[l]);
		return;
	}
	int m=(l+r)/2, qa=qry({0}, vector<int>(b.begin()+l, b.begin()+m+1), u);
	fc(u, l, m, qa);
	fc(u, m+1, r, s-qa);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1; i<n; ++i)
		a.push_back(i);
	for(int i=0; i<n; ++i)
		s[i]={qry({0}, a, i), i};
	++s[0][0];
	sort(s, s+n);
	b={s[0][1]};
	for(int i=1; i<n; ++i) {
		fc(s[i][1], 0, b.size()-1, qry({0}, b, s[i][1]));
		for(int a : c) {
			b.erase(find(b.begin(), b.end(), a));
			ans.push_back({a, s[i][1]});
		}
		b.push_back(s[i][1]);
		c.clear();
	}
	cout << "ANSWER\n";
	for(array<int, 2> a : ans)
		cout << a[0]+1 << " " << a[1]+1 << "\n";
}
