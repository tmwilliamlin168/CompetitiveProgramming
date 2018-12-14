import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "mincross";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] a = new int[n], b = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt()-1;
			for(int i=0; i<n; ++i)
				b[i]=in.nextInt()-1;
			out.println(Math.min(solve(n, a, b), solve(n, b, a)));
		}
		
		long solve(int n, int[] a, int[] b) {
			int[] p1 = new int[n], p2 = new int[n];
			for(int i=0; i<n; ++i)
				p1[a[i]]=i;
			for(int i=0; i<n; ++i)
				p2[i]=p1[b[i]];
			FenwickTree ft = new FenwickTree(n);
			long ans=Long.MAX_VALUE, cur=0;
			for(int i=n-1; i>=0; --i) {
				cur+=ft.sum(p2[i]);
				ft.add(p2[i], 1);
			}
			for(int i=0; i<n; ++i)
				ans=Math.min(cur+=(n-1-2*p2[i]), ans);
			return ans;
		}
		
		class FenwickTree {
			int[] a;
			FenwickTree(int n) {
				a = new int[n+1];
			}
			void add(int i, int x) {
				for(++i; i<a.length; i+=i&-i)
					a[i]+=x;
			}
			int sum(int i) {
				int r=0;
				for(; i>0; i-=i&-i)
					r+=a[i];
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
