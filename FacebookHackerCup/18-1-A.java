import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long M=(long)1e9+7;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt();
			char[][] g = new char[3][];
			for(int i=0; i<3; ++i)
				g[i]=in.next().toCharArray();
			int[][] dp = new int[n+1][3];
			dp[0][0]=1;
			for(int i=0; i<n; ++i) {
				if(g[0][i]=='.'&&g[1][i]=='.') {
					dp[i+1][0]+=dp[i][1];
					dp[i+1][1]+=dp[i][0];
				}
				if(g[1][i]=='.'&&g[2][i]=='.') {
					dp[i+1][1]+=dp[i][2];
					dp[i+1][2]+=dp[i][1];
				}
				dp[i+1][1]%=M;
			}
			out.println("Case #"+ti+": "+dp[n][2]);
		}
		out.close();
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
