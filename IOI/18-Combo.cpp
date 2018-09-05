#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

string guess_sequence(int n) {
	string a="ABXY", b="AB", d, s;
	if(!press("AB"))
		b="XY";
	char fc=b[0];
	if(!press(b.substr(0, 1)))
		fc=b[1];
	for(char c : a)
		if(c!=fc)
			d+=c;
	s+=fc;
	if(n<=1)
		return s;
	while(s.size()<n-1)
		s+=d[press(s+d[1]+s+d[2]+d[0]+s+d[2]+d[1]+s+d[2]+d[2])-s.size()];
	if(press(s+d[0]+s+d[1])>s.size()) {
		if(press(s+d[0])>s.size())
			return s+d[0];
		return s+d[1];
	}
	return s+d[2];
}
