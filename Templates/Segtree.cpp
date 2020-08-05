struct {
	//CUSTOM
	struct d1 {
		//values for segment
		int len=1;
		ll sum;
		ll mn;
		ll mx;
	};
	struct d2 {
		//values for update
		bool res=0;
		ll add=0;
	};
	d1 d1d1(d1 a, d1 b) {
		//return a+b
		d1 c;
		c.len=a.len+b.len;
		c.sum=a.sum+b.sum;
		c.mn=min(a.mn, b.mn);
		c.mx=max(a.mx, b.mx);
		return c;
	}
	void d1d2(d1& a, d2& b) {
		//a+=b
		if(b.res) {
			a.sum=0;
			a.mn=0;
			a.mx=0;
		}
		a.sum+=a.len*b.add;
		a.mn+=b.add;
		a.mx+=b.add;
	}
	void d2d2(d2& a, d2& b) {
		//a+=b
		if(b.res) {
			a.res=1;
			a.add=0;
		}
		a.add+=b.add;
	}
	//convert to d1
	template<class T> d1 cd1(T& x) {
		d1 a;
		a.sum=x;
		a.mn=x;
		a.mx=x;
		return a;
	}
	//TEMPLATE
	int n;
	vt<d1> st;
	vt<d2> lz;
	template<class T> void bld(vt<T>& a, int i, int l2, int r2) {
		if(l2==r2) {
			st[i]=cd1(a[l2]);
			return;
		}
		int m2=(l2+r2)/2;
		bld(a, 2*i, l2, m2);
		bld(a, 2*i+1, m2+1, r2);
		st[i]=d1d1(st[2*i], st[2*i+1]);
	}
	template<class T> void bld(vt<T> a) {
		n=sz(a);
		vti(st, d1{}, 4*n);
		vti(lz, d2{}, 4*n);
		bld(a, 1, 0, n-1);
	}
	void app(int i, d2 &x) {
		d1d2(st[i], x);
		d2d2(lz[i], x);
	}
	void psh(int i) {
		app(2*i, lz[i]);
		app(2*i+1, lz[i]);
		lz[i]={};
	}
	template<class T> void set(int l1, T& x, int i, int l2, int r2) {
		if(l2==r2) {
			st[i]=cd1(x);
			return;
		}
		int m2=(l2+r2)/2;
		psh(i);
		if(l1<=m2)
			set(l1, x, 2*i, l2, m2);
		else
			set(l1, x, 2*i+1, m2+1, r2);
		st[i]=d1d1(st[2*i], st[2*i+1]);
	}
	template<class T> void set(int l1, T x) {
		set(l1, x, 1, 0, n-1);
	}
	void upd(int l1, int r1, d2& x, int i, int l2, int r2) {
		if(l1<=l2&&r2<=r1) {
			app(i, x);
			return;
		}
		int m2=(l2+r2)/2;
		psh(i);
		if(l1<=m2)
			upd(l1, r1, x, 2*i, l2, m2);
		if(m2<r1)
			upd(l1, r1, x, 2*i+1, m2+1, r2);
		st[i]=d1d1(st[2*i], st[2*i+1]);
	}
	void upd(int l1, int r1, d2 x) {
		upd(l1, r1, x, 1, 0, n-1);
	}
	d1 qry(int l1, int r1, int i, int l2, int r2) {
		if(l1<=l2&&r2<=r1)
			return st[i];
		int m2=(l2+r2)/2;
		psh(i);
		if(l1>m2)
			return qry(l1, r1, 2*i+1, m2+1, r2);
		if(r1<=m2)
			return qry(l1, r1, 2*i, l2, m2);
		return d1d1(qry(l1, r1, 2*i, l2, m2), qry(l1, r1, 2*i+1, m2+1, r2));
	}
	d1 qry(int l1, int r1) {
		return qry(l1, r1, 1, 0, n-1);
	}
} st;
