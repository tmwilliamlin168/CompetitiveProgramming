#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6, NS=5500;
int n, k, a[mxN], qu[mxN], qh, qt, i1, i2, b[NS], no;
vector<int> a1, a2;

int get(int index) {
	++no;
	if(index<0||index>=NS) {
		cout << "WA2";
		exit(0);
	}
//	cout << "g " << index << "\n";
	return b[index];
}

void set(int index, int value) {
	++no;
	if(index<0||index>=NS) {
		cout << "WA3";
		exit(0);
	}
//	cout << "s " << index << " " << value << "\n";
	b[index]=value;
}

void shoutMinimum(int output) {
	a2.push_back(output);
}

int getTrainLength() {
	return n;
}

int getWindowLength() {
	return k;
}

int getCurrentCarIndex() {
	return i1;
}

int getCurrentPassIndex() {
	return i2;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(; i1<n; ++i1) {
		cin >> a[i1];
		while(qh<qt&&a[qu[qt-1]]>a[i1])
			--qt;
		qu[qt++]=i1;
		if(qu[qh]<=i1-k)
			++qh;
		if(i1>=k-1)
			a1.push_back(a[qu[qh]]);
		helpBessie(a[i1]);
	}
	i2=1;
	for(i1=0; i1<n; ++i1)
		helpBessie(a[i1]);
	bool ac=a1.size()==a2.size();
	for(int i=0; i<a1.size()&&ac; ++i)
		ac=a1[i]==a2[i];
	for(int i=0; i<a1.size(); ++i)
		cout << a1[i] << " \n"[i==a1.size()-1];
	for(int i=0; i<a2.size(); ++i)
		cout << a2[i] << " \n" [i==a2.size()-1];
	cout << (ac?"AC":"WA1") << " " << (double)no/n;
}
