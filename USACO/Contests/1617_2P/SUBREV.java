import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "subrev";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		int[] a;
		int[][][][] dp;
		
		Solver() {
			int n=in.nextInt();
			a = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			dp = new int[n][n][51][51];
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
					for(int k=1; k<=50; ++k)
						Arrays.fill(dp[i][j][k], -1);
			out.println(dp(0, n-1, 1, 50));
		}
		
		int dp(int l, int r, int x, int y) {
			if(l>r||x>y)
				return 0;
			if(l==r)
				return x<=a[l]&&a[l]<=y?1:0;
			if(dp[l][r][x][y]<0) {
				if(x<=a[l]&&a[l]<=y) {
					dp[l][r][x][y]=Math.max(dp(l+1, r, a[l], y)+1, dp[l][r][x][y]);
					dp[l][r][x][y]=Math.max(dp(l+1, r-1, x, a[l])+1, dp[l][r][x][y]);
					if(x<=a[r]&&a[r]<=a[l])
						dp[l][r][x][y]=Math.max(dp(l+1, r-1, a[r], a[l])+2, dp[l][r][x][y]);
				}
				if(x<=a[r]&&a[r]<=y) {
					dp[l][r][x][y]=Math.max(dp(l, r-1, x, a[r])+1, dp[l][r][x][y]);
					dp[l][r][x][y]=Math.max(dp(l+1, r-1, a[r], y)+1, dp[l][r][x][y]);
				}
				dp[l][r][x][y]=Math.max(dp(l+1, r, x, y), dp[l][r][x][y]);
				dp[l][r][x][y]=Math.max(dp(l, r-1, x, y), dp[l][r][x][y]);
			}
			return dp[l][r][x][y];
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
