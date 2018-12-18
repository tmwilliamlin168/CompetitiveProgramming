#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[mxN], t[mxN], sortedbyA[mxN], ans;
priority_queue<int, vector<int>, greater<int>> waiting;

int main() {
	ifstream cin("convention2.in");
	ofstream cout("convention2.out");
	
	//input
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i] >> t[i];
		sortedbyA[i]=i;
	}
	sort(sortedbyA, sortedbyA+n, [&](const int &i, const int &j) {
		return a[i]<a[j];
	});
	//iterate from lowest a
	for(int i=0, time; ; ) {
		if(!waiting.size()) {
			if(i>=n)
				break;
			//update time to when next one arrives
			time=a[sortedbyA[i]];
			//add next cow to arrive
			waiting.push(sortedbyA[i++]);
		}
		int next=waiting.top();
		waiting.pop();
		//update ans according to wait time
		ans=max(time-a[next], ans);
		//update time
		time+=t[next];
		//add the cows that arrived
		while(i<n&&a[sortedbyA[i]]<=time)
			waiting.push(sortedbyA[i++]);
	}
	cout << ans;
}
