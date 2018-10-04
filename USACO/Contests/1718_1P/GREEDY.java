import java.io.*;
import java.util.*;

public class Main {
	static boolean stdio=true;
	static Reader in = new Reader();
	static PrintWriter out;
	
	public static void main(String[] args) {
		if(stdio)
			out = new PrintWriter(System.out);
		else {
			try {
				out = new PrintWriter("greedy.out");
			} catch (Exception e) {}
		}
		int n=in.nextInt();
		SegTree segTree = new SegTree(n);
		for(int i=1; i<n; ++i)
			segTree.add(i, i, -i);
		for(int i=0; i<n; ++i) {
			int c=n-1-in.nextInt();
			segTree.add(c, n-1, 1);
			if(segTree.get(0, n-1)>0) {
				out.println(n-1-i);
				break;
			}
		}
		out.close();
	}
	
	static class SegTree {
		int n, l1, r1;
		int v;
		int[] a, lazy;
		SegTree(int n) {
			this.n=n;
			a = new int[4*n];
			lazy = new int[4*n];
		}
		void add(int l, int r, int x) {
			l1=l;
			r1=r;
			v=x;
			add2(1, 0, n-1);
		}
		private void add2(int i, int l2, int r2) {
			if(l1<=l2&&r2<=r1) {
				a[i]+=v;
				if(l2<r2) {
					lazy[2*i]+=v;
					lazy[2*i+1]+=v;
				}
			} else {
				int mid=(l2+r2)/2;
				push(i*2, l2, mid);
				push(i*2+1, mid+1, r2);
				if(l1<=mid)
					add2(i*2, l2, mid);
				if(mid<r1)
					add2(i*2+1, mid+1, r2);
				a[i]=Math.max(a[i*2], a[i*2+1]);
			}
		}
		void push(int i, int l, int r) {
			a[i]+=lazy[i];
			if(l<r) {
				lazy[2*i]+=lazy[i];
				lazy[2*i+1]+=lazy[i];
			}
			lazy[i]=0;
		}
		int get(int l, int r) {
			l1=l;
			r1=r;
			return get2(1, 0, n-1);
		}
		private int get2(int i, int l2, int r2) {
			push(i, l2, r2);
			if(l1<=l2&&r2<=r1)
				return a[i];
			else {
				int mid=(l2+r2)/2;
				int res=Integer.MIN_VALUE;
				if(l1<=mid)
					res = Math.max(get2(2*i, l2, mid), res);
				if(mid<r1)
					res = Math.max(get2(2*i+1, mid+1, r2), res);
				return res;
			}
		}
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			if(stdio)
				br = new BufferedReader(new InputStreamReader(System.in));
			else {
				try {
					br = new BufferedReader(new FileReader("greedy.in"));
				} catch (Exception e) {}
			}
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
