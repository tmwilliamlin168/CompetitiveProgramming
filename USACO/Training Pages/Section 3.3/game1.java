package section_3_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: game1
*/
import java.io.*;
import java.util.*;

public class game1 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "game1";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] a = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			int[][] dp1 = new int[n+1][n+1], dp2 = new int[n+1][n+1];
			for(int l=1; l<=n; ++l) {
				for(int i=0; i+l<=n; ++i) {
					if(dp2[i+1][i+l]+a[i]>dp2[i][i+l-1]+a[i+l-1]) {
						dp1[i][i+l]=dp2[i+1][i+l]+a[i];
						dp2[i][i+l]=dp1[i+1][i+l];
					} else {
						dp1[i][i+l]=dp2[i][i+l-1]+a[i+l-1];
						dp2[i][i+l]=dp1[i][i+l-1];
					}
				}
			}
			out.println(dp1[0][n]+" "+dp2[0][n]);
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