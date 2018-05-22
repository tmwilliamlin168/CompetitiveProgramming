package section_4_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: ditch
*/
import java.io.*;
import java.util.*;

public class ditch {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "ditch";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			Edge[] edges = new Edge[2*n];
			List<Integer>[] graph = new List[m];
			for(int i=0; i<m; ++i)
				graph[i] = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				int s=in.nextInt()-1, e=in.nextInt()-1, c=in.nextInt();
				edges[2*i]=new Edge(2*i, s, e, c);
				graph[s].add(2*i);
				edges[2*i+1]=new Edge(2*i+1, e, s, 0);
				graph[e].add(2*i+1);
			}
			int tFlow=0;
			int[] qu = new int[m];
			int[] prevEdge = new int[m];
			int qt, qh;
			while(true) {
				//Find path
				boolean foundPath=false;
				qt=qh=0;
				qu[qt++]=0;
				Arrays.fill(prevEdge, -1);
				prevEdge[0]=-2;
				while(qt>qh) {
					int node=qu[qh++];
					if(node==m-1) {
						foundPath=true;
						break;
					}
					for(int e : graph[node]) {
						if(edges[e].cap>0&&prevEdge[edges[e].to]==-1) {
							qu[qt++]=edges[e].to;
							prevEdge[edges[e].to]=e;
						}
					}
				}
				if(!foundPath)
					break;
				int minCap=Integer.MAX_VALUE, c=m-1;
				while(prevEdge[c]!=-2) {
					minCap=Math.min(edges[prevEdge[c]].cap, minCap);
					c=edges[prevEdge[c]].from;
				}
				c=m-1;
				while(prevEdge[c]!=-2) {
					edges[prevEdge[c]].cap-=minCap;
					edges[prevEdge[c]^1].cap+=minCap;
					c=edges[prevEdge[c]].from;
				}
				tFlow+=minCap;
			}
			out.println(tFlow);
			TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer>();
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