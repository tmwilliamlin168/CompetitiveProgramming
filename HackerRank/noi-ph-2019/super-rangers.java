import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final int M=(int)1e9+7;
	static List<Integer>[] adj;
	static int[] tin, low, eu, ev, who, st;
	static int dt=1, sth, ci;
	static long[] dp, ans;
	
	static void dfs1(int u, int pe) {
		tin[u]=low[u]=dt++;
		st[sth++]=u;
		for(int e : adj[u]) {
			if(e==pe)
				continue;
			int v=u^eu[e]^ev[e];
			if(tin[v]<1) {
				dfs1(v, e);
				low[u]=Math.min(low[v], low[u]);
			}
			low[u]=Math.min(tin[v], low[u]);
		}
		if(tin[u]==low[u]) {
			do
				who[st[--sth]]=ci;
			while(st[sth]!=u);
			++ci;
		}
	}
	
	static void dfs2(int u) {
		dp[u]=1;
		for(int v : adj[u]) {
			dfs2(v);
			dp[u]=dp[u]*dp[v]%M;
		}
		dp[u]=(dp[u]+1)%M;
	}
	
	static void dfs3(int u, long p) {
		long[] a = new long[adj[u].size()+1], b = new long[adj[u].size()+1];
		a[0]=b[adj[u].size()]=1;
		for(int i=0; i<adj[u].size(); ++i)
			a[i+1]=a[i]*dp[adj[u].get(i)]%M;
		for(int i=adj[u].size()-1; i>=0; --i)
			b[i]=b[i+1]*dp[adj[u].get(i)]%M;
		ans[u]=a[adj[u].size()]*p%M;
		for(int i=0; i<adj[u].size(); ++i)
			dfs3(adj[u].get(i), (a[i]*b[i+1]%M*p+1)%M);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt(), q=in.nextInt();
		int[] a = new int[q];
		for(int i=0; i<q; ++i)
			a[i]=in.nextInt()-1;
		adj = new List[n];
		for(int i=0; i<n; ++i)
			adj[i] = new ArrayList<Integer>();
		eu = new int[m];
		ev = new int[m];
		for(int i=0; i<m; ++i) {
			eu[i]=in.nextInt()-1;
			ev[i]=in.nextInt()-1;
			adj[eu[i]].add(i);
			adj[ev[i]].add(i);
		}
		tin = new int[n];
		low = new int[n];
		who = new int[n];
		st = new int[n];
		dfs1(0, -1);
		for(int i=0; i<ci; ++i)
			adj[i] = new ArrayList<Integer>();
		for(int i=0; i<m; ++i)
			if(who[eu[i]]!=who[ev[i]])
				adj[Math.max(who[eu[i]], who[ev[i]])].add(Math.min(who[eu[i]], who[ev[i]]));
		dp = new long[ci];
		dfs2(ci-1);
		ans = new long[ci];
		dfs3(ci-1, 1);
		for(int i=0; i<q; ++i)
			out.print(ans[who[a[i]]]+" ");
		out.close();
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
