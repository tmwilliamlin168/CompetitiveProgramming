/*
	- There are 2N-2 other dancers in the same row or column, and there are 2N different costumes, so there will always be a valid type to change to
	- Problem becomes to remove the minimum number of dancers such that in the same row or column, no two dancers have the same costume
	- For each costume, create a bipartite graph
		- One side represents the rows and the other side represents the columns
		- For each dancer, create an edge between the nodes for the row and column that the dancer is in
	- Keep maximum number of dancers => find maximum set of edges that don't share the row of column nodes
	- Which is max flow/matching
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static boolean[][] vis = new boolean[100][100];
	static int n;
	static int[][] a = new int[100][100];
	static List<Pair> ps = new ArrayList<Pair>();
	
	public static void main(String[] args) {
		for(int i=0; i<100; ++i)
			adj[i] = new ArrayList<Integer>();
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti) {
			n=in.nextInt();
			int ans=n*n;
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
				    a[i][j]=in.nextInt();
			for(int i=0; i<n; ++i)
				Arrays.fill(vis[i], false);
			for(int i=0; i<n; ++i) {
				for(int j=0; j<n; ++j) {
					if(vis[i][j])
						continue;
					ps.clear();
					dfs(i, j);
					ans-=mf();
				}
			}
			out.println("Case #"+ti+": "+ans);
		}
		out.close();
	}
	
	static void dfs(int i, int j) {
		vis[i][j]=true;
		ps.add(new Pair(i, j));
		for(int k=i-1; k>=0; --k) {
			if(a[k][j]==a[i][j]) {
				if(!vis[k][j])
					dfs(k, j);
				break;
			}
		}
		for(int k=i+1; k<n; ++k) {
			if(a[k][j]==a[i][j]) {
				if(!vis[k][j])
					dfs(k, j);
				break;
			}
		}
		for(int k=j-1; k>=0; --k) {
			if(a[i][j]==a[i][k]) {
				if(!vis[i][k])
					dfs(i, k);
				break;
			}
		}
		for(int k=j+1; k<n; ++k) {
			if(a[i][j]==a[i][k]) {
				if(!vis[i][k])
					dfs(i, k);
				break;
			}
		}
	}
	
	static List<Integer>[] adj = new List[100];
	static int[] matching = new int[100];
	static boolean[] v2 = new boolean[100];
	
	static int mf() {
		int r=0;
		for(int i=0; i<n; ++i)
			adj[i].clear();
		for(Pair p : ps)
			adj[p.a].add(p.b);
		Arrays.fill(matching, -1);
		for(int i=0; i<n; ++i) {
			Arrays.fill(v2, false);
			if(fp(i))
				++r;
		}
		return r;
	}
	
	static boolean fp(int u) {
		v2[u]=true;
		for(int v : adj[u]) {
			int u2=matching[v];
			if (u2 == -1 || !v2[u2] && fp(u2)) {
				matching[v] = u;
				return true;
			}
		}
		return false;
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
