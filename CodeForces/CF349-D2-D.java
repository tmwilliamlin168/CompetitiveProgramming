/*
	- For each node i, find l[i] = the minimum number of apples you can remove from this subtree at once
		- Can be calculated with dp + lcm
	- When there are 2 subtrees of unequal size (i and j), we need to find x>=0 and y>=0 such that s[i]-x*l[i]=s[j]-y*l[j] and x/y is minimized
		- Extended gcd
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long INF=(long)1e18;
	static List<Integer>[] adj;
	static long[] a, s, l;
	static long ans;
	
	public static void main(String[] args) {
		int n=in.nextInt();
		adj = new List[n];
		for(int i=0; i<n; ++i)
			adj[i] = new ArrayList<Integer>();
		a = new long[n];
		for(int i=0; i<n; ++i)
			a[i]=in.nextInt();
		s = new long[n];
		l = new long[n];
		for(int i=0; i<n-1; ++i) {
			int u=in.nextInt()-1, v=in.nextInt()-1;
			adj[u].add(v);
			adj[v].add(u);
		}
		dfs(0, -1);
		out.println(ans);
		out.close();
	}
	
	static void dfs(int u, int p) {
		long mic=INF, lcm=1;
		for(int v : adj[u]) {
			if(v==p)
				continue;
			dfs(v, u);
			if(mic==0)
				continue;
			long g=gcde(lcm, l[v]);
			if(mic>=INF)
				mic=s[v];
			else {
				if(mic<s[v]) {
					gx*=(mic-s[v])/g;
					gx=(gx%(l[v]/g)+l[v]/g)%(l[v]/g);
					mic-=lcm*gx;
				} else {
					gy*=(s[v]-mic)/g;
					gy=(gy%(lcm/g)+lcm/g)%(lcm/g);
					mic=s[v]-l[v]*gy;
				}
			}
			lcm=lcm/g*l[v];
		}
		if(mic>=INF) {
			s[u]=a[u];
			l[u]=1;
			return;
		}
		for(int v : adj[u]) {
			if(v==p)
				continue;
			ans+=s[v]-mic;
			s[u]+=mic;
			l[u]+=lcm;
		}
	}
	
	static long gx, gy;
	static long gcde(long a, long b) {
		if(a==0) {
			gx=0;
			gy=1;
			return b;
		}
		long r=gcde(b%a, a), t=gx;
		gx=gy-(b/a)*gx;
		gy=t;
		return r;
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
