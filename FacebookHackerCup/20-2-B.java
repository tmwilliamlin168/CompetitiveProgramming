import java.io.*;
import java.util.*;

public class B {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			double p=in.nextDouble();
			double[][] dp = new double[n][n];
			for(int i=0; i<n; ++i) {
				for(int j=0; j<n; ++j) {
					if(i<1&&j<1)
						continue;
					if(i>0)
						dp[i][j]+=i*(i-1)/2*dp[i-1][j]+i*j*p*dp[i-1][j]+i*p*dp[i-1][j];
					if(j>0)
						dp[i][j]+=j*(j-1)/2*dp[i][j-1]+i*j*(1-p)*dp[i][j-1]+j*(1-p)*dp[i][j-1];
					dp[i][j]=dp[i][j]*2/(i+j+1)/(i+j)+1;
				}
			}
			out.println();
			for(int i=0; i<n; ++i)
				out.println(dp[i][n-1-i]);
		}
	}
	
	static class Reader {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		String next() {
			while(st==null||!st.hasMoreTokens()) {
				try {
					st=new StringTokenizer(in.readLine());
				} catch(Exception e) {}
			}	
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
		double nextDouble() {
			return Double.parseDouble(next());
		}
	}
}
