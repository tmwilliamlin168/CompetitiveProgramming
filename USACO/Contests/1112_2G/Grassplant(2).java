import java.io.*;
import java.util.*;

public class Main {
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		List<Integer>[] adj;
		int dt;
		int[] sz, dep, par, fti, prt;
		FenTree ft;
		
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=0; i<n-1; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				adj[u].add(v);
				adj[v].add(u);
			}
			sz = new int[n];
			dep = new int[n];
			par = new int[n];
			fti = new int[n];
			prt = new int[n];
			ft = new FenTree(n);
			par[0]=-1;
			dfs1(0);
			dfs2(0, true);
			while(m-->0) {
				char qt=in.next().charAt(0);
				int u=in.nextInt()-1, v=in.nextInt()-1;
				if(qt=='P') {
					upd(u, 1);
					upd(v, 1);
					while(prt[u]!=prt[v]) {
						if(dep[prt[u]]>dep[prt[v]])
							u=par[prt[u]];
						else
							v=par[prt[v]];
					}
					upd(dep[u]<dep[v]?u:v, -2);
				} else
					out.println(dep[u]>dep[v]?ft.qry(fti[u]+1):ft.qry(fti[v]+1));
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
			fti[u]=dt++;
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
		
		void upd(int u, int x) {
			for(; u!=-1; u=par[prt[u]]) {
				ft.upd(fti[prt[u]], x);
				ft.upd(fti[u]+1, -x);
			}
		}
		
		class FenTree {
			int[] a;
			FenTree(int n) {
				a = new int[n+1];
			}
			void upd(int i, int x) {
				for(++i; i<a.length; i+=i&-i)
					a[i]+=x;
			}
			int qry(int i) {
				int r=0;
				for(; i>0; i-=i&-i)
					r+=a[i];
				return r;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		in = new Reader();
		out = new PrintWriter(System.out);
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
