/*
	- For each i in 1...n, maintain intervals that represent which multisets do not contain i
	- For each query, if l and r are in intervals, then split the intervals at l and r
	- For each interval, add 1
	- For each interval in the complement of the intervals, multiply by 2
	- This can be done with a segment tree
	- Only O(n+q) intervals are created, and after an interval is updated on the segment tree it merges with another interval, so O((n+q)logn) total
*/

import java.io.*;
import java.util.*;

public class MainG {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long M=998244353;
	
	public static void main(String[] args) {
		int n=in.nextInt(), q=in.nextInt();
		SegTree st = new SegTree(n);
		TreeMap<Integer, Integer>[] iss = new TreeMap[n];
		for(int i=0; i<n; ++i) {
			iss[i] = new TreeMap<Integer, Integer>();
			iss[i].put(0, n-1);
			iss[i].put(n, n);
		}
		while(q-->0) {
			int qt=in.nextInt(), l=in.nextInt()-1, r=in.nextInt()-1;
			if(qt==1) {
				int x=in.nextInt()-1;
				TreeMap<Integer, Integer> is = iss[x];
				Map.Entry<Integer, Integer> me1 = is.lowerEntry(l);
				if(me1!=null&&me1.getValue()>=l) {
					is.put(l, me1.getValue());
					is.put(me1.getKey(), l-1);
				}
				me1=is.lowerEntry(r+1);
				if(me1!=null&&me1.getValue()>=r+1) {
					is.put(r+1, me1.getValue());
					is.put(me1.getKey(), r);
				}
				while(l<=r) {
					me1=is.ceilingEntry(l);
					if(me1.getKey()==l) {
						st.upd(l, me1.getValue(), 1, 1);
						is.remove(l);
						l=me1.getValue()+1;
					} else {
						st.upd(l, Math.min(me1.getKey()-1, r), 2, 0);
						l=me1.getKey();
					}
				}
			} else
				out.println(st.qry(l, r));
		}
		out.close();
	}
	
	static class SegTree {
		int n, l, r;
		long d1, d2;
		long[] a;
		long[] lMult, lAdd;
		SegTree(int n) {
			this.n=n;
			a = new long[4*n];
			lMult = new long[4*n];
			Arrays.fill(lMult, 1);
			lAdd = new long[4*n];
		}
		private void push(int i, int l2, int r2) {
			a[i]=(lMult[i]*a[i]+lAdd[i]*(r2-l2+1))%M;
			if(l2<r2) {
				lMult[2*i]=lMult[i]*lMult[2*i]%M;
				lAdd[2*i]=(lMult[i]*lAdd[2*i]+lAdd[i])%M;
				lMult[2*i+1]=lMult[i]*lMult[2*i+1]%M;
				lAdd[2*i+1]=(lMult[i]*lAdd[2*i+1]+lAdd[i])%M;
			}
			lMult[i]=1;
			lAdd[i]=0;
		}
		void upd(int l, int r, long d1, long d2) {
			this.l=l;
			this.r=r;
			this.d1=d1;
			this.d2=d2;
			upd2(1, 0, n-1);
		}
		private void upd2(int i, int l2, int r2) {
			if(l<=l2&&r2<=r) {
				lMult[i]=d1*lMult[i]%M;
				lAdd[i]=(d1*lAdd[i]+d2)%M;
				push(i, l2, r2);
			} else {
				int mid=(l2+r2)/2;
				push(2*i, l2, mid);
				push(2*i+1, mid+1, r2);
				if(l<=mid)
					upd2(2*i, l2, mid);
				if(mid<r)
					upd2(2*i+1, mid+1, r2);
				a[i]=(a[2*i]+a[2*i+1])%M;
			}
		}
		long qry(int l, int r) {
			this.l=l;
			this.r=r;
			return qry2(1, 0, n-1);
		}
		private long qry2(int i, int l2, int r2) {
			push(i, l2, r2);
			if(l<=l2&&r2<=r)
				return a[i];
			int mid=(l2+r2)/2;
			long res=0;
			if(l<=mid)
				res+=qry2(2*i, l2, mid);
			if(mid<r)
				res+=qry2(2*i+1, mid+1, r2);
			return res%M;
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
