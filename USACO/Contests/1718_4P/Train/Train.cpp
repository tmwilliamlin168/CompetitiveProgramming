#include "grader.h"
#include <cstring>
#include <unordered_map>
using namespace std;

const int bs=1000, f=4010, qh=5015, qt=5016, rmf=5017, rms=5018, spi=5019, tr=5020, big=1e9, cs=qh, ce=qh+6;

void helpBessie(int ID) {
	int cc[ce-cs];
	memset(cc, -1, sizeof(cc));
	bool ch[ce-cs]={};
	auto g=[&](int i) {
		if(i<cs||i>=ce)
			return get(i);
		if(cc[i-cs]==-1)
			cc[i-cs]=get(i);
		return cc[i-cs];
	};
	auto s=[&](int i, int x) {
		if(i<cs||i>=ce)
			return set(i, x);
		ch[i-cs]=1;
		cc[i-cs]=x;
	};
	int n=getTrainLength(), k=getWindowLength(), i1=getCurrentCarIndex(), i2=getCurrentPassIndex();
	auto prm=[&]() {
		while(g(qh)<g(qt)&&g(g(qt)-1)>g(rmf))
			s(qt, g(qt)-2);
		s(g(qt), g(rms));
		s(g(qt)+1, g(rmf));
		s(qt, g(qt)+2);
		s(rmf, big);
	};
	auto rn=[&]() {
		while(g(g(qh))<g(tr))
			s(qh, g(qh)+2);
		shoutMinimum(g(g(qh)+1));
		s(tr, g(tr)+1);
	};
	if(!i1)
		s(rmf, big);
	if(ID<g(rmf)) {
		s(rmf, ID);
		s(rms, i1);
	}
	while(g(qh)<g(qt)&&g(g(qh))<=i1-k)
		s(qh, g(qh)+2);
	if(!i2) {
		if(i1==n-1||i1%bs==bs-1||i1%bs==(k-1)%bs) {
			prm();
			if(i1%bs==(k-1)%bs&&i1-k+1>=0)
				s(f+(i1-k+1)/bs, g(g(qh)));
			if(i1==n-1) {
				for(int j=0; j*bs<n; ++j) {
					if(j*bs+k<=n)
						continue;
					while(g(g(qh))<j*bs)
						s(qh, g(qh)+2);
					s(f+j, g(g(qh)));
				}
				s(f+(n-1)/bs+1, n-1);
				s(f+(n-1)/bs+2, n);
				s(qh, 0);
				s(qt, 0);
			}
		}
	} else if(i1>=g(f)) {
		while(i1>=g(f+g(spi)+1)) {
			prm();
			while(g(tr)<min(bs*(g(spi)+1), n-k+1))
				rn();
			s(spi, g(spi)+1);
			s(qh, 0);
			s(qt, 0);
			s(rmf, ID);
			s(rms, i1);
		}
		if(i1<bs*(g(spi)+1)||i1>=bs*g(spi)+k-1)
			prm();
		if(i1==g(tr)+k-1)	
			rn();
	}
	for(int i=cs; i<ce; ++i)
		if(ch[i-cs])
			set(i, cc[i-cs]);
}
