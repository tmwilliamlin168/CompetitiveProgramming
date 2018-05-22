package section_3_4;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: fence9
*/
import java.io.*;
import java.util.*;

public class fence9 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "fence9";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt(), p=in.nextInt(), t=((n-1)*(m-1)-(gcd(n, m)-1))/2;
			if(n<p) {
				t+=((p-n-1)*(m-1)-(gcd(p-n, m)-1))/2+m-1;
			} else if(n>p) {
				t-=((n-p-1)*(m-1)-(gcd(n-p, m)-1))/2+gcd(n-p, m)-1;
			}
			out.println(t);
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