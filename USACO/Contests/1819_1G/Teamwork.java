import java.io.*;
import java.util.*;

public class Teamwork {
	static final boolean stdin = false;
	static final String filename = "teamwork";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			//input
			int n=in.nextInt(), k=in.nextInt();
			int[] s = new int[n], dp = new int[n+1];
			for(int i=0; i<n; ++i)
				s[i]=in.nextInt();
			//calc the dp
			for(int i=1; i<=n; ++i) {
				int runningmax=0;
				for(int j=0; j<k&&i>j; ++j) {
					runningmax=Math.max(s[i-j-1], runningmax);
					dp[i]=Math.max(dp[i-j-1]+runningmax*(j+1), dp[i]);
				}
			}
			out.println(dp[n]);
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