package section_5_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: theme
*/
import java.io.*;
import java.util.*;

public class theme {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "theme";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] a = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			int max=1;
			for(int i=1; i<n; ++i) {
				int c=1;
				for(int j=1; j+1<=n-i; ++j) {
					if(a[j]-a[j-1]==a[j+i]-a[j+i-1])
						++c;
					else
						c=1;
					c=Math.min(c, i);
					max=Math.max(max, c);
				}
			}
			if(max<5)
				out.println(0);
			else
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