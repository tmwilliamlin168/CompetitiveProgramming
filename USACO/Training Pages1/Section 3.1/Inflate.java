package section_3_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: inflate
*/
import java.io.*;
import java.util.*;

public class inflate {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "inflate";
	
	static class Solver {
		Solver() {
			int m=in.nextInt(), n=in.nextInt();
			int[] len = new int[n], pts = new int[n], dp = new int[m+1];
			for(int i=0; i<n; ++i) {
				pts[i]=in.nextInt();
				len[i]=in.nextInt();
			}
			for(int i=0; i<m; ++i)
				for(int j=0; j<n; ++j)
					if(i+len[j]<=m)
						dp[i+len[j]]=Math.max(dp[i]+pts[j], dp[i+len[j]]);
			out.println(dp[m]);
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