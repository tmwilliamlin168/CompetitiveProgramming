import java.io.*;
import java.util.*;

public class Gathering {
	static final boolean stdin = false;
	static final String filename = "gathering";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		List<Integer>[] adj1, adj2;
		int dt;
		int[] ds, de, gd, gu;
		int[][] anc;
		boolean[] vis, act, a1;
		boolean fk;
		
		Solver() {
			//input
			int n=in.nextInt(), m=in.nextInt();
			adj1 = new List[n];
			adj2 = new List[n];
			for(int i=0; i<n; ++i) {
				adj1[i] = new ArrayList<Integer>();
				adj2[i] = new ArrayList<Integer>();
			}
			for(int i=0; i<n-1; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				adj1[u].add(v);
				adj1[v].add(u);
			}
			//find basic tree stuff
			ds = new int[n];
			de = new int[n];
			anc = new int[n][17];
			vis = new boolean[n];
			dfs1(0, -1);
			gd = new int[n+1];
			gu = new int[n];
			while(m-->0) {
				int a=in.nextInt()-1, b=in.nextInt()-1;
				adj2[b].add(a);
				if(ds[a]<ds[b]&&ds[b]<de[a]) {
					//b is descendant
					//add downward edges to all nodes but subtree with b
					++gd[1];
					--gd[n];
					//child of a that is b's ancestor
					int c=b;
					for(int i=16; i>=0; --i)
						if(anc[c][i]!=-1&&ds[a]<ds[anc[c][i]])
							c=anc[c][i];
					--gd[ds[c]];
					++gd[de[c]];
					//upward edges from a to root
					++gu[ds[a]];
				} else {
					//add downward edges to a's subtree
					++gd[ds[a]+1];
					--gd[de[a]];
				}
			}
			//Postprocess down edges
			for(int i=1; i<n; ++i)
				gd[i]+=gd[i-1];
			//Postprocess up edges
			dfs2(0);
			//Add the down/up edges
			for(int i=1; i<n; ++i) {
				if(gd[ds[i]]>0)
					adj2[anc[i][0]].add(i);
				if(gu[ds[i]]>0)
					adj2[i].add(anc[i][0]);
			}
			//Check DAG and find nodes with in-degree 0
			act = new boolean[n];
			a1 = new boolean[n];
			for(int i=0; i<n; ++i)
				if(!vis[i])
					dfs3(i);
			//output
			for(int i=0; i<n; ++i)
				out.println(!a1[i]&&!fk?1:0);
		}
		
		void dfs1(int u, int p) {
			ds[u]=dt++;
			anc[u][0]=p==-1?-1:p;
			for(int i=1; i<17; ++i)
				anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
			for(int v : adj1[u])
				if(v!=p)
					dfs1(v, u);
			de[u]=dt;
		}
		
		void dfs2(int u) {
			for(int v : adj1[u]) {
				if(v==anc[u][0])
					continue;
				dfs2(v);
				gu[ds[u]]+=gu[ds[v]];
			}
			gd[ds[u]]-=gu[ds[u]];
		}
		
		void dfs3(int u) {
			vis[u]=true;
			act[u]=true;
			for(int v : adj2[u]) {
				a1[v]=true;
				fk|=act[v];
				if(!vis[v])
					dfs3(v);
			}
			act[u]=false;
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