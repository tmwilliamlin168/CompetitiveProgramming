#include <bits/stdc++.h>
using namespace std;

class PairsOfHouses {
public:
	vector<int> design(int p) {
		int r=-1, c;
		for(int i=1; i<=25&&r<0; ++i) {
			for(int j=1; j<=25&&r<0; ++j) {
				int a=j*i*(i-1)/2;
				if(a+i*(j-1)<=p&&p<=a+i*j*(j-1)/2) {
					r=i;
					c=j;
				}
			}
		}
		vector<vector<int>> v(r, vector<int>(c, 1));
		for(int i=0; i<r; ++i)
			for(int j=0; j<c; ++j)
				v[i][j]+=3000*i*(i-1)/2;
		int a=c*r*(r-1)/2+r*(c-1);
		for(int i=0; i<r; ++i) {
			for(int j1=c-1; j1>1; --j1) {
				if(a+j1-1<=p) {
					v[i][j1]+=j1*(j1-1)/2;
					a+=j1-1;
				} else if(a<=p) {
					for(int j=j1; ~j; --j)
						v[i][j]+=j1*(j1-1)/2;
					for(int j2=j1-2; a<p; --j2, ++a)
						for(int j=j2; ~j; --j)
							++v[i][j];
					break;
				}
			}
		}
		vector<int> ans={r, c};
		for(int i=0; i<r; ++i)
			for(int j=0; j<c; ++j)
				ans.push_back(v[i][j]);
		return ans;
	}
};
