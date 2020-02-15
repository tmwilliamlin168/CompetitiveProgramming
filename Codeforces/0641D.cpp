/*
	- p(max(a, b)<=x) + p(min(a, b)<=x) = p(a<=x) + p(b<=x)
	- p(a<=x)*p(b<=x) = p(max(a, b)<=x)
	- Solve quadratic to find probabilities
		- You can prove that if there is a solution (as given guaranteed by the problem) then you can just assign the smaller roots to a and the bigger roots to b
		- Calculations can be close to 0 and there are precision errors so use sqrt(max(x, 0)) instead of sqrt(x)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n;
double smx[mxN+1], smn[mxN+1], s1, pa[mxN+1], pb[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> smx[i+1], smx[i+1]+=smx[i];
	cout << fixed << setprecision(9);
	for(int i=0; i<n; ++i) {
		cin >> smn[i+1], smn[i+1]+=smn[i];
		s1=smx[i+1]+smn[i+1];
		pa[i+1]=(s1-sqrt(max(s1*s1-4*smx[i+1], 0.0)))/2;
		pb[i+1]=(s1+sqrt(max(s1*s1-4*smx[i+1], 0.0)))/2;
		cout << pa[i+1]-pa[i] << " ";
	}
	cout << "\n";
	for(int i=0; i<n; ++i)
		cout << pb[i+1]-pb[i] << " ";
}
