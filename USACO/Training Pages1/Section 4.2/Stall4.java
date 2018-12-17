package section_4_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: stall4
*/
import java.io.*;
import java.util.*;

public class stall4 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "stall4";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			Graph graph = new Graph(n+m+2);
			for(int i=0; i<n; ++i) {
				graph.addEdge(0, i+1, 1);
				for(int s=in.nextInt(); s>0; --s)
					graph.addEdge(i+1, n+in.nextInt(), 1);
			}
			for(int i=0; i<m; ++i)
				graph.addEdge(n+1+i, n+m+1, 1);
			out.println(graph.maxFlow(0, n+m+1));
		}
		class Graph {
			int n;
			List<Edge> edges = new ArrayList<Edge>();
			List<Integer>[] adjList;
			Graph(int n) {
				this.n=n;
				adjList = new List[n];
				for(int i=0; i<n; ++i)
					adjList[i] = new ArrayList<Integer>();
			}
			void addEdge(int from, int to, int cap) {
				edges.add(new Edge(edges.size(), from, to, cap));
				adjList[from].add(edges.size()-1);
				edges.add(new Edge(edges.size(), to, from, 0));
				adjList[to].add(edges.size()-1);
			}
			int maxFlow(int source, int sink) {
				int tFlow=0, qt, qh;
				int[] qu = new int[n], prevE = new int[n];
				while(true) {
					//find augmenting path
					qt=qh=0;
					qu[qt++]=source;
					Arrays.fill(prevE, -1);
					prevE[source]=-2;
					boolean foundPath=false;
					while(qt>qh) {
						int node=qu[qh++];
						if(node==sink) {
							foundPath=true;
							break;
						}
						for(int edgeI : adjList[node]) {
							Edge edge=edges.get(edgeI);
							if(prevE[edge.to]==-1&&edge.cap>0) {
								prevE[edge.to]=edgeI;
								qu[qt++]=edge.to;
							}
						}
					}
					if(!foundPath)
						break;
					//backtrack path
					int minCap=Integer.MAX_VALUE, c=sink;
					while(c!=source) {
						minCap=Math.min(edges.get(prevE[c]).cap, minCap);
						c=edges.get(prevE[c]).from;
					}
					c=sink;
					while(c!=source) {
						edges.get(prevE[c]).cap-=minCap;
						edges.get(prevE[c]^1).cap+=minCap;
						c=edges.get(prevE[c]).from;
					}
					tFlow+=minCap;
				}
				return tFlow;
			}
			class Edge {
				int id, from, to, cap;
				Edge(int id, int from, int to, int cap) {
					this.id=id;
					this.from=from;
					this.to=to;
					this.cap=cap;
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