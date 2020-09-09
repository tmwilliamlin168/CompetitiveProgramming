/*
	- Note that maximum m is changed to 2e6 on yandex
	- For each i, find the minimum r[i] > i such that a[r[i]] < a[i]
	- For each i, find the maximum l[i] < i such that a[l[i]] > a[i]
	- Necessary and sufficient condition for a framed interval [l, r]
		- min(a[l, r]) = a[l], i.e. r[l] > r
		- max(a[l, r]) = a[r], i.e. l[r] < l
		- a[l]-l = a[r]-r
	- Group indexes by a[i]-i
	- Iterate through indexes i in each group from left to right
		- Maintain a stack s such that s[j] < s[j+1] and r[s[j]] > r[s[j+1]]
		- We try to match the topmost element of s with i
			- If r[s[j]] < i, pop s[j]
			- If l[i] > s[j], then all elements in the stack will not work, and we can quit
			- Otherwise, [s[j], i] is a framed interval
		- Lastly, we add i to the stack (while making sure it is monotonic)
	- We now have at most n candidate empodia, just find which ones don't contain other ones
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e6;
int n, a[mxN], r[mxN], l[mxN], b[mxN];
vector<int> v[2*mxN-1], ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		l[i]=i-1;
		while(~l[i]&&a[l[i]]<a[i])
			l[i]=l[l[i]];
		v[a[i]-i+n-1].push_back(i);
	}
	for(int i=n-1; ~i; --i) {
		r[i]=i+1;
		while(r[i]<n&&a[r[i]]>a[i])
			r[i]=r[r[i]];
	}
	for(int k=0; k<2*n-1; ++k) {
		vector<int> w;
		for(int i : v[k]) {
			while(w.size()&&r[w.back()]<i)
				w.pop_back();
			b[i]=w.size()&&l[i]<=w.back()?w.back():i;
			while(w.size()&&r[w.back()]<r[i])
				w.pop_back();
			w.push_back(i);
		}
	}
	for(int i=1; i<n; ++i)
		if(b[i]<i&&(!ans.size()||b[i]>b[ans.back()]))
			ans.push_back(i);
	cout << ans.size() << "\n";
	for(int i : ans)
		cout << b[i]+1 << " " << i+1 << "\n";
}
