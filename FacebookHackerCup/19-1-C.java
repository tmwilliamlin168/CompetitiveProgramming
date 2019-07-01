import java.io.*;
import java.util.*;

public class C {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int n=in.nextInt(), h=in.nextInt();
			Ladder[] l = new Ladder[n];
			List<Integer> p = new ArrayList<Integer>(Arrays.asList(0, h));
			for(int i=0; i<n; ++i) {
				l[i] = new Ladder(in.nextInt(), in.nextInt(), in.nextInt());
				p.add(l[i].a);
				p.add(l[i].b);
			}
			Arrays.sort(l);
			Collections.sort(p);
			for(int i=0; i<n; ++i) {
				l[i].a=Collections.binarySearch(p, l[i].a);
				l[i].b=Collections.binarySearch(p, l[i].b);
			}
			Graph g = new Graph(n*(p.size()-1)+2);
			for(int i=0; i<n; ++i) {
				for(int j=l[i].a; j+1<l[i].b; ++j)
					g.addEdge(i*(p.size()-1)+j, i*(p.size()-1)+j+1, (int)1e9);
				for(int j=l[i].a; j<l[i].b; ++j) {
					int k=i-1;
					while(k>=0&&(l[k].a>j||j>=l[k].b))
						--k;
					if(k>=0)
						g.addEdge(i*(p.size()-1)+j, k*(p.size()-1)+j, p.get(j+1)-p.get(j));
				}
				if(p.get(l[i].a)==0)
					g.addEdge(n*(p.size()-1), i*(p.size()-1)+l[i].a, (int)1e9);
				if(p.get(l[i].b)==h)
					g.addEdge(n*(p.size()-1)+1, i*(p.size()-1)+l[i].b-1, (int)1e9);
			}
			int ans=g.maxFlow(n*(p.size()-1), n*(p.size()-1)+1);
			out.println("Case #"+_+": "+(ans>=1e9?-1:ans));
		}
		out.close();
	}
	
	static class Ladder implements Comparable<Ladder> {
		int x, a, b;
		Ladder(int x, int a, int b) {
			this.x=x;
			this.a=a;
			this.b=b;
		}
		public int compareTo(Ladder o) {
			return x-o.x;
		}
	}
	
	static class Graph {
		int n;
		List<Edge>[] adjList;
		Graph(int n) {
			this.n=n;
			adjList = new List[n];
			for(int i=0; i<n; ++i)
				adjList[i] = new ArrayList<Edge>();
		}
		void addEdge(int u, int v, int c) {
			adjList[u].add(new Edge(u, v, c, adjList[v].size()));
			adjList[v].add(new Edge(v, u, c, adjList[u].size()-1));
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
