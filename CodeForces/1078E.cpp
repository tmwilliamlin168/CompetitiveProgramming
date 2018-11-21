#include <bits/stdc++.h>
using namespace std;

int main() {
	auto c=[&](string a, int b=1) {
		while(b--)
			cout << a;
	};
	auto cl=[&](int a, int b) {
		c("l", a);
		c("r10lt", b);
	};
	c("d");
	c("d0usut0dtl", 31);
	c("uuu");
	c("ru0dsdt0ut", 31);
	c("drrr0llld");
	for(int i=0; i<31; ++i) {
		cl(i, i);
		c("u");
		cl(i, i+1);
		c("d010ltutr10ltr010ltut");
		cl(0, 31-i);
		c("l", 31-i);
		c("100ltutll100ltutd10utrr10utl10ltrtu10dtu10dtr10ltdlll");
	}
	c("rrrr");
}
