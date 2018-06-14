/*
	- 1D version
		- Use a priority queue for keeping track of neighboring ninjas that might have colliding kunais
		- Every time a pair is popped from the priority queue (and the kunais do actually collide)
			- Remove the ninjas
			- Find if a new neighboring pair has been created and add it to the priority queue
	- The 2D version is just a combination of 6 of the 1D verions
	- Now we have the lifetime of each kunai, create a segment representing its path
	- For each row / column, merge all intersections in that row / column
	- Total squares covered is the sum of the lengths of all segments minus the intersections
	- Calculate the intersections with sweeping binary indexed tree
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int n, w, h, nisi, ft[mxN+1];
unordered_map<int, int> smp[6];
bool vp[4][4];
vector<int> xps, niv;
vector<pii> sevs;

struct ninja {
	int x, y, d, lt, si[3];
	bool g;
} ns[mxN];
struct nicmp {
	inline bool operator()(const int &a, const int &b) const {
		return ns[a].x-2*ns[a].y<ns[b].x-2*ns[b].y;
	}
};
set<int, nicmp> nis[3*mxN];

struct event {
	int lt, i1, i2;
	inline bool operator<(const event &o) const {
		return lt>o.lt;
	}
};
priority_queue<event> pq;

inline void ftupd(int i, int x) {
	for(++i; i<=xps.size(); i+=i&-i)
		ft[i]+=x;
}

inline int ftqry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

inline int gsi(int smpi, int i2, int i3) {
	auto it=smp[smpi].find(i2);
	if(it==smp[smpi].end())	
		it=smp[smpi].insert({i2, nisi++}).fi;
	nis[it->se].insert(i3);
	return it->se;
}

inline void aidc(auto it) {
	int i2=*it, i1=*(--it);
	if(vp[ns[i1].d][ns[i2].d])
		pq.push({abs(ns[i1].x-ns[i2].x)+abs(ns[i1].y-ns[i2].y), i1, i2});
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	vp[1][0]=vp[0][2]=vp[0][3]=vp[1][2]=vp[1][3]=vp[2][3]=1;
	cin >> w >> h >> n;
	for(int i=0; i<n; ++i) {
		cin >> ns[i].x >> ns[i].y >> ns[i].d;
		ns[i].si[0]=gsi(ns[i].d>>1, ns[i].x-ns[i].y, i);
		ns[i].si[1]=gsi((ns[i].d&1)+2, ns[i].d&1?ns[i].x:ns[i].y, i);
		ns[i].si[2]=gsi((ns[i].d&1^ns[i].d>>1)+4, ns[i].x+ns[i].y, i);
	}
	for(int i=0; i<nisi; ++i) {
		auto it=nis[i].begin();
		while(++it!=nis[i].end())
			aidc(it);
	}
	while(!pq.empty()) {
		int clt=pq.top().lt;
		vector<int> tp;
		while(!pq.empty()&&pq.top().lt==clt) {
			if(!ns[pq.top().i1].g&&!ns[pq.top().i2].g) {
				tp.push_back(pq.top().i1);
				tp.push_back(pq.top().i2);
			}
			pq.pop();
		}
		for(int tpi : tp) {
			if(ns[tpi].g)
				continue;
			ns[tpi].lt=clt/2;
			for(int i=0; i<3; ++i) {
				auto it=nis[ns[tpi].si[i]].erase(nis[ns[tpi].si[i]].find(tpi));
				if(it!=nis[ns[tpi].si[i]].end()&&it!=nis[ns[tpi].si[i]].begin())
					aidc(it);
			}
			ns[tpi].g=1;
		}
	}
	for(int i=0; i<n; ++i) {
		if(ns[i].d&1) {
			xps.push_back(ns[i].x);
			niv.push_back(i);
		}
		if(ns[i].g)
			continue;
		if(ns[i].d==0)
			ns[i].lt=w-ns[i].x;
		else if(ns[i].d==1)
			ns[i].lt=ns[i].y-1;
		else if(ns[i].d==2)
			ns[i].lt=ns[i].x-1;
		else
			ns[i].lt=h-ns[i].y;
	}
	sort(xps.begin(), xps.end());
	sort(niv.begin(), niv.end(), [&](const int &a, const int &b) {
		int ay=ns[a].y-(ns[a].d==1?ns[a].lt:0), by=ns[b].y-(ns[b].d==1?ns[b].lt:0);
		return ns[a].x==ns[b].x?ay<by:ns[a].x<ns[b].x;
	});
	long long ans=0;
	for(int i1=0, i2=0, ley=0; i1<niv.size(); ++i1) {
		while(ns[niv[i1]].x!=xps[i2]) {
			ley=0;
			++i2;
		}
		int sy=max(ns[niv[i1]].y-(ns[niv[i1]].d==1?ns[niv[i1]].lt:0), ley+1), ey=ns[niv[i1]].y+(ns[niv[i1]].d==3?ns[niv[i1]].lt:0);
		if(sy<=ey) {
			sevs.push_back({sy, i2+1});
			sevs.push_back({ey+1, -i2-1});
			ans+=ey-sy+1;
			ley=ey;
		}
	}
	sort(sevs.begin(), sevs.end());
	niv.clear();
	for(int i=0; i<n; ++i)
		if(ns[i].d&1^1)
			niv.push_back(i);
	sort(niv.begin(), niv.end(), [&](const int &a, const int &b) {
		int ax=ns[a].x-(ns[a].d==2?ns[a].lt:0), bx=ns[b].x-(ns[b].d==2?ns[b].lt:0);
		return ns[a].y==ns[b].y?ax<bx:ns[a].y<ns[b].y;
	});
	for(int i1=0, i2=0, lex; i2<niv.size(); ++i2) {
		while(i1<sevs.size()&&sevs[i1].fi<=ns[niv[i2]].y) {
			ftupd(abs(sevs[i1].se)-1, sevs[i1].se>0?1:-1);
			++i1;
		}
		if(!i2||ns[niv[i2-1]].y!=ns[niv[i2]].y)
			lex=0;
		int sx=max(ns[niv[i2]].x-(ns[niv[i2]].d==2?ns[niv[i2]].lt:0), lex+1), ex=ns[niv[i2]].x+(ns[niv[i2]].d==0?ns[niv[i2]].lt:0);
		if(sx<=ex) {
			ans+=ex-sx+1-(ftqry(upper_bound(xps.begin(), xps.end(), ex)-xps.begin())-ftqry(lower_bound(xps.begin(), xps.end(), sx)-xps.begin()));
			lex=ex;
		}
	}
	cout << ans;
}
