package section_3_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: stamps
*/
import java.io.*;
import java.util.*;

public class stamps {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "stamps";
	
	static class Solver {
		static int INF=(int)1e9;
		
		Solver() {
			int k=in.nextInt(), n=in.nextInt();
			int[] stamps = new int[n];
			for(int i=0; i<n; ++i)
				stamps[i]=in.nextInt();
			int[] dp = new int[2000001];
			Arrays.fill(dp, INF);
			dp[0]=0;
			for(int i=1; i<dp.length; ++i) {
				for(int j=0; j<n; ++j)
					if(i-stamps[j]>=0)
						dp[i]=Math.min(dp[i-stamps[j]]+1, dp[i]);
				if(dp[i]>k) {
					out.println(i-1);
					return;
				}
			}
			out.println(2000000);
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