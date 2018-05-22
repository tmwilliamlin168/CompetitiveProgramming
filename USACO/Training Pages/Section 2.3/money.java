package section_2_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: money
*/
import java.io.*;
import java.util.*;

public class money {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "money";
	
	static class Solver {
		Solver() {
			int v=in.nextInt(), n=in.nextInt();
			int[] c = new int[v];
			for(int i=0; i<v; ++i)
				c[i]=in.nextInt();
			long[][] dp = new long[v+1][n+1];
			dp[0][0]=1;
			for(int i=1; i<=v; ++i) {
				for(int j=0; j<=n; ++j) {
					for(int k=0; j+k*c[i-1]<=n; ++k) {
						dp[i][j+k*c[i-1]]+=dp[i-1][j];
					}
				}
			}
			out.println(dp[v][n]);
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