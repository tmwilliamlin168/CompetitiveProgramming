import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "haybales";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), q=in.nextInt();
			int[] a = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			SegTree st = new SegTree(a);
			while(q-->0) {
				String qt=in.next();
				int l=in.nextInt()-1, r=in.nextInt()-1;
				if(qt.charAt(0)=='M')
					out.println(st.qry(l, r, 0));
				else if(qt.charAt(0)=='P')
					st.upd(l, r, in.nextInt());
				else
					out.println(st.qry(l, r, 1));
			}
		}
		
		class SegTree {
			int n, l, r, x;
			long[][] a;
			long[] lz;
			SegTree(int[] b) {
				n=b.length;
				a = new long[2][4*n];
				lz = new long[4*n];
				build(1, 0, n-1, b);
			}
			void cmb(int i) {
				a[0][i]=Math.min(a[0][2*i], a[0][2*i+1]);
				a[1][i]=a[1][2*i]+a[1][2*i+1];
			}
			void build(int i, int l2, int r2, int[] b) {
				if(l2==r2) {
					a[0][i]=a[1][i]=b[l2];
					return;
				}
				int m=(l2+r2)/2;
				build(2*i, l2, m, b);
				build(2*i+1, m+1, r2, b);
				cmb(i);
			}
			void push(int i, int l2, int r2) {
				a[0][i]+=lz[i];
				a[1][i]+=lz[i]*(r2-l2+1);
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
				cmb(i);
			}
			long qry(int l, int r, int x) {
				this.l=l;
				this.r=r;
				this.x=x;
				return qry2(1, 0, n-1);
			}
			long qry2(int i, int l2, int r2) {
				push(i, l2, r2);
				if(l<=l2&&r2<=r)
					return a[x][i];
				int m=(l2+r2)/2;
				if(x==0)
					return Math.min(l<=m?qry2(2*i, l2, m):Long.MAX_VALUE, m<r?qry2(2*i+1, m+1, r2):Long.MAX_VALUE);
				return (l<=m?qry2(2*i, l2, m):0)+(m<r?qry2(2*i+1, m+1, r2):0);
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
