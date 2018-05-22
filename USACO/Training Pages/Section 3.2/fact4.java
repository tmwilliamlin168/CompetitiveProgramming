package section_3_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: fact4
*/
import java.io.*;
import java.util.*;

public class fact4 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "fact4";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int ignore2s=n/5+n/25+n/125+n/625+n/3125;
			int res=1;
			for(int i=1; i<=n; ++i) {
				int a=i;
				while(a%5==0)
					a/=5;
				while(ignore2s>0&&a%2==0) {
					a/=2;
					--ignore2s;
				}
				res=res*a%10;
			}
			out.println(res);
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