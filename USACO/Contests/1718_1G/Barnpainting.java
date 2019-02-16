import java.io.*;
import java.util.*;

public class Main {
	static boolean stdio=false;
	static Reader in = new Reader();
	static PrintWriter out;
	
	static final int M=(int)1e9+7;
	static List<Integer>[] graph;
	static int[] prepaint;
	static long[][] dp;
	
	public static void main(String[] args) {
		if(stdio)
			out = new PrintWriter(System.out);
		else {
			try {
				out = new PrintWriter("barnpainting.out");
			} catch (Exception e) {}
		}
		int n=in.nextInt(), k=in.nextInt();
		graph = new List[n];
		for(int i=0; i<n; ++i)
			graph[i] = new ArrayList<Integer>();
		for(int i=0; i<n-1; ++i) {
			int u=in.nextInt()-1, v=in.nextInt()-1;
			graph[u].add(v);
			graph[v].add(u);
		}
		prepaint = new int[n];
		Arrays.fill(prepaint, -1);
		for(int i=0; i<k; ++i) {
			int b=in.nextInt()-1, c=in.nextInt()-1;
			prepaint[b]=c;
		}
		dp = new long[3][n];
		dfs(0, -1);
		out.println((dp[0][0]+dp[1][0]+dp[2][0])%M);
		out.close();
	}
	
	static void dfs(int u, int p) {
		for(int v : graph[u])
			if(v!=p)
				dfs(v, u);
		for(int i=0; i<3; ++i) {
			if(prepaint[u]!=-1&&prepaint[u]!=i)
				continue;
			dp[i][u]=1;
			for(int v : graph[u]) {
				if(v==p)
					continue;
				long sum=0;
				for(int j=0; j<3; ++j)
					if(j!=i)
						sum+=dp[j][v];
				dp[i][u]=sum%M*dp[i][u]%M;
			}
		}
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			if(stdio)
				br = new BufferedReader(new InputStreamReader(System.in));
			else {
				try {
					br = new BufferedReader(new FileReader("barnpainting.in"));
				} catch (Exception e) {}
			}
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
