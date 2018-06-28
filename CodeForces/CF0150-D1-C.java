/*
	- Each ticket between consecutive stops has a expected profit associated with it if it is not sold
	- We want tickets for consecutive stops, which is a subarray
	- The subarray with the best expected profit for each person can be found with a segment tree
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt(), c=in.nextInt();
		long[] x = new long[n];
		for(int i=0; i<n; ++i)
			x[i]=in.nextInt();
		for(int i=0; i<n-1; ++i)
			x[i]=(x[i+1]-x[i])*50;
		for(int i=0; i<n-1; ++i)
			x[i]-=c*in.nextInt();
		long ans=0;
		Node rt = new Node(0, n-2, x);
		for(int i=0; i<m; ++i)
			ans+=rt.qry(in.nextInt()-1, in.nextInt()-2).mx;
		out.println(ans/100.0);
		out.close();
	}
	
	static class Node {
		int l, r;
		Node lc, rc;
		long sum, mxL, mxR, mx;
		Node() {}
		Node(int l2, int r2, long[] b) {
			l=l2;
			r=r2;
			if(l==r) {
				sum=b[l];
				mxL=mxR=mx=Math.max(b[l], 0);
			} else {
				int m=(l+r)/2;
				lc = new Node(l, m, b);
				rc = new Node(m+1, r, b);
				cmb();
			}
		}
		void cmb() {
			sum=lc.sum+rc.sum;
			mxL=Math.max(lc.sum+rc.mxL, lc.mxL);
			mxR=Math.max(rc.sum+lc.mxR, rc.mxR);
			mx=Math.max(lc.mxR+rc.mxL, Math.max(lc.mx, rc.mx));
		}
		Node qry(int l2, int r2) {
			if(l2<=l&&r<=r2)
				return this;
			int m=(l+r)/2;
			if(l2>m)
				return rc.qry(l2, r2);
			if(m>=r2)
				return lc.qry(l2, r2);
			Node r = new Node();
			r.lc=lc.qry(l2, r2);
			r.rc=rc.qry(l2, r2);
			r.cmb();
			return r;
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
