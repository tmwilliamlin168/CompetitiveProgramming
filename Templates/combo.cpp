template<int N, int M> struct combo {
	Mnt<M> iv[N+1], f1[N+1], f2[N+1];
	combo() {
		iv[1]=1;
		FOR(i, 2, N+1)
			iv[i]=-M/i*iv[M%i];
		f1[0]=f2[0]=1;
		FOR(i, 1, N+1) {
			f1[i]=f1[i-1]*i;
			f2[i]=f2[i-1]*iv[i];
		}
	}
	Mnt<M> inv2(int n) {
		return iv[n];
	}
	Mnt<M> fact(int n) {
		return f1[n];
	}
	Mnt<M> invfact(int n) {
		return f2[n];
	}
	Mnt<M> nck(int n, int k) {
		return f1[n]*f2[k]*f2[n-k];
	}
	Mnt<M> nck2(int n, int k) {
		umin(k, n-k);
		Mnt<M> r=f2[k];
		FOR(k)
			r*=n-i;
		return r;
	}
	vt<Mnt<M>> gp(int n, Mnt<M> b) {
		vt<Mnt<M>> v(n+1, 1);
		FOR(n)
			v[i+1]=v[i]*b;
		return v;
	}
};
