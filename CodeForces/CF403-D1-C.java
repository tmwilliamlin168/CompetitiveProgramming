/*
	- Create a graph where there is an edge from i to j if a_ij > 0
	- If (a^k)_ij > 0, then there is a path of length k from i to j
	- Since all entries have to be positive, the graph has to be strongly connected
	- sum(a_ii)>0 => there is at least one loop, call the vertex with the loop x
	- Consider all pairs (i, j) and the paths between them: i->x->j
	- Set k to the maximum path length
	- This works because if a path has length < k, we can increase the path length by using the loop on x
	- Thus, the answer is yes iff the graph is strongly connected
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt();
		List<Integer>[] adj = new List[n];
		for(int i=0; i<n; ++i) {
			adj[i] = new ArrayList<Integer>();
			for(int j=0; j<n; ++j)
				if(in.nextInt()>0)
					adj[i].add(j);
		}
		SCCFinder sccf = new SCCFinder(adj);
		for(int i=0; i<n; ++i) {
			if(sccf.who[i]!=0) {
				System.out.println("NO");
				return;
			}
		}
		System.out.println("YES");
	}
	
	static class SCCFinder {
		List<Integer>[] graph;
		List<List<Integer>> sccs = new ArrayList<List<Integer>>();
		int[] tin, low, who;
		Stack<Integer> st = new Stack<Integer>();
		boolean[] inst;
		int n, time=1;
		SCCFinder(List<Integer>[] graph) {
			this.graph=graph;
			n=graph.length;
			tin = new int[n];
			low = new int[n];
			who = new int[n];
			inst = new boolean[n];
			for(int i=0; i<n; ++i)
				if(tin[i]==0)
					dfs(i);
		}
		void dfs(int u) {
			tin[u]=low[u]=time++;
			st.push(u);
			inst[u]=true;
			for(int v : graph[u]) {
				if(tin[v]==0) {
					dfs(v);
					low[u]=Math.min(low[u], low[v]);
				} else if(inst[v])
					low[u]=Math.min(low[u], tin[v]);
			}
			if(tin[u]==low[u]) {
				List<Integer> scc = new ArrayList<Integer>();
				do {
					scc.add(st.peek());
					inst[st.peek()]=false;
					who[st.peek()]=sccs.size();
				} while(st.pop()!=u);
				sccs.add(scc);
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
