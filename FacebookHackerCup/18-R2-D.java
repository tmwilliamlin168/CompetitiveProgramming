import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static long M=(long)1e9+7;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), s=in.nextInt(), m=in.nextInt(), k=in.nextInt();
			Pair[] ps = new Pair[n];
			for(int i1=0, i2=0; i1<k; ++i1) {
				int li=in.nextInt();
				long ai=in.nextInt(), xi=in.nextInt(), yi=in.nextInt(), zi=in.nextInt();
				for(int j=0; j<li; ++j) {
					ps[i2++] = new Pair(ai, 0);
					ai=(xi*ai+yi)%zi+1;
				}
			}
			for(int i1=0, i2=0; i1<k; ++i1) {
				int li=in.nextInt();
				long ai=in.nextInt(), xi=in.nextInt(), yi=in.nextInt(), zi=in.nextInt();
				for(int j=0; j<li; ++j) {
					ps[i2++].b=ai;
					ai=(xi*ai+yi)%zi+1;
				}
			}
			Arrays.sort(ps);
			int[] prv = new int[n];
			for(int i=0; i<n; ++i) {
				prv[i]=i-1;
				while(prv[i]>=0&&ps[prv[i]].b<ps[i].b)
					prv[i]=prv[prv[i]];
			}
			SegTree st = new SegTree(n);
			long dp=0;
			for(int i1=0, i2=0; i1<n; ++i1) {
				st.add(i1, i1, dp);
				st.add(prv[i1]+1, i1, ps[i1].b);
				for(int j=i1-1; j>=0&&ps[j].b<ps[i1].b; j=prv[j])
					st.add(prv[j]+1, j, -ps[j].b);
				while(ps[i2].a+2*m<ps[i1].a)
					++i2;
				dp=st.get(i2, i1)+s;
			}
			System.out.println("Case #"+ti+": "+dp);
		}
		out.close();
	}
	
	static class Pair implements Comparable<Pair> {
		long a, b;
		Pair(long a, long b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return Long.compare(a, o.a);
		}
	}
	
	static class SegTree {
		int n, l1, r1;
		long v;
		long[] a, lazy;
		SegTree(int n) {
			this.n=n;
			a = new long[4*n];
			lazy = new long[4*n];
		}
		void build(long[] b) {
			build2(1, 0, n-1, b);
		}
		private void build2(int i, int l2, int r2, long[] b) {
			if(l2<r2) {
				int mid=(l2+r2)/2;
				build2(2*i, l2, mid, b);
				build2(2*i+1, mid+1, r2, b);
				a[i]=Math.min(a[2*i], a[2*i+1]);
			} else
				a[i]=b[l2];
		}
		void add(int l, int r, long x) {
			l1=l;
			r1=r;
			v=x;
			add2(1, 0, n-1);
		}
		private void add2(int i, int l2, int r2) {
			if(l1<=l2&&r2<=r1) {
				a[i]+=v;
				if(l2<r2) {
					lazy[2*i]+=v;
					lazy[2*i+1]+=v;
				}
			} else {
				int mid=(l2+r2)/2;
				push(i*2, l2, mid);
				push(i*2+1, mid+1, r2);
				if(l1<=mid)
					add2(i*2, l2, mid);
				if(mid<r1)
					add2(i*2+1, mid+1, r2);
				a[i]=Math.min(a[i*2], a[i*2+1]);
			}
		}
		void push(int i, int l, int r) {
			a[i]+=lazy[i];
			if(l<r) {
				lazy[2*i]+=lazy[i];
				lazy[2*i+1]+=lazy[i];
			}
			lazy[i]=0;
		}
		long get(int l, int r) {
			l1=l;
			r1=r;
			return get2(1, 0, n-1);
		}
		private long get2(int i, int l2, int r2) {
			push(i, l2, r2);
			if(l1<=l2&&r2<=r1)
				return a[i];
			else {
				int mid=(l2+r2)/2;
				long res=Long.MAX_VALUE;
				if(l1<=mid)
					res = Math.min(get2(2*i, l2, mid), res);
				if(mid<r1)
					res = Math.min(get2(2*i+1, mid+1, r2), res);
				return res;
			}
		}
	}
	
	static class Reader {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		String next() {
			while(st==null||!st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}
