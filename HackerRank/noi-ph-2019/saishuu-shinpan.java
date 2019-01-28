import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests>0; --tests)
			new Solver();
		out.close();
	}
	
	static class Solver {
		int[] v;
		Dat[] st;
		
		void bld(int i, int l2, int r2) {
			if(l2==r2) {
				st[i]=new Dat(l2>0?v[l2-1]:0);
				return;
			}
			int m2=(l2+r2)/2;
			bld(2*i, l2, m2);
			bld(2*i+1, m2+1, r2);
			st[i]=Dat.cmb(st[2*i], st[2*i+1]);
		}
		
		void upd(int l1, long x, int i, int l2, int r2) {
			if(l2==r2) {
				st[i]=new Dat(x);
				return;
			}
			int m2=(l2+r2)/2;
			if(l1<=m2)
				upd(l1, x, 2*i, l2, m2);
			else
				upd(l1, x, 2*i+1, m2+1, r2);
			st[i]=Dat.cmb(st[2*i], st[2*i+1]);
		}
		
		Dat qry(int l1, int r1, int i, int l2, int r2) {
			if(l1<=l2&&r2<=r1)
				return st[i];
			int m2=(l2+r2)/2;
			return Dat.cmb(l1<=m2?qry(l1, r1, 2*i, l2, m2):null, m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):null);
		}
		
		Solver() {
			int n=in.nextInt(), q=in.nextInt();
			st = new Dat[4*n];
			v = new int[n];
			for(int i=0; i<n; ++i)
				v[i]=in.nextInt();
			bld(1, 0, n);
			while(q-->0) {
				int qt=in.nextInt();
				if(qt==1) {
					int l1=in.nextInt()-1, l2=in.nextInt()-1, r1=in.nextInt(), r2=in.nextInt();
					l2=Math.min(r2-1, l2);
					r1=Math.max(l1+1, r1);
					long ans=Long.MIN_VALUE;
					if(r1>l1)
						ans=Math.max(qry(r1, r2, 1, 0, n).mxp-qry(l1, Math.min(l2, r1-1), 1, 0, n).mnp+qry(l1, r1-1, 1, 0, n).s, ans);
					if(l2<r2)
						ans=Math.max(qry(Math.max(r1, l2+1), r2, 1, 0, n).mxp-qry(l1, l2, 1, 0, n).mnp+qry(l1, Math.max(r1-1, l2), 1, 0, n).s, ans);
					if(r1+1<=l2)
						ans=Math.max(qry(r1+1, l2, 1, 0, n).mss, ans);
					out.println(ans);
				} else
					upd(in.nextInt(), in.nextInt(), 1, 0, n);
			}
		}
		
		static class Dat {
			long s, mnp, mxp, mxs, mss;
			Dat(long x) {
				s=mnp=mxp=mxs=mss=x;
			}
			static Dat cmb(Dat a, Dat b) {
				if(a==null)
					return b;
				if(b==null)
					return a;
				Dat r = new Dat(a.s+b.s);
				r.mnp=Math.min(a.mnp, a.s+b.mnp);
				r.mxp=Math.max(a.mxp, a.s+b.mxp);
				r.mxs=Math.max(a.mxs+b.s, b.mxs);
				r.mss=Math.max(Math.max(a.mss, b.mss), a.mxs+b.mxp);
				return r;
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
