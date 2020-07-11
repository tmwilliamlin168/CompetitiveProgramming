ll inv(ll a, ll m) {
	return (a%=m)>1?(1-m*inv(m, a))/a+m:1;
}
struct Mnt {
	int x;
	Mnt() {
		x=0;
	}
	Mnt(ll b) {
		if(b<-M||b>=M)
			b%=M;
		if(b<0)
			b+=M;
		x=b;
	}
	friend bool operator==(const Mnt& a, const Mnt& b) {
		return a.x==b.x;
	}
	friend bool operator!=(const Mnt& a, const Mnt& b) {
		return a.x^b.x;
	}
	friend bool operator<(const Mnt& a, const Mnt& b) {
		return a.x<b.x;
	}
	friend void read(Mnt& a) {
		ll x;
		read(x);
		a=Mnt(x);
	}
	friend string to_string(Mnt a) {
		return to_string(a.x);
	}
	Mnt& operator+=(const Mnt& a) {
		if((x+=a.x)>=M)
			x-=M;
		return *this;
	}
	Mnt& operator-=(const Mnt& a) {
		if((x-=a.x)<0)
			x+=M;
		return *this;
	}
	Mnt& operator*=(const Mnt& a) {
		x=(ll)x*a.x%M;
		return *this;
	}
	Mnt& operator/=(const Mnt& a) {
		return (*this)*=inv(a.x, M);
	}
	friend Mnt pm(Mnt a, ll p) {
		Mnt r=1;
		for (; p; p/=2, a*=a)
			if(p&1)
				r*=a;
		return r;
	}
	Mnt operator-() const {
		return Mnt(-x);
	}
	Mnt& operator++() {
		return *this+=1;
	}
	Mnt& operator--() {
		return *this-=1;
	}
	friend Mnt operator+(Mnt a, const Mnt& b) {
		return a+=b;
	}
	friend Mnt operator-(Mnt a, const Mnt& b) {
		return a-=b;
	}
	friend Mnt operator*(Mnt a, const Mnt& b) {
		return a*=b;
	}
	friend Mnt operator/(Mnt a, const Mnt& b) {
		return a/=b;
	}
};
