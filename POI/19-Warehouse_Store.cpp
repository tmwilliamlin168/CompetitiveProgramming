/*
	- Process everything in order
	- Always complete orders if possible
	- If a certain order can not be completed and an order with a higher demand was completed, undo that order and complete the new order instead
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2.5e5;
int n, a[mxN], bi;
priority_queue<array<int, 2>> pq;
long long s=0;
vector<int> ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n; ++i) {
		s+=a[i];
		cin >> bi;
		if(s<bi&&!pq.empty()&&pq.top()[0]>bi) {
			s+=pq.top()[0];
			pq.pop();
		}
		if(s>=bi) {
			pq.push({bi, i});
			s-=bi;
		}
	}
	while(!pq.empty()) {
		ans.push_back(pq.top()[1]);
		pq.pop();
	}
	cout << ans.size() << "\n";
	sort(ans.begin(), ans.end());
	for(int b : ans)
		cout << b+1 << " ";
}
