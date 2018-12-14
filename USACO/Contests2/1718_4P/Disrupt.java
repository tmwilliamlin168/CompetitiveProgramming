import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "disrupt";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		List<Integer>[] adj;
		int dt;
		int[] sz, dep, par, st, prt;
		
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			Pair[] e = new Pair[n-1];
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=0; i<n-1; ++i) {
				e[i] = new Pair(in.nextInt()-1, in.nextInt()-1);
				adj[e[i].a].add(e[i].b);
				adj[e[i].b].add(e[i].a);
			}
			sz = new int[n];
			dep = new int[n];
			par = new int[n];
			st = new int[n];
			prt = new int[n];
			par[0]=-1;
			dfs1(0);
			dfs2(0, true);
			List<Integer>[] toAdd = new List[n], toDel = new List[n];
			for(int i=0; i<n; ++i) {
				toAdd[i] = new ArrayList<Integer>();
				toDel[i] = new ArrayList<Integer>();
			}
			while(m-->0) {
				int u=in.nextInt()-1, v=in.nextInt()-1, w=in.nextInt();
				while(prt[u]!=prt[v]) {
					if(dep[prt[v]]>dep[prt[u]]) {
						u^=v;
						v^=u;
						u^=v;
					}
					toAdd[st[prt[u]]].add(w);
					toDel[st[u]].add(w);
					u=par[prt[u]];
				}
				if(u!=v) {
					if(dep[v]>dep[u]) {
						u^=v;
						v^=u;
						u^=v;
					}
					toAdd[st[v]+1].add(w);
					toDel[st[u]].add(w);
				}
			}
			int[] ans = new int[n];
			Arrays.fill(ans, Integer.MAX_VALUE);
			PriorityQueue<Integer> pq1 = new PriorityQueue<Integer>(), pq2 = new PriorityQueue<Integer>();
			pq1.add(Integer.MAX_VALUE);
			for(int i=0; i<n; ++i) {
				for(int j : toAdd[i])
					pq1.add(j);
				ans[i]=pq1.peek();
				for(int j : toDel[i])
					pq2.add(j);
				while(!pq2.isEmpty()&&(int)pq1.peek()==(int)pq2.peek()) {
					pq1.poll();
					pq2.poll();
				}
			}
			for(int i=0; i<n-1; ++i) {
				if(dep[e[i].b]>dep[e[i].a]) {
					e[i].a^=e[i].b;
					e[i].b^=e[i].a;
					e[i].a^=e[i].b;
				}
				out.println(ans[st[e[i].a]]==Integer.MAX_VALUE?-1:ans[st[e[i].a]]);
			}
		}
		
		void dfs1(int u) {
			sz[u]=1;
			dep[u]=par[u]==-1?0:dep[par[u]]+1;
			for(int v : adj[u]) {
				if(v==par[u])
					continue;
				par[v]=u;
				dfs1(v);
				sz[u]+=sz[v];
			}
		}
		
		void dfs2(int u, boolean np) {
			st[u]=dt++;
			prt[u]=np?u:prt[par[u]];
			int mc=-1;
			for(int v : adj[u])
				if(v!=par[u]&&(mc==-1||sz[v]>sz[mc]))
					mc=v;
			if(mc==-1)
				return;
			dfs2(mc, false);
			for(int v : adj[u])
				if(v!=par[u]&&v!=mc)
					dfs2(v, true);
		}
		
		class Pair {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
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
