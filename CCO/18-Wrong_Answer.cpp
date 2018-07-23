#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cout << "100\n";
	for(int i=0; i<99; ++i)
		cout << "1 ";
	cout << "\n";
	for(int i=98; i>0; --i) {
		cout << (i&1?100:1);
		if(i>1)
			cout << " 100";
		for(int j=0; j<i-2; ++j)
			cout << " 1";
		cout << "\n";
	}
}
