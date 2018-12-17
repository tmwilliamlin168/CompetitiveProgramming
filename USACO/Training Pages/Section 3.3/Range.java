package section_3_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: range
*/
import java.io.*;
import java.util.*;

public class range {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "range";
	
	static class SolverA {
		SolverA() {
			//O(n^3) solver
			int n=in.nextInt();
			char[][] mat = new char[n][];
			for(int i=0; i<n; ++i)
				mat[i]=in.next().toCharArray();
			for(int s=2; s<=n; ++s) {
				int t=0;
				for(int i=0; i<=n-s; ++i)
					for(int j=0; j<=n-s; ++j)
						if(mat[i][j]=='1'&&mat[i+1][j]=='1'&&mat[i][j+1]=='1'&&mat[i+1][j+1]=='1')
							++t;
						else
							mat[i][j]='0';
				if(t!=0)
					out.println(s+" "+t);
			}
		}
	}

	static class SolverB {
		SolverB() {
			//O(n^2) solver
			int n=in.nextInt();
			char[][] mat = new char[n][];
			for(int i=0; i<n; ++i)
				mat[i]=in.next().toCharArray();
			int[] cnt = new int[n+1];
			int[][] dp = new int[n+1][n+1];
			for(int i=1; i<=n; ++i) {
				for(int j=1; j<=n; ++j) {
					if(mat[i-1][j-1]=='1') {
						dp[i][j]=Math.min(Math.min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1])+1;
						++cnt[dp[i][j]];
					}
				}
			}
			for(int i=n; i>=3; --i)
				cnt[i-1]+=cnt[i];
			for(int i=2; i<=n; ++i)
				if(cnt[i]!=0)
					out.println(i+" "+cnt[i]);
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
			//new SolverA();
			new SolverB();
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