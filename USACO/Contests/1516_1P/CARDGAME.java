import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "cardgame";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), ans=-n;
			List<Integer> bc = new ArrayList<Integer>(), ec = new ArrayList<Integer>();
			boolean[] hse = new boolean[2*n];
			for(int i=0; i<n; ++i) {
				ec.add(in.nextInt()-1);
				hse[ec.get(i)]=true;
			}
			for(int i=2*n-1; i>=0; --i)
				if(!hse[i])
					bc.add(i);
			SegTree st1 = new SegTree(2*n), st2 = new SegTree(2*n);
			for(int i=0; i<2*n; ++i)
				st1.upd(0, i, hse[i]?-1:1);
			ans=Math.max(st1.qry(0, 2*n-1), ans);
			for(int i=n-1; i>=0; --i) {
				st1.upd(0, bc.get(i), -1);
				st1.upd(0, ec.get(i), 1);
				st2.upd(bc.get(i), 2*n-1, 1);
				st2.upd(ec.get(i), 2*n-1, -1);
				ans=Math.max(st1.qry(0, 2*n-1)+st2.qry(0, 2*n-1), ans);
			}
			out.println(n+ans);
		}
		
		class SegTree {
			int n, l, r, x;
			int[] a, lz;
			SegTree(int n) {
				this.n=n;
				a = new int[4*n];
				lz = new int[4*n];
			}
			void push(int i, int l2, int r2) {
				a[i]+=lz[i];
				if(l2<r2) {
					lz[2*i]+=lz[i];
					lz[2*i+1]+=lz[i];
				}
				lz[i]=0;
			}
			void upd(int l, int r, int x) {
				this.l=l;
				this.r=r;
				this.x=x;
				upd2(1, 0, n-1);
			}
			void upd2(int i, int l2, int r2) {
				if(l<=l2&&r2<=r) {
					lz[i]+=x;
					push(i, l2, r2);
					return;
				}
				int m=(l2+r2)/2;
				push(2*i, l2, m);
				push(2*i+1, m+1, r2);
				if(l<=m)
					upd2(2*i, l2, m);
				if(m<r)
					upd2(2*i+1, m+1, r2);
				a[i]=Math.min(a[2*i], a[2*i+1]);
			}
			int qry(int l, int r) {
				this.l=l;
				this.r=r;
				return qry2(1, 0, n-1);
			}
			int qry2(int i, int l2, int r2) {
				push(i, l2, r2);
				if(l<=l2&&r2<=r)
					return a[i];
				int m=(l2+r2)/2;
				return Math.min(l<=m?qry2(2*i, l2, m):Integer.MAX_VALUE, m<r?qry2(2*i+1, m+1, r2):Integer.MAX_VALUE);
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
