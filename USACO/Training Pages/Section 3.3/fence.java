package section_3_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: fence
*/
import java.io.*;
import java.util.*;

public class fence {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "fence";
	
	static class Solver {
		int[][] adj = new int[500][500];
		int tourI;
		int[] tour;
		
		Solver() {
			int f=in.nextInt();
			tour = new int[f+1];
			for(int i=0; i<f; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				++adj[u][v];
				++adj[v][u];
			}
			int minOdd=-1, minEven=-1;
			for(int i=0; i<500; ++i) {
				int t=0;
				for(int j=0; j<500; ++j)
					t+=adj[i][j];
				if(minOdd==-1&&t%2==1) {
					minOdd=i;
					break;
				} else if(minEven==-1&&t%2==0)
					minEven=i;
			}
			if(minOdd==-1)
				findCircuit(minEven);
			else
				findCircuit(minOdd);
			for(int i=0; i<f+1; ++i)
				out.println(tour[f-i]+1);
		}
		
		void findCircuit(int node) {
			for(int i=0; i<500; ++i) {
				while(adj[node][i]>0) {
					--adj[node][i];
					--adj[i][node];
					findCircuit(i);
				}
			}
			tour[tourI++]=node;
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