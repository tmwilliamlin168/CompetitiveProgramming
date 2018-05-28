/*
	- You can prove that the maximum answer is 2, so you just need to check if the answer is 0 or 1
	- b = sum('('->+1, ')'->-1), mb = min(b over all prefixes)
	- If b = mb = 0, the string is already balanced
	- If b = 0 and mb < 0, the answer is 2
	- If b > 0, the answer is 1 if mb == 0
		- If mb < 0 but b>0, the answer can't be 1 because a flip will only increase both or decrease both
	- If b < 0, the answer is 1 if mb == b
		- 1 flip can only increase b and mb by the same amount
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, b=0, mb=0;
	string s;
	cin >> n >> s;
	for(int i=0; i<n; ++i) {
		b+=s[i]=='('?1:-1;
		mb=min(b, mb);
	}
	cout << (b==0&&mb>=0?0:(b>0&&mb>=0||b<0&&mb>=b?1:2));
}
