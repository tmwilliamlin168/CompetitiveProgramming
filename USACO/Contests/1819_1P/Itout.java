import java.io.*;
import java.util.*;

public class Itout {
	static final boolean stdin = false;
	static final String filename = "itout";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			//input
			//add a 0 in front to make things easier
			int n=in.nextInt()+1;
			long k=in.nextLong();
			final int[] a = new int[n+1];
			for(int i=1; i<n; ++i)
				a[i]=in.nextInt();
			//do the normal LIS dp
			PIL[] dp = new PIL[n];
			FenwickTree ft = new FenwickTree(n);
			List<Integer>[] b = new List[n+1];
			for(int i=1; i<=n; ++i)
				b[i] = new ArrayList<Integer>();
			for(int i=n-1; i>=0; --i) {
				dp[i]=ft.qry(a[i]);
				dp[i]=add(new PIL(dp[i].a+1, dp[i].b), new PIL(1, 1));
				ft.upd(a[i], dp[i]);
				//add element to bucket according to length of LIS
				b[dp[i].a].add(i);
			}
			//restore kth largest LIS
			for(int i=1; i<=n; ++i) {
				Collections.sort(b[i], new Comparator<Integer>() {
					public int compare(Integer i, Integer j) {
						return -(a[i]-a[j]);
					}
				});
			}
			boolean[] inlis = new boolean[n];
			for(int i=0; ; ) {
				inlis[a[i]]=true;
				if(dp[i].a==1)
					break;
				//iterate over possible next elements
				for(Integer j : b[dp[i].a-1]) {
					if(j<i)
						continue;
					if(dp[j].b>=k) {
						i=j;
						break;
					} else
						k-=dp[j].b;
				}
			}
			//output the complement
			out.println(n-dp[0].a);
			for(int i=0; i<n; ++i)
				if(!inlis[i])
					out.println(i);
		}
		
		static PIL add(PIL a, PIL b) {
			if(a.a>b.a)
				return new PIL(a.a, a.b);
			if(a.a<b.a)
				return new PIL(b.a, b.b);
			return new PIL(a.a, Math.min(a.b+b.b, (long)1e18));
		}
		
		static class FenwickTree {
			PIL[] a;
			FenwickTree(int n) {
				a = new PIL[n+1];
				for(int i=1; i<=n; ++i)
					a[i] = new PIL(0, 0);
			}
			void upd(int i, PIL x) {
				for(i=a.length-1-i; i<a.length; i+=i&-i)
					a[i]=add(a[i], x);
			}
			PIL qry(int i) {
				PIL r = new PIL(0, 0);
				for(i=a.length-1-i; i>0; i-=i&-i)
					r=add(r, a[i]);
				return r;
			}
		}
		
		static class PIL {
			int a;
			long b;
			PIL(int a, long b) {
				this.a=a;
				this.b=b;
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}