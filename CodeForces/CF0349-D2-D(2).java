/*
	- http://codeforces.com/blog/entry/9031
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long INF=(long)1e18;
	static List<Integer>[] adj;
	static long[] s, l;
	static long ans;
	
	public static void main(String[] args) {
		int n=in.nextInt();
		adj = new List[n];
		for(int i=0; i<n; ++i)
			adj[i] = new ArrayList<Integer>();
		s = new long[n];
		for(int i=0; i<n; ++i)
			s[i]=in.nextInt();
		l = new long[n];
		Arrays.fill(l, 1);
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
		long mic=INF, cn=(adj[u].size()-(p==-1?0:1));
		if(cn==0)
			return;
		for(int v : adj[u]) {
			if(v==p)
				continue;
			dfs(v, u);
			l[u]=l[u]/gcd(l[u], l[v])>INF/l[v]?INF:l[u]/gcd(l[u], l[v])*l[v];
		}
		for(int v : adj[u])
			if(v!=p)
				mic=Math.min(s[v]/l[u]*l[u], mic);
		for(int v : adj[u])
			if(v!=p)
				ans+=s[v]-mic;
		s[u]=mic*cn;
		l[u]=l[u]>INF/cn?INF:l[u]*cn;
	}
	
	static long gcd(long a, long b) {
		while((a%=b)>0&&(b%=a)>0);
		return a^b;
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
