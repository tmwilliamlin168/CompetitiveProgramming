template<int N> struct combo {
	Mnt iv[N+1], f1[N+1], f2[N+1];
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
	friend Mnt inv2(int n) {
		return iv[n];
	}
	friend Mnt fact(int n) {
		return f1[n];
	}
	friend Mnt invfact(int n) {
		return f2[n];
	}
	friend Mnt nck(int n, int k) {
		return f1[n]*f2[k]*f2[n-k];
	}
	friend Mnt nck2(int n, int k) {
		umin(k, n-k);
		Mnt r=f2[k];
		FOR(k)
			r*=n-i;
		return r;
	}
	friend vt<Mnt> gp(int n, Mnt b) {
		vt<Mnt> v(n+1, 1);
		FOR(n)
			v[i+1]=v[i]*b;
		return v;
	}
};
