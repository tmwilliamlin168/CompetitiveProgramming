import java.io.*;
import java.util.*;

public class Main {
	static final int M=(int)1e6+3;
	static long[] iv = new long[123457], f1 = new long[123457], f2 = new long[123457], p2 = new long[91];
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t=in.nextInt();
		long[] ans = new long[t];
		iv[1]=1;
		for(int i=2; i<123457; ++i)
			iv[i]=(M-M/i)*iv[M%i]%M;
		f1[0]=f2[0]=1;
		for(int i=1; i<123457; ++i) {
			f1[i]=f1[i-1]*i%M;
			f2[i]=f2[i-1]*iv[i]%M;
		}
		p2[0]=1;
		for(int i=1; i<91; ++i)
			p2[i]=p2[i-1]*2%M;
		List<B>[][] fl = new List[2][2];
		for(int i=0; i<2; ++i)
			for(int j=0; j<2; ++j)
				fl[i][j] = new ArrayList<B>();
		for(int ti=0; ti<t; ++ti) {
			int n=in.nextInt(), c1=in.nextInt(), c2=in.nextInt(), c3=in.nextInt();
			int[] w = new int[3];
			for(int i=0; i<3; ++i)
				w[i]=in.nextInt();
			int m=in.nextInt();
			if(m<1)
				continue;
			if(c1+c2+c3<1) {
				for(int i=0; i<8; ++i) {
					int s=0;
					for(int j=0; j<3; ++j)
						if((i>>j)%2==1)
							s+=w[j];
					if(s<m)
						++ans[ti];
				}
				for(int i=0; i<n-3; ++i)
					ans[ti]=ans[ti]*2%M;
			} else if(c1+c2+c3<2) {
				TreeMap<Integer, Integer> c = new TreeMap<Integer, Integer>();
				c.put(w[0], 1);
				c.put(w[1], c.getOrDefault(w[1], 0)+1);
				c.put(w[2], c.getOrDefault(w[2], 0));
				if(c1>0) {
					c.put(w[2], c.get(w[2])+n-2);
				} else if(c2>0) {
					c.put(w[1], c.get(w[1])+(n-2)/2);
					c.put(w[2], c.get(w[2])+(n-1)/2);
				} else {
					c.put(w[0], c.get(w[0])+(n-1)/3);
					c.put(w[1], c.get(w[1])+(n-2)/3);
					c.put(w[2], c.get(w[2])+n/3);
				}
				if(n==123456&&c3>0&&c.size()>2) {
					fl[c.firstKey()-1][c.higherKey(c.firstKey())-2].add(new B(ti, c.lastKey(), m));
				} else {
					for(int i=-1; c.size()<3; --i)
						c.put(i, 0);
					int pi=0;
					P[] pa = new P[3];
					for(Map.Entry<Integer, Integer> me : c.entrySet())
						pa[pi++] = new P(me.getValue(), me.getKey());
					Arrays.sort(pa);
					long[] d=gc(pa[0].a), e=gc(pa[1].a), f=gc(pa[2].a);
					for(int i=1; i<=pa[2].a; ++i)
						f[i]=(f[i]+f[i-1])%M;
					for(int i=0; i<=pa[0].a&&i*pa[0].b<m; ++i)
						for(int j=0; j<=pa[1].a&&i*pa[0].b+j*pa[1].b<m; ++j)
							ans[ti]=(ans[ti]+d[i]*e[j]*f[Math.min((m-i*pa[0].b-j*pa[1].b-1)/pa[2].b, pa[2].a)])%M;
				}
			} else {
				long[] x = new long[n];
				for(int i=0; i<3; ++i)
					x[i]=w[i];
				for(int i=3; i<n; ++i)
					x[i]=Math.min(x[i-1]*c1+x[i-2]*c2+x[i-3]*c3, m);
				Arrays.sort(x);
				while(--n>=0&&x[n]>=m);
				for(int i=1; i<=n; ++i)
					x[i]+=x[i-1];
				ans[ti]=dfs(x, n, m, new HashMap<Long, Integer>());
			}
		}
		long m1=998244353, m2=1045430273, he=pm(m1, m2-2, m2);
		NTT na = new NTT(1<<18, m1, 3), nb = new NTT(1<<18, m2, 3);
		long[] sc=gc(41152);
		for(int a=0; a<2; ++a) {
			for(int b=0; b<2; ++b) {
				if(fl[a][b].isEmpty())
					continue;
				long[] aa = new long[1<<18], ab = new long[1<<18];
				for(int i=0; i<41153; ++i)
					aa[i*(a+1)]=ab[i*(b+2)]=sc[i];
				long[] ba=Arrays.copyOf(aa, 1<<18), bb=Arrays.copyOf(ab, 1<<18);
				na.mul(aa, ab);
				nb.mul(ba, bb);
				for(int i=0; i<1<<18; ++i) {
					aa[i]=(aa[i]+(ba[i]-aa[i]%m2+m2)*he%m2*m1)%M;
					if(i>0)
						aa[i]=(aa[i-1]+aa[i])%M;
				}
				for(B d : fl[a][b])
					for(int i=0; i<41153&&d.m>i*d.w; ++i)
						ans[d.ti]=(ans[d.ti]+sc[i]*aa[Math.min(d.m-i*d.w-1, (1<<18)-1)])%M;
			}
		}
		for(int i=0; i<t; ++i)
			System.out.println(ans[i]);
	}
	
	static int dfs(long[] w, int i, int m, Map<Long, Integer> dp) {
		if(m<1)
			return 0;
		if(m<=w[0])
			return 1;
		if(m>w[i])
			return (int)p2[i+1];
		int a=dp.getOrDefault(i*(long)1e9+m, 0);
		if(a<1) {
			a=(dfs(w, i-1, m, dp)+dfs(w, i-1, (int)(m-w[i]+w[i-1]), dp))%M;
			dp.put(i*(long)1e9+m, a);
		}
		return a;
	}
	
	static long[] gc(int n) {
		long[] c = new long[n+1];
		for(int i=0; i<=n; ++i)
			c[i]=f1[n]*f2[i]*f2[n-i]%M;
		return c;
	}
	
	static int gcd(int a, int b) {
		while((a%=b)>0&&(b%=a)>0);
		return a^b;
	}
	
	static long pm(long b, long p, long M) {
		long r=1;
		while(p>0) {
			if(p%2==1)
				r=r*b%M;
			b=b*b%M;
			p/=2;
		}
		return r;
	}
	
	static class NTT {
		long M;
		long[] rt;
		NTT(int n, long M, int G) {
			rt = new long[n];
			rt[n/2]=1;
			rt[n/2+1]=pm(G, (M-1)/n, M);
			for(int i=n/2+2; i<n; ++i)
				rt[i]=rt[i-1]*rt[n/2+1]%M;
			for(int i=n/2; --i>=1; )
				rt[i]=rt[2*i];
			this.M=M;
		}
		void ac(long[] a) {
			int n=a.length;
			for(int i=0, j=0; i<n; ++i) {
				if(i>j)
					a[i]^=a[j]^(a[j]=a[i]);
				for(int k=n/2; (j^=k)<k; k/=2);
			}
			for(int st=1; 2*st<=n; st*=2) {
				for(int i=0; i<n; i+=2*st) {
					for(int j=i; j<i+st; ++j) {
						long z=rt[j-i+st]*a[j+st]%M;
						a[j+st]=a[j]-z;
						if(a[j+st]<0)
							a[j+st]+=M;
						a[j]+=z;
						if(a[j]>=M)
							a[j]-=M;
					}
				}
			}
		}
		void mul(long[] a, long[] b) {
			ac(a);
			ac(b);
			long in=pm(a.length, M-2, M);
			for(int i=0; i<a.length; ++i)
				a[i]=a[i]*b[i]%M*in%M;
			for(int i=1; i<a.length-i; ++i)
				a[i]^=a[a.length-i]^(a[a.length-i]=a[i]);
			ac(a);
		}
	}
	
	static class B {
		int ti, w, m;
		B(int ti, int w, int m) {
			this.ti=ti;
			this.w=w;
			this.m=m;
		}
	}
	
	static class P implements Comparable<P> {
		int a, b;
		P(int a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(P o) {
			return a-o.a;
		}
	}
}
