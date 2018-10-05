import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "slingshot";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final long INF=(long)1e10;
		
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			Shot[] shots = new Shot[n];
			for(int i=0; i<n; ++i)
				shots[i] = new Shot(in.nextInt(), in.nextInt(), in.nextInt());
			Arrays.sort(shots, new Comparator<Shot>() {
				public int compare(Shot a, Shot b) {
					return Long.compare(a.x, b.x);
				}
			});
			long[] sxs = new long[n];
			for(int i=0; i<n; ++i) {
				sxs[i]=shots[i].x;
				shots[i].cx=i;
			}
			Arrays.sort(shots, new Comparator<Shot>() {
				public int compare(Shot a, Shot b) {
					return Long.compare(a.y, b.y);
				}
			});
			Query[] queries = new Query[m];
			long[] ans = new long[m];
			for(int i=0; i<m; ++i) {
				int a=in.nextInt(), b=in.nextInt();
				ans[i]=Math.abs(a-b);
				queries[i] = new Query(i, a, b);
			}
			Arrays.sort(queries, new Comparator<Query>() {
				public int compare(Query a, Query b) {
					return a.b-b.b;
				}
			});
			FenwickTree ft1 = new FenwickTree(n), ft2 = new FenwickTree(n);
			for(int i1=0, i2=0; i2<m;) {
				if(i1>=n||shots[i1].y>queries[i2].b) {
					int p=Arrays.binarySearch(sxs, queries[i2].a);
					if(p<0)
						p=-p-1;
					ans[queries[i2].i]=Math.min(Math.min(ft1.qry(p)+queries[i2].a, ft2.qry(n-p)-queries[i2].a)+queries[i2].b, ans[queries[i2].i]);
					++i2;
				} else {
					ft1.upd(shots[i1].cx, shots[i1].t-shots[i1].x-shots[i1].y);
					ft2.upd(n-1-shots[i1].cx, shots[i1].t+shots[i1].x-shots[i1].y);
					++i1;
				}
			}
			ft1 = new FenwickTree(n);
			ft2 = new FenwickTree(n);
			for(int i1=n-1, i2=m-1; i2>=0;) {
				if(i1<0||shots[i1].y<queries[i2].b) {
					int p=Arrays.binarySearch(sxs, queries[i2].a);
					if(p<0)
						p=-p-1;
					ans[queries[i2].i]=Math.min(Math.min(ft1.qry(p)+queries[i2].a, ft2.qry(n-p)-queries[i2].a)-queries[i2].b, ans[queries[i2].i]);
					--i2;
				} else {
					ft1.upd(shots[i1].cx, shots[i1].t-shots[i1].x+shots[i1].y);
					ft2.upd(n-1-shots[i1].cx, shots[i1].t+shots[i1].x+shots[i1].y);
					--i1;
				}
			}
			for(int i=0; i<m; ++i)
				out.println(ans[i]);
		}
		
		class Shot {
			long x, y, t;
			int cx;
			Shot(long x, long y, long t) {
				this.x=x;
				this.y=y;
				this.t=t;
			}
		}
		
		class Query {
			int i, a, b;
			Query(int i, int a, int b) {
				this.i=i;
				this.a=a;
				this.b=b;
			}
		}
		
		class FenwickTree {
			long[] a;
			FenwickTree(int n) {
				a = new long[n+1];
				Arrays.fill(a, INF);
			}
			void upd(int i, long x) {
				for(++i; i<a.length; i+=i&-i)
					a[i]=Math.min(x, a[i]);
			}
			long qry(int i) {
				long r=INF;
				for(; i>0; i-=i&-i)
					r=Math.min(a[i], r);
				return r;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String filename) throws Exception {
			br = new BufferedReader(new FileReader(filename));
		}
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
