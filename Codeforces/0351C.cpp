/*
	- Consider each block of n brackets
	- Blocks can be rearranged so that the depth of the brackets never reaches 2*n
	- Dp with matrix exponentiation
*/

#include <bits/stdc++.h>
using namespace std;

#define uint unsigned int

const int mxN=20, INF=2e9;
int n, m;
uint c[mxN][2], mat1[2*mxN][2*mxN], mat2[2*mxN][2*mxN], vec1[2*mxN], vec2[2*mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> c[i][0];
	for(int i=0; i<n; ++i)
		cin >> c[i][1];
	for(int i=0; i<2*n; ++i) {
		vec1[i]=INF;
		for(int j=0; j<2*n; ++j)
			mat1[i][j]=INF;
	}
	vec1[0]=0;
	for(int i=0; i<1<<n; ++i) {
		int b=0, mb=0;
		uint cc=0;
		for(int j=0; j<n; ++j) {
			cc+=c[j][i>>j&1];
			b+=i>>j&1?-1:1;
			mb=min(b, mb);
		}
		for(int j=-mb; j+b<2*n&&j<2*n; ++j)
			mat1[j+b][j]=min(cc, mat1[j+b][j]);
	}
	while(m) {
		if(m&1) {
			for(int i=0; i<2*n; ++i)
				vec2[i]=INF;
			for(int i=0; i<2*n; ++i)
				for(int j=0; j<2*n; ++j)
					vec2[i]=min(mat1[i][j]+vec1[j], vec2[i]);
			memcpy(vec1, vec2, 4*2*n);
		}
		for(int i=0; i<2*n; ++i) {
			for(int j=0; j<2*n; ++j) {
				mat2[i][j]=INF;
				for(int k=0; k<2*n; ++k)
					mat2[i][j]=min(mat1[i][k]+mat1[k][j], mat2[i][j]);
			}
		}
		for(int i=0; i<2*n; ++i)
			memcpy(mat1[i], mat2[i], 4*2*n);
		m/=2;
	}
	cout << vec1[0];
}
