/*
ID: tmwilliamlin168
LANG: JAVA
TASK: schlnet
*/
import java.io.*;
import java.util.*;

public class schlnet {
	static final boolean stdin = false;
	static final String filename = "schlnet";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			List<Integer>[] adj1 = new List[n], adj2 = new List[n];
			for(int i=0; i<n; ++i)
				adj2[i] = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				adj1[i] = new ArrayList<Integer>();
				int j;
				while((j=in.nextInt()-1)!=-1) {
					adj1[i].add(j);
					adj2[j].add(i);
				}
			}
			
			int a1=a(n, adj1), a2=a(n, adj2);
			out.println(a1);
			out.println(scc(n, adj1)?0:Math.max(a1, a2));
		}
	}
	
	static int a(int n, List<Integer>[] adj) {
		int r=0;
		boolean[] rec = new boolean[n], vis = new boolean[n];
		while(true) {
			int mi=-1;
			for(int i=0; i<n; ++i)
				if(!vis[i])
					dfs(mi=i, adj, vis);
			if(mi==-1)
				break;
			dfs(mi, adj, rec);
			vis=Arrays.copyOf(rec, n);
			++r;
		}
		return r;
	}
	
	static boolean scc(int n, List<Integer>[] adj) {
		boolean[] vis = new boolean[n];
		for(int i=0; i<n; ++i) {
			dfs(i, adj, vis);
			for(int j=0; j<n; ++j)
				if(!vis[j])
					return false;
			Arrays.fill(vis, false);
		}
		return true;
	}
	
	static void dfs(int u, List<Integer>[] adj, boolean[] vis) {
		vis[u]=true;
		for(int v : adj[u])
			if(!vis[v])
				dfs(v, adj, vis);
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