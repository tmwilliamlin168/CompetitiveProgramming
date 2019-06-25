/*
	- Note that problem statement is wrong, tests actually give n <= 2e5
	- Find the points with the smallest and greatest angles, break ties by choosing the ones with smaller coordinates
	- Traverse the lower part of the polygon while maintaining a stack of candidate answers
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, l, r;
long long x[mxN+1], y[mxN+1];
vector<int> v, s;
bool b[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	//positive if a->b->c turns left, negative if it turns right, and 0 if they are collinear
	auto cp=[](int a, int b, int c) {
		return (y[c]-y[a])*(x[b]-x[a])-(y[b]-y[a])*(x[c]-x[a]);
	};
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> y[i];
		if(!i||cp(n, l, i)>0||!cp(n, l, i)&&x[i]<x[l])
			l=i;
		if(!i||cp(n, r, i)<0||!cp(n, r, i)&&x[i]<x[r])
			r=i;
	}
	int ic=cp((l+n-1)%n, l, (l+1)%n)>0?1:n-1;
	for(; l^r; l=(l+ic)%n)
		v.push_back(l);
	v.push_back(r);
	s={0, 1};
	for(int i=2; i<v.size(); ++i) {
		//update stuff when we find a new side which goes to the left
		auto ul=[&]() {
			//while one of s.back() and i hides the other and it is actually s.back() which is hidden
			//note <= here so we can pop off v[i-1]
			while(cp(n, v[s.back()], v[i])>=0&&cp(v[i-1], v[i], v[s.back()])<=0)
				s.pop_back();
			//j set to the right side that we need to escape, c set to if right side actually overlaps with the left
			//while i is not to the right of s.back() or i is hidden by segment j
			for(int j=i, c=cp(n, v[s.back()], v[i])<0; cp(n, v[s.back()], v[i])>=0||!c; ++i) {
				//if this is the first side, c will be one iff the new edge goes right and is not hidden by segment j
				//else if we start not to the right of j but end up to the right of j and j does not hide i+1
				if(i^j?cp(n, v[j], v[i])>=0&&cp(n, v[j], v[i+1])<0&&cp(v[i], v[i+1], v[j])>0:cp(n, v[i], v[i+1])<0&&cp(v[i-1], v[i], v[i+1])>0)
					++c;
				//if we start to the right of j but end up not to the right of j and j does not hide i+1
				if(cp(n, v[j], v[i])<0&&cp(n, v[j], v[i+1])>=0&&cp(v[i], v[i+1], v[j])<0)
					--c;
			}
		};
		//both endpoints have the same angle and the new point hides the old point
		if(!cp(n, v[i-1], v[i])&&(cp(n, v[i-2], v[i-1])<0)==(cp(v[i-2], v[i-1], v[i])<0))
			s.pop_back();
		//side not going left and will be hidden by a side from the right
		else if(cp(n, v[i-1], v[i])<=0&&cp(n, v[i-2], v[i-1])>0&&cp(v[i-2], v[i-1], v[i])<0) {
			//while hidden
			while(cp(n, v[s.back()], v[i])<=0)
				++i;
			s.pop_back();
			ul();
		}
		//side going left and won't be hidden
		else if(cp(n, v[i-1], v[i])>0&&(cp(n, v[i-2], v[i-1])>=0||cp(v[i-2], v[i-1], v[i])<0))
			ul();
		//side not going right and will be hidden by a side from the left
		else if(cp(n, v[i-1], v[i])>=0)
			//while hidden
			while(cp(n, v[s.back()], v[i])>=0)
				++i;
		s.push_back(i);
	}
	cout << s.size() << "\n";
	for(int a : s)
		b[v[a]]=1;
	for(int i=0; i<n; ++i)
		if(b[i])
			cout << i+1 << " ";
}
