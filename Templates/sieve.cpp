template<int N> struct sieve {
	int lp[N+1];
	vt<int> p;
	sieve() {
		FOR(i, 2, N+1) {
			if(!lp[i]) {
				lp[i]=i;
				p.pb(i);
			}
			for(int j=0; j<sz(p)&&(ll)i*p[j]<=N&&p[j]<=lp[i]; ++j)
				lp[i*p[j]]=p[j];
		}
	}
};
