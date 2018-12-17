/*
ID: tmwilliamlin168
LANG: JAVA
TASK: tour
*/
import java.io.*;
import java.util.*;

public class tour {
	static final boolean stdin = false;
	static final String filename = "tour";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			Map<String, Integer> mp = new HashMap<String, Integer>();
			for(int i=0; i<n; ++i)
				mp.put(in.next(), i);
			List<Integer>[] adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=0; i<m; ++i) {
				int u=mp.get(in.next()), v=mp.get(in.next());
				adj[u].add(v);
				adj[v].add(u);
			}
			int[][] dp = new int[n][n];
			for(int i=0; i<n; ++i)
				Arrays.fill(dp[i], -n);
			dp[0][0]=1;
			for(int i=0; i<n; ++i) {
				for(int j=0; j<i; ++j)
					dp[i][j]=dp[j][i];
				if(i>0)
					dp[i][i]=-n;
				for(int j=i+1; j<n; ++j)
					for(int k : adj[j])
						if(k<j)
							dp[i][j]=Math.max(dp[i][k]+1, dp[i][j]);
			}
			int ans=1;
			for(int i : adj[n-1])
				ans=Math.max(dp[n-1][i], ans);
			out.println(ans);
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
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