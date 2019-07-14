import java.io.*;
import java.util.*;

public class B {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int n=in.nextInt(), m=in.nextInt();
			List<Integer>[] adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			int[] mp = new int[2*n-1];
			for(int i=0; i<m; ++i) {
				int x=in.nextInt()-1, y=in.nextInt()-1;
				mp[x+y]=Math.max(mp[x+y], (y-x)/2+1);
			}
			for(int i=0; i<2*n-1; ++i) {
				int l=i/2, r=(i+1)/2;
				for(int j=0; j<mp[i]; ++j) {
					adj[l-j].add(r+j);
					adj[r+j].add(l-j);
				}
			}
			List<Pair> s = new ArrayList<Pair>();
			boolean[] vis = new boolean[n];
			for(int i=0; i<n; ++i)
				if(!vis[i])
					s.add(new Pair(i, dfs1(i, adj, vis)));
			boolean[][] dp = new boolean[s.size()+1][n/2+1];
			dp[0][0]=true;
			for(int i=0; i<s.size(); ++i) {
				dp[i+1]=Arrays.copyOf(dp[i], n/2+1);
				for(int j=0; j+s.get(i).b<=n/2; ++j)
					dp[i+1][j+s.get(i).b]|=dp[i][j];
			}
			int[] c = new int[n];
			for(int j=n/2; j>=0; --j) {
				if(!dp[s.size()][j])
					continue;
				int i=s.size();
				while(i>0) {
					if(!dp[i-1][j]) {
						j-=s.get(i-1).b;
						dfs2(s.get(i-1).a, adj, c);
					}
					--i;
				}
				break;
			}
			out.print("Case #"+_+": ");
			for(int i=0; i<n; ++i)
				out.print(c[i]);
			out.println();
		}
		out.close();
	}
	
	static int dfs1(int u, List<Integer>[] adj, boolean[] vis) {
		int s=1;
		vis[u]=true;
		for(int v : adj[u])
			if(!vis[v])
				s+=dfs1(v, adj, vis);
		return s;
	}
	
	static void dfs2(int u, List<Integer>[] adj, int[] c) {
		c[u]=1;
		for(int v : adj[u])
			if(c[v]<1)
				dfs2(v, adj, c);
	}
	
	static class Pair {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
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
