import java.io.*;
import java.util.*;

public class D {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long INF=(long)9e9;

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] p=inp(n), h=inp(n);
			char[] o=in.next().toCharArray();
			int mc=0, mr=0;
			List<Integer> hc = new ArrayList<Integer>();
			A[] a = new A[n];
			for(int i=0; i<n; ++i) {
				if(o[i]=='C')
					mc=Math.max(h[i], mc);
				else
					mr=Math.max(h[i], mr);
				hc.add(h[i]);
				a[i] = new A(p[i], h[i], o[i]);
			}
			if(mr<=mc) {
				out.println(-1);
				return;
			}
			Collections.sort(hc);
			int hcs=0;
			for(int i=0; i<hc.size(); ++i)
				if(i<1||hc.get(i)!=hc.get(i-1))
					hc.set(hcs++, hc.get(i));
			while(hc.size()>hcs)
				hc.remove(hc.size()-1);
			for(int i=0; i<n; ++i)
				a[i].h=Collections.binarySearch(hc, a[i].h);
			Arrays.sort(a);
			int lcp=0;
			for(int i=0; i<n; ++i)
				if(a[i].o=='C')
					lcp=a[i].p;
			SegTree st = new SegTree(hcs);
			st.upd(0, 0, 0, 0, false);
			long ans=(long)2e9;
			for(int i=0, lp=0; i<n; lp=a[i].p, ++i) {
				st.upd(0, hcs-1, -1, a[i].p-lp, false);
				if(a[i].o=='C') {
					st.upd(a[i].h, a[i].h, st.qry(0, a[i].h, 0), 0, false);
					if(a[i].h>0)
						st.upd(0, a[i].h-1, INF, 0, false);
				} else if(a[i].h>0)
					st.upd(0, a[i].h-1, -1, 0, true);
				if(a[i].p>=lcp)
					ans=Math.min(st.qry(0, hcs-1, 1)+a[i].p, ans);
				st.upd(0, 0, Math.min(st.qry(0, 0, 0), st.qry(0, hcs-1, 2)), 0, false);
			}
			out.println(ans);
		}
		
		int[] inp(int n) {
			int[] e = new int[n];
			e[0]=in.nextInt();
			e[1]=in.nextInt();
			long a=in.nextInt(), b=in.nextInt(), c=in.nextInt(), d=in.nextInt();
			for(int i=2; i<n; ++i)
				e[i]=(int)((a*e[i-2]+b*e[i-1]+c)%d+1);
			return e;
		}
		
		class A implements Comparable<A> {
			int p, h;
			char o;
			A(int p, int h, char o) {
				this.p=p;
				this.h=h;
				this.o=o;
			}
			public int compareTo(A o) {
				return p-o.p;
			}
		}
		
		class SegTree {
			static final int STS=1<<21;
			int n;
			long[] stA = new long[STS], stB = new long[STS], lzA = new long[STS], lzB = new long[STS];
			long[][] stAB = new long[3][STS];
			boolean[] lzB2 = new boolean[STS];
			SegTree(int n) {
				this.n=n;
				Arrays.fill(stA, INF);
				Arrays.fill(stB, INF);
				for(int i=0; i<3; ++i)
					Arrays.fill(stAB[i], INF);
				Arrays.fill(lzA, INF);
				Arrays.fill(lzB, INF);
			}
			void app(int i, long a, long b, boolean b2) {
				if(b2) {
					stB[i]=0;
					for(int j=0; j<3; ++j)
						stAB[j][i]=stA[i];
				}
				stB[i]+=b;
				for(int j=0; j<3; ++j)
					stAB[j][i]+=b*j;
				if(a!=-1) {
					stA[i]=a;
					for(int j=0; j<3; ++j)
						stAB[j][i]=a+stB[i]*j;
				}
				if(a!=-1)
					lzA[i]=a;
				if(b2) {
					lzB2[i]=true;
					lzB[i]=0;
				}
				lzB[i]+=b;
			}
			void psh(int i) {
				app(2*i, lzA[i], lzB[i], lzB2[i]);
				app(2*i+1, lzA[i], lzB[i], lzB2[i]);
				lzA[i]=-1;
				lzB[i]=0;
				lzB2[i]=false;
			}
			void upd(int l1, int r1, long a, long b, boolean b2) {
				upd2(l1, r1, a, b, b2, 1, 0, n-1);
			}
			void upd2(int l1, int r1, long a, long b, boolean b2, int i, int l2, int r2) {
				if(l1<=l2&&r2<=r1) {
					app(i, a, b, b2);
					return;
				}
				int m2=(l2+r2)/2;
				psh(i);
				if(l1<=m2)
					upd2(l1, r1, a, b, b2, 2*i, l2, m2);
				if(m2<r1)
					upd2(l1, r1, a, b, b2, 2*i+1, m2+1, r2);
				stA[i]=Math.min(stA[2*i], stA[2*i+1]);
				stB[i]=Math.min(stB[2*i], stB[2*i+1]);
				for(int j=0; j<3; ++j)
					stAB[j][i]=Math.min(stAB[j][2*i], stAB[j][2*i+1]);
			}
			long qry(int l1, int r1, int k) {
				return qry2(l1, r1, k, 1, 0, n-1);
			}
			long qry2(int l1, int r1, int k, int i, int l2, int r2) {
				if(l1<=l2&&r2<=r1)
					return stAB[k][i];
				int m2=(l2+r2)/2;
				psh(i);
				return Math.min(l1<=m2?qry2(l1, r1, k, 2*i, l2, m2):INF, m2<r1?qry2(l1, r1, k, 2*i+1, m2+1, r2):INF);
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
