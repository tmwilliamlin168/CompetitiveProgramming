import java.io.*;
import java.util.*;

public class Main {
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			List<Seg> v = new ArrayList<Seg>(), h = new ArrayList<Seg>();
			for(int i=0; i<n; ++i) {
				int x1=in.nextInt(), y1=in.nextInt(), x2=in.nextInt(), y2=in.nextInt();
				if(x1==x2)
					v.add(new Seg(Math.min(y1, y2), Math.max(y1, y2), x1));
				if(y1==y2)
					h.add(new Seg(Math.min(x1, x2), Math.max(x1, x2), y1));
			}
			List<Integer>[] intersect = new List[v.size()];
			for(int i=0; i<v.size(); ++i) {
				intersect[i] = new ArrayList<Integer>();
				for(int j=0; j<h.size(); ++j)
					if(v.get(i).a<=h.get(j).c&&v.get(i).b>=h.get(j).c&&h.get(j).a<=v.get(i).c&&h.get(j).b>=v.get(i).c)
						intersect[i].add(j);
			}
			Graph graph = new Graph(n+2);
			for(int i=0; i<v.size(); ++i) {
				graph.addEdge(0, i+1, 1);
				for(int j : intersect[i])
					graph.addEdge(i+1, j+v.size()+1, 1);
			}
			for(int i=0; i<h.size(); ++i)
				graph.addEdge(i+v.size()+1, n+1, 1);
			out.println(n-graph.maxFlow(0, n+1));
		}
		
		class Graph {
			int n;
			List<Edge>[] adjList;
			Graph(int n) {
				this.n=n;
				adjList = new List[n];
				for(int i=0; i<n; ++i)
					adjList[i] = new ArrayList<Edge>();
			}
			void addEdge(int from, int to, int cap) {
				adjList[from].add(new Edge(from, to, cap, adjList[to].size()));
				adjList[to].add(new Edge(to, from, 0, adjList[from].size()-1));
			}
			int maxFlow(int source, int sink) {
				int tFlow=0;
				int[] qu = new int[n];
				Edge[] prevE = new Edge[n];
				while(true) {
					qu[0]=source;
					Arrays.fill(prevE, null);
					prevE[source]=new Edge(-1, -1, -1, -1);
					for(int qt=1, qh=0; qh<qt&&prevE[sink]==null;) {
						int u=qu[qh++];
						for(Edge e : adjList[u]) {
							if(prevE[e.to]==null&&e.cap>0) {
								prevE[e.to]=e;
								qu[qt++]=e.to;
							}
						}
					}
					if(prevE[sink]==null)
						break;
					int minCap=Integer.MAX_VALUE;
					for(int c=sink; c!=source; c=prevE[c].from)
						minCap=Math.min(prevE[c].cap, minCap);
					for(int c=sink; c!=source; c=prevE[c].from) {
						prevE[c].cap-=minCap;
						adjList[prevE[c].to].get(prevE[c].rev).cap+=minCap;
					}
					tFlow+=minCap;
				}
				return tFlow;
			}
			class Edge {
				int from, to, cap, rev;
				Edge(int from, int to, int cap, int rev) {
					this.from=from;
					this.to=to;
					this.cap=cap;
					this.rev=rev;
				}
			}
		}
		
		class Seg {
			int a, b, c;
			Seg(int a, int b, int c) {
				this.a=a;
				this.b=b;
				this.c=c;
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
