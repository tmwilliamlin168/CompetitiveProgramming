/*
	- Basic idea is to reduce the number of edges by dividing a query range into at most logn segments => (n+q)logn edges
	- Create extra nodes to represent those segments
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final int sts=1<<18;
	static final long INF=(long)1e18;
	static int n, q, s, n2;
	static List<Pair>[] adj;
	
	public static void main(String[] args) {
		n=in.nextInt();
		q=in.nextInt();
		s=in.nextInt()-1;
		n2=n+2*sts;
		adj = new List[n2];
		for(int i=0; i<n2; ++i)
			adj[i] = new ArrayList<Pair>();
		b(1, 0, n-1);
		while(q-->0) {
			int t=in.nextInt();
			if(t==1) {
				int v=in.nextInt()-1, u=in.nextInt()-1, w=in.nextInt();
				ae1(v, u, u, w, 1, 0, n-1);
			} else if(t==2)
				ae1(in.nextInt()-1, in.nextInt()-1, in.nextInt()-1, in.nextInt(), 1, 0, n-1);
			else
				ae2(in.nextInt()-1, in.nextInt()-1, in.nextInt()-1, in.nextInt(), 1, 0, n-1);
		}
		long[] dist = new long[n2];
		boolean[] vis = new boolean[n2];
		Arrays.fill(dist, INF);
		dist[s]=0;
		PriorityQueue<Pair> pq = new PriorityQueue<Pair>();
		pq.add(new Pair(s, 0));
		while(!pq.isEmpty()) {
			Pair p=pq.poll();
			if(vis[p.a])
				continue;
			vis[p.a]=true;
			for(Pair e : adj[p.a]) {
				if(dist[p.a]+e.b<dist[e.a]) {
					dist[e.a]=dist[p.a]+e.b;
					pq.add(new Pair(e.a, dist[e.a]));
				}
			}
		}
		for(int i=0; i<n; ++i)
			out.print((dist[i]>=INF?-1:dist[i])+" ");
		out.close();
	}
	
	static void b(int i, int l2, int r2) {
		for(int j=l2; j<=r2; ++j) {
			adj[n+i].add(new Pair(j, 0));
			adj[j].add(new Pair(n+sts+i, 0));
		}
		if(l2==r2)
			return;
		int m2=(l2+r2)/2;
		b(2*i, l2, m2);
		b(2*i+1, m2+1, r2);
	}
	
	static void ae1(int v, int l, int r, int w, int i, int l2, int r2) {
		if(l<=l2&&r2<=r) {
			adj[v].add(new Pair(n+i, w));
			return;
		}
		int m2=(l2+r2)/2;
		if(l<=m2)
			ae1(v, l, r, w, 2*i, l2, m2);
		if(m2<r)
			ae1(v, l, r, w, 2*i+1, m2+1, r2);
	}
	
	static void ae2(int v, int l, int r, int w, int i, int l2, int r2) {
		if(l<=l2&&r2<=r) {
			adj[n+sts+i].add(new Pair(v, w));
			return;
		}
		int m2=(l2+r2)/2;
		if(l<=m2)
			ae2(v, l, r, w, 2*i, l2, m2);
		if(m2<r)
			ae2(v, l, r, w, 2*i+1, m2+1, r2);
	}
	
	static class Pair implements Comparable<Pair> {
		int a;
		long b;
		Pair(int a, long b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return Long.compare(b, o.b);
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
