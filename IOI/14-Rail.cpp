/*
	- Query all distances from station 0, the station with minimum distance must be the next D station
	- Process all stations in increasing order by distance from station 0
		- Maintain leftmost C station and rightmost D station
		- Query the new station with the leftmost and rightmost stations
		- We can figure out the station type of the new station by doing some simple case analysis
*/

#include "rail.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=5e3;
array<int, 2> a[mxN];
map<int, int> mp;

void findLocation(int n, int f, int *p, int *s) {
	p[0]=f;
	s[0]=1;
	mp[f]=0;
	for(int i=1; i<n; ++i)
		a[i]={getDistance(0, i), i};
	sort(a, a+n);
	int l=0, r=a[1][1];
	p[r]=f+a[1][0];
	s[r]=2;
	mp[p[r]]=r;
	for(int i=2; i<n; ++i) {
		int dl=getDistance(l, a[i][1]), dr=getDistance(r, a[i][1]), m=(p[l]+dl+p[r]-dr)/2, t=mp.find(m)==mp.end()?(m>f?1:2):s[mp[m]];
		if(t^2) {
			p[a[i][1]]=p[l]+dl;
			s[a[i][1]]=2;
			if(p[a[i][1]]>p[r])
				r=a[i][1];
		} else {
			p[a[i][1]]=p[r]-dr;
			s[a[i][1]]=1;
			if(p[a[i][1]]<p[l])
				l=a[i][1];
		}
		mp[p[a[i][1]]]=a[i][1];
	}
}
