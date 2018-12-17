package section_2_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: nocows
*/
import java.io.*;
import java.util.*;

public class nocows {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "nocows";
	
	static class Solver {
		Solver() {
			int M=9901, N=in.nextInt(), K=in.nextInt();
			long[][] dp = new long[N+1][K+1], dp2 = new long[N+1][K+1];
			dp[1][1]=1;
			for(int i=1; i<=K; ++i)
				dp2[1][i]=1;
			for(int i=3; i<=N; i+=2) {
				for(int j=2; j<=K; ++j) {
					for(int k=1; k<=i-2; k+=2)
						dp[i][j]+=dp[k][j-1]*dp2[i-1-k][j-2];
					dp[i][j]*=2;
					for(int k=1; k<=i-2; k+=2)
						dp[i][j]+=dp[k][j-1]*dp[i-1-k][j-1];
					dp[i][j]%=M;
					dp2[i][j]=(dp2[i][j-1]+dp[i][j])%M;
				}
			}
			out.println(dp[N][K]);
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