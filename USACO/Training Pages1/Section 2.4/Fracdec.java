package section_2_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: fracdec
*/
import java.io.*;
import java.util.*;

public class fracdec {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "fracdec";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), d=in.nextInt();
			StringBuilder s=new StringBuilder(n/d+".");
			if(n%d==0)
				s.append("0");
			else {
				int[] remPos = new int[d*10];
				n=n%d;
				n*=10;
				while(true) {
					if(n==0||remPos[n]!=0)
						break;
					remPos[n]=s.length();
					s.append(n/d);
					n=n%d;
					n*=10;
				}
				if(n!=0)
					s=new StringBuilder(s.substring(0, remPos[n])+"("+s.substring(remPos[n])+")");
			}
			for(int i=0; i<s.length(); i+=76)
				out.println(s.substring(i, Math.min(i+76, s.length())));
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