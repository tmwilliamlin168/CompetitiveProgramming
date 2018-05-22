package section_2_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: comehome
*/
import java.io.*;
import java.util.*;

public class comehome {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "comehome";
	
	static class Solver {
		static int INF=(int)1e9;
		
		Solver() {
			int[] cMap = new int[256];
			Arrays.fill(cMap, -1);
			for(char c='A'; c<='Z'; ++c)
				cMap[c]=c-'A';
			for(char c='a'; c<='z'; ++c)
				cMap[c]=c-'a'+26;
			int[][] adj = new int[52][52];
			for(int i=0; i<52; ++i)
				Arrays.fill(adj[i], INF);
			int p=in.nextInt();
			for(int i=0; i<p; ++i) {
				int u=cMap[in.next().charAt(0)], v=cMap[in.next().charAt(0)], dist=in.nextInt();
				adj[u][v]=adj[v][u]=Math.min(dist, adj[u][v]);
			}
			int[] dist = new int[52];
			Arrays.fill(dist, INF);
			boolean[] visited = new boolean[52];
			dist[25]=0;
			while(true) {
				int minI=-1;
				for(int j=0; j<52; ++j)
					if(!visited[j]&&(minI==-1||dist[j]<dist[minI]))
						minI=j;
				visited[minI]=true;
				if(minI<25) {
					out.println((char)(minI+'A')+" "+dist[minI]);
					return;
				}
				for(int j=0; j<52; ++j)
					dist[j]=Math.min(dist[minI]+adj[minI][j], dist[j]);
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