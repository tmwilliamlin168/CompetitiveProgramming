package section_1_5;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: numtri
*/
import java.io.*;
import java.util.*;

public class numtri {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "numtri";
	
	static class Solver {
		Solver() {
			int R=in.nextInt();
			int[][] mat = new int[R][R];
			for(int i=0; i<R; ++i)
				for(int j=0; j<=i; ++j)
					mat[i][j]=in.nextInt();
			int[][] dp = new int[R][R];
			dp[0][0]=mat[0][0];
			for(int i=1; i<R; ++i)
				for(int j=0; j<=i; ++j)
					dp[i][j]=mat[i][j]+Math.max(dp[i-1][j], j==0?0:dp[i-1][j-1]);
			int max=0;
			for(int i=0; i<R; ++i)
				max=Math.max(dp[R-1][i], max);
			out.println(max);
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