import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "team";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final long M=(long)1e9+9;
		
		Solver() {
			int n=in.nextInt(), m=in.nextInt(), k=in.nextInt();
			int[] a = new int[n], b = new int[m];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			Arrays.sort(a);
			for(int i=0; i<m; ++i)
				b[i]=in.nextInt();
			Arrays.sort(b);
			long[][][] dp = new long[2][n+1][m+1];
			for(int i=0; i<=n; ++i)
				Arrays.fill(dp[0][i], 1);
			for(int l=1; l<=k; ++l) {
				for(int i=1; i<=n; ++i)
					for(int j=1; j<=m; ++j)
						dp[l&1][i][j]=((a[i-1]>b[j-1]?dp[l&1^1][i-1][j-1]:0)+dp[l&1][i-1][j]+dp[l&1][i][j-1]-dp[l&1][i-1][j-1]+M)%M;
				if(l==1) {
					for(int i=0; i<=n; ++i)
						dp[0][i][0]=0;
					for(int i=1; i<=m; ++i)
						dp[0][0][i]=0;
				}
			}
			out.println(dp[k&1][n][m]);
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
