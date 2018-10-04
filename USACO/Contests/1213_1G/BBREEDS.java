import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "bbreeds";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final int M=2012;
		
		Solver() {
			char[] s = in.next().toCharArray();
			int n=s.length, p=0;
			int[][] dp = new int[n+1][n+1];
			dp[0][0]=1;
			for(int i=0; i<n; ++i) {
				for(int j=0; j<=n; ++j) {
					if(dp[i][j]==0)
						continue;
					if(s[i]=='(') {
						dp[i+1][j+1]=(dp[i][j]+dp[i+1][j+1])%M;
						dp[i+1][j]=(dp[i][j]+dp[i+1][j])%M;
					} else {
						if(j>0)
							dp[i+1][j-1]=(dp[i][j]+dp[i+1][j-1])%M;
						if(j<p)
							dp[i+1][j]=(dp[i][j]+dp[i+1][j])%M;
					}
				}
				p+=(s[i]=='('?1:-1);
			}
			out.println(p==0?dp[n][0]:0);
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
