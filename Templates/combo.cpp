vt<Mnt> iv, f1, f2;
void comboInit(int n) {
	vti(iv, 1, n+1);
	vti(f1, 1, n+1);
	vti(f2, 1, n+1);
	FOR(i, 2, n+1)
		iv[i]=-M/i*iv[M%i];
	FOR(i, 1, n+1) {
		f1[i]=f1[i-1]*i;
		f2[i]=f2[i-1]*iv[i];
	}
}
Mnt nck(int n, int k) {
	return f1[n]*f2[k]*f2[n-k];
}
Mnt nck2(int n, int k) {
	umin(k, n-k);
	Mnt r=f2[k];
	FOR(k)
		r*=n-i;
	return r;
}
vt<Mnt> gp(Mnt b, int n) {
	vt<Mnt> v(n+1, 1);
	FOR(n)
		v[i+1]=v[i]*b;
	return v;
}
