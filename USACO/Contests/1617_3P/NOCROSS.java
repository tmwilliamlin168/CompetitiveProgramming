import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "nocross";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] p1 = new int[n], p2 = new int[n];
			for(int i=0; i<n; ++i)
				p1[i]=in.nextInt()-1;
			for(int i=0; i<n; ++i)
				p2[in.nextInt()-1]=i;
			SegTree st = new SegTree(n);
			for(int i=0; i<n; ++i) {
				List<Integer> a = new ArrayList<Integer>();
				for(int j=Math.max(p1[i]-4, 0); j<=Math.min(p1[i]+4, n-1); ++j)
					a.add(p2[j]);
				Collections.sort(a);
				for(int j=a.size()-1; j>=0; --j)
					st.upd(a.get(j), st.qry(0, a.get(j)-1)+1);
			}
			out.println(st.qry(0, n-1));
		}
		
		class SegTree {
			int[] a;
			int n, l1, r1, x;
			SegTree(int n) {
				this.n=n;
				a = new int[4*n];
			}
			void upd(int i, int x) {
				l1=i;
				this.x=x;
				upd2(1, 0, n-1);
			}
			void upd2(int i, int l2, int r2) {
				if(l2==r2) {
					a[i]=x;
					return;
				}
				int m=(l2+r2)/2;
				if(l1<=m)
					upd2(2*i, l2, m);
				else
					upd2(2*i+1, m+1, r2);
				a[i]=Math.max(a[2*i], a[2*i+1]);
			}
			int qry(int l, int r) {
				if(r<l)
					return 0;
				l1=l;
				r1=r;
				return qry2(1, 0, n-1);
			}
			int qry2(int i, int l2, int r2) {
				if(l1<=l2&&r2<=r1)
					return a[i];
				int m=(l2+r2)/2;
				return Math.max(l1<=m?qry2(2*i, l2, m):0, m<r1?qry2(2*i+1, m+1, r2):0);
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
