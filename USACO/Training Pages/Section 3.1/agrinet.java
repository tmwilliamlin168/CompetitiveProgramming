package section_3_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: agrinet
*/
import java.io.*;
import java.util.*;

public class agrinet {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "agrinet";
	
	static class Solver {
		static int INF=(int)1e9;
		
		Solver() {
			int n=in.nextInt(), t=0;
			int[][] adj = new int[n][n];
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
					adj[i][j]=in.nextInt();
			int[] dist = new int[n];
			Arrays.fill(dist, INF);
			dist[0]=0;
			boolean[] visited = new boolean[n];
			for(int i=0; i<n; ++i) {
				int minI=-1;
				for(int j=0; j<n; ++j)
					if(!visited[j]&&(minI==-1||dist[j]<dist[minI]))
						minI=j;
				visited[minI]=true;
				t+=dist[minI];
				for(int j=0; j<n; ++j)
					dist[j]=Math.min(adj[minI][j], dist[j]);
			}
			out.println(t);
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