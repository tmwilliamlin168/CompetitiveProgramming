/*
ID: tmwilliamlin168
LANG: JAVA
TASK: telecow
*/
import java.io.*;
import java.util.*;

public class telecow {
	static final boolean stdin = false;
	static final String filename = "telecow";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt(), c1=in.nextInt()-1, c2=in.nextInt()-1;
			Graph graph = new Graph(2*n);
			for(int i=0; i<n; ++i)
				graph.addEdge(2*i, 2*i+1, 1);
			while(m-->0) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				graph.addEdge(2*u+1, 2*v, n);
				graph.addEdge(2*v+1, 2*u, n);
			}
			int mf=graph.maxFlow(2*c1+1, 2*c2);
			out.println(mf);
			for(int i=0, j=0; i<n; ++i) {
				if(i==c1||i==c2)
					continue;
				graph.adj[2*i].get(0).c2=0;
				int cf=graph.maxFlow(2*c1+1, 2*c2);
				if(cf!=mf) {
					if(j>0)
						out.print(" ");
					j=1;
					out.print(i+1);
					mf=cf;
				} else
					graph.adj[2*i].get(0).c2=1;
			}
			out.println();
		}
		
		class Graph {
			int n;
			List<Edge>[] adj;
			Graph(int n) {
				this.n=n;
				adj = new List[n];
				for(int i=0; i<n; ++i)
					adj[i] = new ArrayList<Edge>();
			}
			void addEdge(int u, int v, int c) {
				adj[u].add(new Edge(u, v, c, adj[v].size()));
				adj[v].add(new Edge(v, u, 0, adj[u].size()-1));
			}
			int maxFlow(int s, int t) {
				for(List<Edge> es : adj)
					for(Edge e : es)
						e.c=e.c2;
				int f=0;
				int[] qu = new int[n];
				Edge[] pv = new Edge[n];
				while(true) {
					int qh=0, qt=0;
					Arrays.fill(pv, null);
					qu[qt++]=s;
					while(qh<qt&&pv[t]==null) {
						int u=qu[qh++];
						for(Edge e : adj[u]) {
							if(e.c<=0||pv[e.v]!=null||e.v==s)
								continue;
							qu[qt++]=e.v;
							pv[e.v]=e;
						}
					}
					if(pv[t]==null)
						break;
					for(int u=t; u!=s; u=pv[u].u) {
						--pv[u].c;
						++adj[pv[u].v].get(pv[u].r).c;
					}
					++f;
				}
				return f;
			}
			class Edge {
				int u, v, c, c2, r;
				Edge(int u, int v, int c, int r) {
					this.u=u;
					this.v=v;
					c2=c;
					this.r=r;
				}
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