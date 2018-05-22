package section_4_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: nuggets
*/
import java.io.*;
import java.util.*;

public class nuggets {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "nuggets";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] a = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			int gcd=a[0];
			for(int i=1; i<n; ++i)
				gcd=gcd(a[i], gcd);
			if(gcd>1) {
				out.println(0);
				return;
			}
			boolean[] dp = new boolean[(1<<16)+1];
			dp[0]=true;
			for(int i=0; i<n; ++i)
				for(int j=a[i]; j<dp.length; ++j)
					dp[j]|=dp[j-a[i]];
			dp[0]=false;
			for(int i=dp.length-1; ; --i) {
				if(!dp[i]) {
					out.println(i);
					break;
				}
			}
		}
		int gcd(int a, int b) {
			if(b>a) {
				a^=b;
				b^=a;
				a^=b;
			}
			int r;
			while(b!=0) {
				r=a%b;
				a=b;
				b=r;
			}
			return a;
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