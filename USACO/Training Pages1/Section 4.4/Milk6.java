package section_4_4;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: milk6
*/
import java.io.*;
import java.util.*;

public class milk6 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "milk6";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			Graph graph = new Graph(n, m);
			for(int i=0; i<m; ++i)
				graph.addEdge(i, in.nextInt()-1, in.nextInt()-1, in.nextInt()*(m+1)+1);
			long tFlow=graph.maxFlow(0, n-1);
			out.print(tFlow/(m+1)+" ");
			List<Integer> minCut = new ArrayList<Integer>();
			for(int i=0; i<m; ++i) {
				long tCap=graph.edges[2*i].cap1;
				graph.edges[2*i].cap1=graph.edges[2*i].cap2=0;
				long cFlow=graph.maxFlow(0, n-1);
				if(tFlow-cFlow==tCap) {
					minCut.add(i+1);
					tFlow=cFlow;
					if(tFlow==0)
						break;
				} else
					graph.edges[2*i].cap1=graph.edges[2*i].cap2=tCap;
			}
			out.println(minCut.size());
			for(int edge : minCut)
				out.println(edge);
		}
		
		static class Graph {
			int n, m;
			Edge[] edges;
			List<Edge>[] adjList;
			Graph(int n, int m) {
				this.n=n;
				this.m=m;
				adjList = new List[n];
				for(int i=0; i<n; ++i)
					adjList[i]=new ArrayList<Edge>();
				edges = new Edge[2*m];
			}
			void addEdge(int id, int from, int to, long cap) {
				edges[id*2]=new Edge(id*2, from, to, cap);
				adjList[from].add(edges[id*2]);
				edges[(id*2)^1]=new Edge((id*2)^1, to, from, 0);
				adjList[to].add(edges[(id*2)^1]);
			}
			static final Edge SOURCE_EDGE = new Edge(-1, -1, -1, -1);
			long maxFlow(int source, int sink) {
				long tFlow=0;
				int[] qu = new int[n];
				Edge[] prevE = new Edge[n];
				while(true) {
					qu[0]=source;
					Arrays.fill(prevE, null);
					prevE[source]=SOURCE_EDGE;
					for(int qt=1, qh=0; qh<qt&&prevE[sink]==null;) {
						int node=qu[qh++];
						for(Edge edge : adjList[node]) {
							if(prevE[edge.to]==null&&edge.cap2>0) {
								prevE[edge.to]=edge;
								qu[qt++]=edge.to;
							}
						}
					}
					if(prevE[sink]==null)
						break;
					long minCap=Long.MAX_VALUE;
					for(int c=sink; c!=source; c=prevE[c].from)
						minCap=Math.min(prevE[c].cap2, minCap);
					for(int c=sink; c!=source; c=prevE[c].from) {
						prevE[c].cap2-=minCap;
						edges[prevE[c].id^1].cap2+=minCap;
					}
					tFlow+=minCap;
				}
				for(Edge edge : edges)
					edge.cap2=edge.cap1;
				return tFlow;
			}
			static class Edge {
				int id, from, to;
				long cap1, cap2;
				Edge(int id, int from, int to, long cap) {
					this.id=id;
					this.from=from;
					this.to=to;
					this.cap1=this.cap2=cap;
				}
			}
		}
	}
	
	static void preprocess() {
		
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		preprocess();
		for(int testCases=1; testCases>0; --testCases)
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