import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "maxflow";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		List<Integer>[] graph;
		int[] dep, s1, s2;
		int[][] anc;
		int ans;
		
		Solver() {
			int n=in.nextInt(), k=in.nextInt();
			graph = new List[n];
			for(int i=0; i<n; ++i)
				graph[i] = new ArrayList<Integer>();
			dep = new int[n];
			s1 = new int[n];
			s2 = new int[n];
			anc = new int[16][n];
			for(int i=0; i<n-1; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				graph[u].add(v);
				graph[v].add(u);
			}
			dfs1(0, -1);
			for(int i=1; i<anc.length; ++i)
				for(int j=0; j<n; ++j)
					anc[i][j]=anc[i-1][j]==-1?-1:anc[i-1][anc[i-1][j]];
			while(k-->0) {
				int u1=in.nextInt()-1, v1=in.nextInt()-1;
				if(dep[u1]<dep[v1]) {
					u1^=v1;
					v1^=u1;
					u1^=v1;
				}
				int u2=u1, v2=v1, lca;
				for(int i=anc.length-1; i>=0; --i)
					if(dep[u2]-dep[v2]>=1<<i)
						u2=anc[i][u2];
				if(u2!=v2) {
					for(int i=anc.length-1; i>=0; --i) {
						if(anc[i][u2]!=anc[i][v2]) {
							u2=anc[i][u2];
							v2=anc[i][v2];
						}
					}
					lca=anc[0][u2];
				} else
					lca=v1;
				--s2[lca];
				--s1[lca];
				++s2[u1];
				++s2[v1];
			}
			dfs2(0, -1);
			out.println(ans);
		}
		
		void dfs1(int u, int p) {
			anc[0][u]=p;
			dep[u]=p==-1?0:dep[p]+1;
			for(int v : graph[u])
				if(v!=p)
					dfs1(v, u);
		}
		
		int dfs2(int u, int p) {
			int s=s2[u];
			for(int v : graph[u])
				if(v!=p)
					s+=dfs2(v, u);
			ans=Math.max(s, ans);
			return s+s1[u];
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String filename) throws Exception {
			br = new BufferedReader(new FileReader(filename));
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
	}
}
