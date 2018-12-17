package section_4_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: race3
*/
import java.io.*;
import java.util.*;

public class race3 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "race3";
	
	static class Solver {
		List<List<Integer>> graph = new ArrayList<List<Integer>>();
		boolean[] visited;
		int excluded;
		
		Solver() {
			graph.add(new ArrayList<Integer>());
			int a;
			while((a=in.nextInt())!=-1) {
				if(a==-2)
					graph.add(new ArrayList<Integer>());
				else
					graph.get(graph.size()-1).add(a);
			}
			graph.remove(graph.size()-1);
			visited = new boolean[graph.size()];
			List<Integer> artPts = new ArrayList<Integer>();
			for(excluded=1; excluded<graph.size()-1; ++excluded) {
				if(!dfs(0))
					artPts.add(excluded);
				Arrays.fill(visited, false);
			}
			out.print(artPts.size());
			for(int artPt : artPts)
				out.print(" "+artPt);
			out.println();
			List<List<Integer>> oldGraph = new ArrayList<List<Integer>>();
			for(int i=0; i<graph.size(); ++i) {
				oldGraph.add(new ArrayList<Integer>());
				for(int neighbor : graph.get(i))
					oldGraph.get(i).add(neighbor);
			}
			for(int i=0; i<graph.size(); ++i)
				for(int neighbor : graph.get(i))
					if(neighbor!=i)
						graph.get(neighbor).add(i);
			List<Integer> artPts2 = new ArrayList<Integer>();
			for(int artPt : artPts) {
				excluded=artPt;
				if(!dfs(0)) {
					boolean works=true;
					for(int neighbor : oldGraph.get(artPt)) {
						if(visited[neighbor]) {
							works=false;
							break;
						}
					}
					if(works)
						artPts2.add(artPt);
				}
				Arrays.fill(visited, false);
			}
			out.print(artPts2.size());
			for(int artPt : artPts2)
				out.print(" "+artPt);
			out.println();
		}
		boolean dfs(int node) {
			visited[node]=true;
			if(node==graph.size()-1)
				return true;
			for(int neighbor : graph.get(node))
				if(neighbor!=excluded&&!visited[neighbor]&&dfs(neighbor))
					return true;
			return false;
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