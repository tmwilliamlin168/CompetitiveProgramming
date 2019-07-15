import java.io.*;
import java.util.*;

public class C {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int h=in.nextInt(), s=in.nextInt(), m=in.nextInt();
			char[][] g = new char[h][s];
			for(int i=0; i<h; ++i)
				g[i]=in.next().toCharArray();
			int[] l = new int[m];
			for(int i=0; i<m; ++i)
				l[i]=in.nextInt();
			int[][][][] dp = new int[s][h+1][2][h+1];
			for(int a=0; a<s; ++a) {
				for(int i=1; i<=h; ++i)
					for(int j=0; j<2; ++j)
						Arrays.fill(dp[a][i][j], (int)1e9);
				for(int i=0; i<h; ++i) {
					int c=g[i][a]-'A';
					for(int k=1; k<=h; ++k)
						dp[a][i+1][c][k]=Math.min(dp[a][i][c][k], dp[a][i+1][c][k]);
					for(int k=1; k<h; ++k)
						dp[a][i+1][c][k+1]=Math.min(dp[a][i][c^1][k], dp[a][i+1][c][k+1]);
					for(int j=0; j<2; ++j)
						for(int k=1; k<=h; ++k)
							dp[a][i+1][j][k]=Math.min(dp[a][i][j][k]+1, dp[a][i+1][j][k]);
				}
			}
			int[] ans = new int[h*s+1];
			ans[0]=h+1;
			for(int i=h, ca; i>0; --i) {
				ca=0;
				for(int j=0; j<s; ++j)
					ca+=Math.min(dp[j][h][0][i], dp[j][h][1][i]);
				ans[ca]=i+1;
				ca=0;
				for(int j=0; j<s; ++j) {
					ca+=Math.min(dp[j][h][0][i], dp[j][h][1][i-1]);
				}
				ans[ca]=i;
				ca=0;
				for(int j=0; j<s; ++j) {
					ca+=Math.min(dp[j][h][0][i-1], dp[j][h][1][i]);
				}
				ans[ca]=i;
			}
			for(int i=0; i<h*s; ++i)
				if(ans[i]<1)
					ans[i]=ans[i-1];
			out.print("Case #"+_+":");
			for(int i=0; i<m; ++i)
				out.print(" "+ans[l[i]]);
			out.println();
		}
		out.close();
	}
	
	static class Pair {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
		}
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
